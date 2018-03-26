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

let clearRect = (~canvas as (_, ctx, _), ~x, ~y, ~width, ~height) => {
     clearRect(~ctx, x, y, width, height);
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