type t;

/* create a board to represent the tiles position  */
let initial: unit => t;

/* return the board resulting from clicking on tile (x,y)  */
let click: (~coords: (int, int), ~board: t) => t;

/* draw the given board to the canvas */
let draw: (~board: t, ~canvas: Canvas.t) => unit;

/* is the given board solved? */
let solved: (~board: t) => bool;