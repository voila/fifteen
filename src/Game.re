open FFI;

let show = id => getElementById(id) |> style |> display(_, "block");

let create = () => {
  let canvas =
    Canvas.create(~containerId="game", ~imageId="image", ~width=600);
  let b = ref(Board.initial());
  Board.draw(~board=b^, ~canvas);
  /* event loop */
  Canvas.onClick(
    ~canvas,
    ~handle=evt => {
      b := Board.click(~coords=(offsetX(evt), offsetY(evt)), ~board=b^,~canvas);
      Board.solved(~board=b^) ? show("msg") : ();
    },
  );
};