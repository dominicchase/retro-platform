var __defProp = Object.defineProperty;
var __defNormalProp = (obj, key, value) => key in obj ? __defProp(obj, key, { enumerable: true, configurable: true, writable: true, value }) : obj[key] = value;
var __publicField = (obj, key, value) => __defNormalProp(obj, typeof key !== "symbol" ? key + "" : key, value);
import { protocol, ipcMain, app, BrowserWindow } from "electron";
import path from "node:path";
import { fileURLToPath } from "node:url";
import fs from "node:fs/promises";
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
      const system = path.basename(directory);
      const id = this.createGameId(system, entry.name);
      const title = this.parseTitle(entry.name);
      const coverFile = this.createSlug(title) + ".png";
      games.push({
        id,
        title,
        system,
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
  //   TODO: eventually move to hashed IDs or something else
  createGameId(system, filename) {
    const name = path.parse(filename).name;
    const slug = name.toLowerCase().replace(/[^a-z0-9]+/g, "-").replace(/^-|-$/g, "");
    return `${system.toLowerCase()}-${slug}`;
  }
}
const DATA_DIRECTORY = path.resolve(process.cwd(), "..", "data");
const GAMES_DIRECTORY = path.join(DATA_DIRECTORY, "games");
class GameRepository {
  constructor() {
    __publicField(this, "gamesFile", path.join(DATA_DIRECTORY, "games.json"));
  }
  async getGames() {
    const data = await fs.readFile(this.gamesFile, "utf-8");
    return JSON.parse(data);
  }
  async getGame(gameId) {
    const games = await this.getGames();
    return games.find((game) => game.id === gameId);
  }
  async saveGames(games) {
    await fs.writeFile(this.gamesFile, JSON.stringify(games));
  }
}
function registerScannerIpc() {
  const scanner = new GameScanner();
  const repository = new GameRepository();
  ipcMain.handle(
    "games:get",
    async (_event, system) => {
      const gamesDirectory = path.join(GAMES_DIRECTORY, system);
      const games = scanner.scanDirectory(gamesDirectory);
      await repository.saveGames(await games);
      return games;
    }
  );
}
class GameLauncher {
  async launch(gameId) {
    const repository = new GameRepository();
    console.log(gameId);
    const game = await repository.getGame(gameId);
    console.log(game);
  }
}
function registerLauncherIpc() {
  const launcher = new GameLauncher();
  ipcMain.handle(
    "game:launch",
    async (_event, gameId) => {
      return launcher.launch(gameId);
    }
  );
}
function registerIpcHandlers() {
  registerScannerIpc();
  registerLauncherIpc();
}
const __dirname$1 = path.dirname(fileURLToPath(import.meta.url));
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
app.whenReady().then(() => {
  registerRetroProtocol();
  registerIpcHandlers();
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
