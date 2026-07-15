import { ipcMain } from "electron";
import { GameLauncher } from "../services/GameLauncher";
import { GameRepository } from "../repositories/GameRepository";
import { CoreResolver } from "../services/CoreResolver";
import { LibretroRunner } from "../services/LibretroRunner";

export function registerLauncherIpc() {
  const launcher = new GameLauncher(
    new GameRepository(),
    new CoreResolver(),
    new LibretroRunner(),
  );

  ipcMain.handle(
    "game:launch",
    async (_event, gameId: string): Promise<void> => {
      return launcher.launch(gameId);
    },
  );
}
