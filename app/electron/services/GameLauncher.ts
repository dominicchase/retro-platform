import { GameRepository } from "../repositories/GameRepository";
import { Game } from "../shared/types";

export class GameLauncher {
  constructor(private repository: GameRepository) {}

  async launch(gameId: string): Promise<void> {
    const game = await this.repository.getGame(gameId);

    if (!game) {
      throw Error(`Game ${gameId} not found`);
    }

    switch (game.system) {
      case "SNES":
        return this.launchSnes(game);
      default:
        break;
    }
  }

  private async launchSnes(game: Game) {
    console.log(game);
  }
}
