import { ipcMain, app, BrowserWindow } from "electron";
import path from "node:path";
import { fileURLToPath } from "node:url";
import fs from "node:fs/promises";
const SNES_EXTENSIONS = /* @__PURE__ */ new Set([".smc", ".sfc"]);
class GameScanner {
  async scanDirectory(directory) {
    const games = [];
    await this.scanSNESDirectory(directory, games);
    return games;
  }
  async scanSNESDirectory(directory, games) {
    const entries = await fs.readdir(directory, { withFileTypes: true });
    const coversDir = path.join(
      path.dirname(fileURLToPath(import.meta.url)),
      "..",
      "..",
      "..",
      "data",
      "artwork",
      "covers"
    );
    for (const entry of entries) {
      const entryPath = path.join(directory, entry.name);
      if (!entry.isFile()) continue;
      const extension = path.extname(entry.name).toLowerCase();
      if (!SNES_EXTENSIONS.has(extension)) {
        continue;
      }
      const title = this.parseTitle(entry.name);
      const sanitized = title.toLowerCase().replace(/\s+/g, "-").replace(/[^a-z0-9-_.]/g, "");
      const coverFileName = `${sanitized}.png`;
      const coverPath = path.join(coversDir, coverFileName);
      games.push({
        title,
        romPath: entryPath,
        system: "SNES",
        coverPath
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
ipcMain.handle("snes:games:get", async () => {
  const gamesDirectory = path.join(
    __dirname$1,
    "..",
    "..",
    "data",
    "games",
    "SNES"
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
