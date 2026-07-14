import { contextBridge, ipcRenderer } from "electron";
import type { Game } from "./services/game-scanner";

contextBridge.exposeInMainWorld("api", {
  getSNESGames: async (): Promise<Game[]> => {
    return ipcRenderer.invoke("snes:games:get");
  },
});
