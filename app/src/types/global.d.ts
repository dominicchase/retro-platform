export {};

declare global {
  interface Window {
    api: {
      getGames: (system: System) => Promise<Game[]>;
      launchGame: (gameId: string) => Promise<void>;
    };
  }
}
