"use strict";
const electron = require("electron");
electron.contextBridge.exposeInMainWorld("api", {
  getSNESGames: async () => {
    return electron.ipcRenderer.invoke("snes:games:get");
  }
});
