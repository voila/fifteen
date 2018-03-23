type t;

/* Create from HTML canvas elt, canvas context and the game's image */
let create: (~containerId: string, ~imageId: string, ~width: int) => t;

/* attach an onclick event handler */
let onClick: (~canvas: t, ~handle: Dom.event => unit) => unit;

/* draw a colored rectangle */
let fillRect:
  (~canvas: t, ~x: int, ~y: int, ~width: int, ~color: string) => unit;

/* draw portion of the game's image */
let drawImage:
  (~canvas: t, ~sx: int, ~sy: int, ~dx: int, ~dy: int, ~width: int) => unit;