open FFI;

type t = (canvas, context, image);

let create = (~containerId, ~imageId, ~width) => {
  let cvs = createElement("canvas");
  setWidth(cvs, width) |> ignore;
  setHeight(cvs, width) |> ignore;
  let container = getElementById(containerId);
  let ctx = getContext(cvs);
  let img = getElementById(imageId);
  let () = appendChild(container, cvs) |> ignore;
  (cvs, ctx, img);
};

/* let clear = (cvs, ctx, _) => {
     let width = getWidth(cvs);
     clearRect(~ctx, 0, 0, width, width);
   }; */
let fillRect = (~canvas as (_, ctx, _), ~x, ~y, ~width, ~color) => {
  setFillStyle(ctx, color) |> ignore;
  fillRect(~ctx, ~x, ~y, ~w=width, ~h=width) |> ignore;
};

let drawImage = (~canvas as (_, ctx, img), ~sx, ~sy, ~dx, ~dy, ~width) =>
  drawImage(
    ~ctx,
    ~img,
    ~sx,
    ~sy,
    ~sw=width,
    ~sh=width,
    ~dx,
    ~dy,
    ~dw=width,
    ~dh=width,
  );

let onClick = (~canvas as (cvs, _, _), ~handle) =>
  addEventListener(cvs, "click", handle);