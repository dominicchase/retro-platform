import { GameRepository } from "../repositories/GameRepository";

export class GameLauncher {
  async launch(gameId: string): Promise<void> {
    const repository = new GameRepository();

    console.log(gameId);

    const game = await repository.getGame(gameId);

    console.log(game);

    // const game = await gameRepository.get(gameId);
    // switch (game.system) {
    //     case "SNES":
    //         return this.launchSnes(game);
    //     case "PS2":
    //         return this.launchPs2(game);
    // }
  }
}
