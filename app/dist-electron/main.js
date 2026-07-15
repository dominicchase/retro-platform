import { protocol, ipcMain, app, BrowserWindow } from "electron";
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
      const coverFile = this.createSlug(title) + ".png";
      games.push({
        title,
        // TODO: generalize system here
        system: "SNES",
        romPath: entryPath,
        coverFile
      });
    }
  }
  parseTitle(fileName) {
    return fileName.replace(/\.[^.]+$/, "");
  }
  createSlug(title) {
    return title.toLowerCase().replace(/[^a-z0-9]+/g, "-").replace(/^-+|-+$/g, "");
  }
}
function registerRetroProtocol() {
  protocol.handle("retro", async (request) => {
    const url = new URL(request.url);
    const relativePath = path.join(url.hostname, url.pathname.slice(1));
    const filePath = path.join(process.cwd(), "..", "data", relativePath);
    const file = await fs.readFile(filePath);
    return new Response(file, {
      headers: {
        "Content-Type": "image/png"
      }
    });
  });
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
app.whenReady().then(() => {
  registerRetroProtocol();
  createWindow();
});
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
