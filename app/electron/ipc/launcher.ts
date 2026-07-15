import { ipcMain } from "electron";
import { GameLauncher } from "../services/game-launcher";

export function registerLauncherIpc() {
  const launcher = new GameLauncher();

  ipcMain.handle(
    "game:launch",
    async (_event, gameId: string): Promise<void> => {
      return launcher.launch(gameId);
    },
  );
}
