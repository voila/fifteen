/* Tile */
module Tile = {
  type coords = (int, int)
  and t =
    | Tile(coords)
    | Hole;
  let draw = ((i', j'): coords, tile: t, cvs: Canvas.t, width: int) =>
    switch (tile) {
    | Hole => Canvas.fillRect(cvs, i' * width, j' * width, width, "#000000")
    | Tile((i, j)) =>
      Canvas.drawImage(
        cvs,
        i * width,
        j * width,
        i' * width,
        j' * width,
        width,
      )
    };
  let tile = ((i, j)) => Tile((i, j));
  /* let show = t =>
     switch (t) {
     | Tile((i, j)) => {j|tile ($i, $j)|j}
     | Hole => {j|hole|j}
     }; */
};

type idx = int;

type coords = Tile.coords;

type t = array(Tile.t);

let sides = 3;

let width = 600 / sides;

let size = sides * sides;

let toIdx = ((i, j)) => i + sides * j;

let toCoords = i => (i mod sides, i / sides);

let toImgC = ((i, j)) => (i * width, j * width);

let toTileC = ((x, y)) => (x / width, y / width);

let replaceWithHole = (i, b) =>
  switch (b[i]) {
  | Tile.Tile(_) =>
    b[i] = Tile.Hole;
    b;
  | _ => assert false
  };

let empty = [||];

let draw = (b, cvs) =>
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

let click = ((x, y), b) => {
  /* First we map x,y to the tile */
  let i' = toTileC((x, y)) |> toIdx;
  /* if selected tile is adjacent to the hole */
  if (Belt.List.some(swapable(b), i => i == i')) {
    swap(i', holeIdx(b), b);
  } else {
    b;
  };
};

/* move the hole at ramdom, n times */
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
      let holeIdx = holeIdx(b);
      /** we know headExn is safe here ! */
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
  |> scramble(15);

let id = x => x;

let solved = b =>
  Belt.Array.(
    mapWithIndex(b, (i, t) =>
      switch (t) {
      | Tile.Hole => true
      | Tile.Tile(coords) => i == toIdx(coords)
      }
    )
    |> (b => every(b, id))
  );