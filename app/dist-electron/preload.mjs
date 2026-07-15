"use strict";
const electron = require("electron");
electron.contextBridge.exposeInMainWorld("api", {
  getGames: async (system) => {
    return electron.ipcRenderer.invoke("games:get", system);
  },
  launchGame: async (gameId) => {
    return electron.ipcRenderer.invoke("game:launch", gameId);
  }
});
