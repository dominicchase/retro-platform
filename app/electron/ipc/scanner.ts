import path from "node:path";
import { ipcMain } from "electron";
import { GameScanner } from "../services/GameScanner";
import { GAMES_DIRECTORY } from "../config/paths";
import { Game, System } from "../shared/types";
import { GameRepository } from "../repositories/GameRepository";

export function registerScannerIpc() {
  const scanner = new GameScanner();
  const repository = new GameRepository();

  ipcMain.handle(
    "games:get",
    async (_event, system: System): Promise<Game[]> => {
      const gamesDirectory = path.join(GAMES_DIRECTORY, system);

      const games = scanner.scanDirectory(gamesDirectory, system);

      await repository.saveGames(await games);

      return games;
    },
  );
}
