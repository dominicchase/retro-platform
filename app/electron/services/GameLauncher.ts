import { GameRepository } from "../repositories/GameRepository";
import { CoreResolver } from "./CoreResolver";
import { LibretroRunner } from "./LibretroRunner";
import { Game } from "../shared/types";

export class GameLauncher {
  constructor(
    private repository: GameRepository,
    private core: CoreResolver,
    private libretro: LibretroRunner,
  ) {}

  async launch(gameId: string): Promise<void> {
    const game = await this.repository.getGame(gameId);

    if (!game) {
      throw Error(`Game ${gameId} not found`);
    }

    const core = this.core.getCore(game.system);

    console.log(core);
  }

  private async launchSnes(game: Game) {
    console.log(game);
  }
}
