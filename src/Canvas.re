open FFI;

type t =
  | E
  | C(element, element);

let empty = E;

let create = (containerId, imageId, width) => {
  let cvs = createElement("canvas");
  setWidth(cvs, width) |> ignore;
  setHeight(cvs, width) |> ignore;
  let container = getElementById(containerId);
  let img = getElementById(imageId);
  let () = appendChild(container, cvs) |> ignore;
  C(cvs, img);
};

let clear =
  fun
  | C(cvs, _) => {
      let width = getWidth(cvs);
      let ctx = getContext(cvs);
      clearRect(~ctx, 0, 0, width, width);
    }
  | E => failwith("Empty Canvas");

let fillRect = (cvs, x, y, width, color) =>
  switch (cvs) {
  | C(cvs, _) =>
    let ctx = getContext(cvs);
    setFillStyle(ctx, color) |> ignore;
    fillRect(~ctx, ~x, ~y, ~w=width, ~h=width) |> ignore;
  | E => failwith("Empty Canvas")
  };

let drawImage =
    /*: type a. (t(a), element, int, int, int, int, int) => unit */
    (cvs, x, y, x', y', width) =>
  switch (cvs) {
  | C(cvs, img) =>
    let ctx = getContext(cvs);
    drawImage(
      ~ctx,
      ~img,
      ~sx=x,
      ~sy=y,
      ~sw=width,
      ~sh=width,
      ~dx=x',
      ~dy=y',
      ~dw=width,
      ~dh=width,
    );
  | E => failwith("Empty Canvas")
  };

let onClick = (cvs, handle) =>
  switch (cvs) {
  | C(cvs, _) => addEventListener(cvs, "click", handle)
  | E => failwith("Empty Canvas")
  };