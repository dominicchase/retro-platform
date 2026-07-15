export {};

export type System = "SNES";

declare global {
  interface Game {
    id: string;
    title: string;
    coverFile: string;
    system: System;
    romPath: string;
  }

  interface Window {
    api: {
      getGames: (system: System) => Promise<Game[]>;
      launchGame: (gameId: string) => Promise<void>;
    };
  }
}
