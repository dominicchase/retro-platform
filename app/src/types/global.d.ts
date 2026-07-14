export {};

declare global {
  interface Game {
    title: string;
    romPath: string;
    coverPath: string;
    system: "SNES";
  }

  interface Window {
    api: {
      getSNESGames: () => Promise<Game[]>;
    };
  }
}
