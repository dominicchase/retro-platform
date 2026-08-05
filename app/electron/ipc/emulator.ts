import { ipcMain } from "electron";
import { LibretroRunner } from "../services/LibretroRunner";

export function registerEmulatorIpc() {
  const runner = new LibretroRunner();

  ipcMain.handle("emulator:pause", async (): Promise<void> => {
    return runner.pause();
  });

  ipcMain.handle("emulator:resume", async (): Promise<void> => {
    return runner.resume();
  });

  ipcMain.handle("emulator:save", async (): Promise<void> => {
    return runner.save();
  });

  ipcMain.handle("emulator:load", async (): Promise<void> => {
    return runner.load();
  });
}
