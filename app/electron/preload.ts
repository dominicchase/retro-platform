import { contextBridge, ipcRenderer } from "electron";
import { System } from "../src/types/global";

contextBridge.exposeInMainWorld("api", {
  getGames: async (system: System): Promise<Game[]> => {
    return ipcRenderer.invoke("games:get", system);
  },
  launchGame: async (gameId: string): Promise<void> => {
    return ipcRenderer.invoke("game:launch", gameId);
  },
});
