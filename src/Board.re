/* Tile */
module Tile = {
  type coords = (int, int)
  and t = 
    | Tile(coords)
    | Hole;
  let draw = ((i', j'), tile, canvas, width) =>
    switch (tile) {
    | Hole => ()
    | Tile((i, j)) =>
      Canvas.drawImage(
        ~canvas,
        ~sx=i * width,
        ~sy=j * width,
        ~dx=i' * width,
        ~dy=j' * width,
        ~width,
      )
    };
  
  let animate = (tile, (i,j) as _start, (i',j') as _dest, canvas, width) => {
    switch (tile) {
      | Hole => failwith("Tile.animate: hole tile")
      | Tile((ti, tj)) =>
      /* distance needs to be a multiple of steps, otherwise tile wont be drawn where it should */
        let steps = 10;
        let step = ref(0);
        let dx = ref(i * width);
        let dy = ref(j * width);
        let deltaX = (i' - i) * width / steps; 
        let deltaY = (j' - j) * width / steps;
        let rec drawStep = (_time) => {
          if(step^ < steps){
            /* delete tile at previous location */
            Canvas.clearRect(~canvas, ~x=dx^, ~y=dy^, ~width, ~height=width);
            step := step^ + 1;
            dx := i * width + step^ * deltaX;
            dy := j * width + step^ * deltaY;
            /* draw tile at new location */
            Canvas.drawImage(
            ~canvas,
            ~sx=ti * width,
            ~sy=tj * width,
            ~dx=dx^,
            ~dy=dy^,
            ~width,
            );
            FFI.requestAnimationFrame(drawStep) |> ignore;
          } else {
            ()
          }
        };
      FFI.requestAnimationFrame(drawStep) |> ignore;
    }
  };
  
  let tile = ((i, j)) => Tile((i, j));
};

type idx = int;

type t = array(Tile.t);

let sides = 4;

let width = 600 / sides;

let size = sides * sides;

let toIdx = ((i, j)) => i + sides * j;

let toCoords = i => (i mod sides, i / sides);

/* let toImgC = ((i, j)) => (i * width, j * width); */
let toTileC = ((x, y)) => (x / width, y / width);

let replaceWithHole = (i, b) =>
  switch (b[i]) {
  | Tile.Tile(_) =>
    b[i] = Tile.Hole;
    b;
  | _ => assert false
  };

let draw = (~board as b, ~canvas as cvs) =>
  Belt.Array.forEachWithIndex(b, (i, t) =>
    Tile.draw(toCoords(i), t, cvs, width)
  );

let holeIdx = b => {
  let idx = ref(0);
  for (i in 0 to size - 1) {
    switch (b[i]) {
    | Tile.Hole => idx := i
    | Tile.Tile(_) => ()
    };
  };
  idx^;
};

let inBounds = ((x, y)) =>
  x >= 0 && y >= 0 && x <= sides - 1 && y <= sides - 1;

let swapable = b => {
  let (hx, hy) = holeIdx(b) |> toCoords;
  let neighbours = [
    (hx - 1, hy),
    (hx, hy - 1),
    (hx + 1, hy),
    (hx, hy + 1),
  ];
  /* Discard out of bounds coordinates */
  Belt.List.keep(neighbours, inBounds) |> (l => Belt.List.map(l, toIdx));
};

let swap = (i1, i2, b) => {
  let t1 = b[i1];
  b[i1] = b[i2];
  b[i2] = t1;
  b;
};

let click = (~coords as (x, y), ~board as b, ~canvas as cvs) => {
  /* First we map x,y to the tile */
  let (i,j) = toTileC((x, y));
  let idx = (i,j) |> toIdx;
  /* if selected tile is adjacent to the hole */
  if (Belt.List.some(swapable(b), i => i == idx)) {
    /* we animate the clicked tile */
    Tile.animate(b[idx], (i,j), holeIdx(b) |> toCoords, cvs, width);
    /* we swap them */
    swap(idx, holeIdx(b), b);
  } else {
    b;
  };
};

/* move the hole at ramdom, n =< x < n + n times */
let scramble = (n, b) => {
  Random.self_init();
  let rounds = Random.int(n) + n;
  let rec loop = (n, lastIdx, b) =>
    if (n > 0) {
      let nextIdx =
        Belt.List.(
          shuffle(swapable(b))
          |> (b => keep(b, idx => idx != lastIdx) |> headExn)
        );
      /* we know headExn is safe because swapable(b) should always have 2+ elts ! */
      let holeIdx = holeIdx(b);
      let b' = swap(holeIdx, nextIdx, b);
      loop(n - 1, nextIdx, b');
    } else {
      b;
    };
  loop(rounds, -1, b); /* for first scramble, the last index is not needed (-1) */
};

let initial = () =>
  Belt.Array.makeBy(size, i => i |> toCoords |> Tile.tile)
  |> replaceWithHole(Random.int(16))
  |> scramble(30);

let id = x => x;

let solved = (~board as b) =>
  Belt.Array.(
    mapWithIndex(b, (i, t) =>
      switch (t) {
      | Tile.Hole => true
      | Tile.Tile(coords) => i == toIdx(coords)
      }
    )
    |> (b => every(b, id))
  );