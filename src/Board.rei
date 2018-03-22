type idx;

type coords;

type t;

let size: int;

let empty: t;

let click: ((int, int), t) => t;

let swapable: t => list(idx);

let holeIdx: t => idx;

let swap: (idx, idx, t) => t;

let draw: (t, Canvas.t) => unit;

let initial: unit => t;

let toIdx: coords => idx;

let toCoords: idx => coords;

let toImgC: coords => coords;

let toTileC: coords => coords;

let solved: t => bool;