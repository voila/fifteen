open FFI;

let show = id => getElementById(id) |> style |> display(_, "block");

let create = () => {
  let canvas = Canvas.create("game", "image", 600);
  let board = ref(Board.initial());
  Board.draw(board^, canvas);
  Canvas.onClick(
    canvas,
    evt => {
      board := Board.click((offsetX(evt), offsetY(evt)), board^);
      let solved = Board.solved(board^);
      Board.draw(board^, canvas);
      solved ? show("msg") : ();
    },
  );
};
/* create(); */