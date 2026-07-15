import { ipcMain, app, BrowserWindow } from "electron";
import path from "node:path";
import { fileURLToPath } from "node:url";
import fs from "node:fs/promises";
class GameScanner {
  async scanDirectory(directory) {
    const games = [];
    await this.scanSystemDirectory(directory, games);
    return games;
  }
  async scanSystemDirectory(directory, games) {
    const entries = await fs.readdir(directory, { withFileTypes: true });
    for (const entry of entries) {
      const entryPath = path.join(directory, entry.name);
      if (!entry.isFile()) continue;
      const title = this.parseTitle(entry.name);
      const coverFile = title.toLowerCase().replace(" ", "-") + ".png";
      games.push({
        title,
        system: "SNES",
        romPath: entryPath,
        coverFile
      });
    }
  }
  parseTitle(fileName) {
    return fileName.replace(/\.[^.]+$/, "");
  }
}
const __dirname$1 = path.dirname(fileURLToPath(import.meta.url));
const scanner = new GameScanner();
function createWindow() {
  const mainWindow = new BrowserWindow({
    width: 1900,
    height: 1080,
    webPreferences: {
      preload: path.join(__dirname$1, "preload.mjs"),
      contextIsolation: true,
      nodeIntegration: false
    }
  });
  if (process.env.VITE_DEV_SERVER_URL) {
    mainWindow.loadURL(process.env.VITE_DEV_SERVER_URL);
  } else {
    mainWindow.loadFile(path.join(__dirname$1, "..", "dist", "index.html"));
  }
  mainWindow.webContents.openDevTools();
}
ipcMain.handle("games:get", async (_event, system) => {
  const gamesDirectory = path.join(
    __dirname$1,
    "..",
    "..",
    "data",
    "games",
    system
  );
  return scanner.scanDirectory(gamesDirectory);
});
app.whenReady().then(createWindow);
app.on("window-all-closed", () => {
  if (process.platform !== "darwin") {
    app.quit();
  }
});
app.on("activate", () => {
  if (BrowserWindow.getAllWindows().length === 0) {
    createWindow();
  }
});
