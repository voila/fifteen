type element;

type css;

/* type window; */
/* [@bs.val] external window : window = "window"; */
/* [@bs.set] external onload : (window, unit => unit) => unit = ""; */
[@bs.get] external offsetX : Dom.event => int = "";

[@bs.get] external offsetY : Dom.event => int = "";

/* [@bs.val] external alert : string => unit = "alert"; */
[@bs.val]
external getElementById : string => element = "document.getElementById";

[@bs.get] external style : element => css = "";

[@bs.set] external display : (css, string) => unit = "";

type document;

[@bs.val] external doc : document = "document";

[@bs.val]
external createElement : string => element = "document.createElement";

[@bs.send] external appendChild : (element, element) => unit = "";

[@bs.get] external getWidth : element => int = "innerWidth";

[@bs.get] external getHeight : element => int = "innerHeight";

[@bs.set] external setWidth : (element, int) => unit = "width";

[@bs.set] external setHeight : (element, int) => unit = "height";

type imageElement = element;

type canvasRenderingContext2D = element;

type context = canvasRenderingContext2D;

type canvasElement = element;

[@bs.send]
external getContext :
  (canvasElement, [@bs.as "2d"] _) => canvasRenderingContext2D =
  "getContext";

[@bs.send]
external drawImage :
  (
    ~ctx: canvasRenderingContext2D,
    ~img: imageElement,
    ~sx: int,
    ~sy: int,
    ~sw: int,
    ~sh: int,
    ~dx: int,
    ~dy: int,
    ~dw: int,
    ~dh: int
  ) =>
  unit =
  "";

[@bs.set]
external setFillStyle : (canvasRenderingContext2D, string) => unit =
  "fillStyle";

[@bs.send]
external fillRect :
  (~ctx: canvasRenderingContext2D, ~x: int, ~y: int, ~w: int, ~h: int) => unit =
  "";

[@bs.send]
external clearRect :
  (~ctx: canvasRenderingContext2D, int, int, int, int) => unit =
  "";

[@bs.send]
external addEventListener : (element, string, Dom.event => unit) => unit =
  "addEventListener";