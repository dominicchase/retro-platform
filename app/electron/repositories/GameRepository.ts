import path from "node:path";
import fs from "node:fs/promises";
import { Game } from "../shared/types";
import { DATA_DIRECTORY } from "../config/paths";

export class GameRepository {
  private gamesFile = path.join(DATA_DIRECTORY, "games.json");

  async getGames(): Promise<Game[]> {
    const data = await fs.readFile(this.gamesFile, "utf-8");
    return JSON.parse(data);
  }

  async getGame(gameId: string): Promise<Game | undefined> {
    const games = await this.getGames();
    return games.find((game) => game.id === gameId);
  }

  async saveGames(games: Game[]): Promise<void> {
    await fs.writeFile(this.gamesFile, JSON.stringify(games));
  }
}
