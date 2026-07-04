/* eslint-disable @typescript-eslint/no-explicit-any */
export {};

declare global {
  interface Window {
    electronAPI: {
      launchGame: (gamePath: string) => Promise<any>;
    };
  }
}
