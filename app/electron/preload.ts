import { contextBridge, ipcRenderer } from "electron";
import { Game, System } from "./shared/types";

contextBridge.exposeInMainWorld("api", {
  getGames: async (system: System): Promise<Game[]> => {
    return ipcRenderer.invoke("games:get", system);
  },
  launchGame: async (gameId: string): Promise<void> => {
    return ipcRenderer.invoke("game:launch", gameId);
  },
});
