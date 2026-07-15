import { app, BrowserWindow, ipcMain } from "electron";
import path from "node:path";
import { fileURLToPath } from "node:url";
import { GameScanner } from "./services/game-scanner";
import { System } from "../src/types/global";
import { registerRetroProtocol } from "./protocols/retroProtocol";

const __dirname = path.dirname(fileURLToPath(import.meta.url));
const scanner = new GameScanner();

function createWindow() {
  const mainWindow = new BrowserWindow({
    width: 1900,
    height: 1080,
    webPreferences: {
      preload: path.join(__dirname, "preload.mjs"),
      contextIsolation: true,
      nodeIntegration: false,
    },
  });

  if (process.env.VITE_DEV_SERVER_URL) {
    mainWindow.loadURL(process.env.VITE_DEV_SERVER_URL);
  } else {
    mainWindow.loadFile(path.join(__dirname, "..", "dist", "index.html"));
  }

  mainWindow.webContents.openDevTools();
}

ipcMain.handle("games:get", async (_event, system: System): Promise<Game[]> => {
  const gamesDirectory = path.join(
    __dirname,
    "..",
    "..",
    "data",
    "games",
    system,
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
