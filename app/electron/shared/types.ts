export type System = "SNES";

export type Game = {
  id: string;
  title: string;
  coverFile: string;
  system: System;
  romPath: string;
};
