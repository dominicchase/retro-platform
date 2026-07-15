/* eslint-disable @typescript-eslint/no-unused-vars */
export class GameLauncher {
  async launch(gameId: string): Promise<void> {
    console.log(gameId);
    // const game = await gameRepository.get(gameId);
    // switch (game.system) {
    //     case "SNES":
    //         return this.launchSnes(game);
    //     case "PS2":
    //         return this.launchPs2(game);
    // }
  }
}
