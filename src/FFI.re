type css;

/* type window; */
/* [@bs.val] external window : window = "window"; */
/* [@bs.set] external onload : (window, unit => unit) => unit = ""; */
type time;

[@bs.val]
external requestAnimationFrame : (time => unit) => int =
  "window.requestAnimationFrame";

[@bs.get] external offsetX : Dom.event => int = "";

[@bs.get] external offsetY : Dom.event => int = "";

/* [@bs.val] external alert : string => unit = "alert"; */
[@bs.val]
external getElementById : string => Dom.element = "document.getElementById";

[@bs.get] external style : Dom.element => css = "";

[@bs.set] external display : (css, string) => unit = "";

type document;

[@bs.val] external doc : document = "document";

[@bs.val]
external createElement : string => Dom.element = "document.createElement";

[@bs.send] external appendChild : (Dom.element, Dom.element) => unit = "";

[@bs.get] external getWidth : Dom.element => int = "innerWidth";

[@bs.get] external getHeight : Dom.element => int = "innerHeight";

[@bs.set] external setWidth : (Dom.element, int) => unit = "width";

[@bs.set] external setHeight : (Dom.element, int) => unit = "height";

type image = Dom.element;

type canvasRenderingContext2D = Dom.element;

type context = canvasRenderingContext2D;

type canvas = Dom.element;

[@bs.send]
external getContext : (canvas, [@bs.as "2d"] _) => canvasRenderingContext2D =
  "";

[@bs.send]
external drawImage :
  (
    ~ctx: canvasRenderingContext2D,
    ~img: image,
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
external clearRect :
  (~ctx: canvasRenderingContext2D, int, int, int, int) => unit =
  "";

[@bs.send] external save : (~ctx: canvasRenderingContext2D, unit) => unit = "";

[@bs.send]
external restore : (~ctx: canvasRenderingContext2D, unit) => unit = "";

[@bs.send]
external addEventListener : (Dom.element, string, Dom.event => unit) => unit =
  "";

[@bs.send]
external removeEventListener : (Dom.element, string, Dom.event => unit) => unit =
  "";