type t;

/* Create from HTML canvas elt, canvas context and the game's image */
let create: (~containerId: string, ~imageId: string, ~width: int) => t;

/* attach an onclick event handler */
let onClick: (~canvas: t, ~handle: Dom.event => unit) => unit;

/* delete a rectangular portion of the canvs */
let clearRect:
  (~canvas: t, ~x: int, ~y: int, ~width: int, ~height: int) => unit;

/* draw portion of the game's image */
let drawImage:
  (~canvas: t, ~sx: int, ~sy: int, ~dx: int, ~dy: int, ~width: int) => unit;