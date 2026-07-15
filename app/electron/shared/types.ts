export type System = "SNES";

export type Core = "snes9x";

export type Game = {
  id: string;
  title: string;
  coverFile: string;
  system: System;
  romPath: string;
};
