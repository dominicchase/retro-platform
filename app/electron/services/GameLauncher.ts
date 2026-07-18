import { GameRepository } from "../repositories/GameRepository";
import { CoreResolver } from "./CoreResolver";
import { LibretroRunner } from "./LibretroRunner";

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

    const corePath = this.core.getCorePath(game.system);

    this.launchSnes(corePath, game.romPath);
  }

  private async launchSnes(
    corePath: string | null,
    romPath: string,
  ): Promise<void> {
    this.libretro.launch(corePath, romPath);
  }
}
