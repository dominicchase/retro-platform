import { ipcMain } from "electron";
import { GameLauncher } from "../services/GameLauncher";
import { GameRepository } from "../repositories/GameRepository";

export function registerLauncherIpc() {
  const launcher = new GameLauncher(new GameRepository());

  ipcMain.handle(
    "game:launch",
    async (_event, gameId: string): Promise<void> => {
      return launcher.launch(gameId);
    },
  );
}
