import fs from "node:fs/promises";
import path from "node:path";
import { System } from "../../src/types/global";

export class GameScanner {
  async scanDirectory(directory: string): Promise<Game[]> {
    const games: Game[] = [];
    await this.scanSystemDirectory(directory, games);
    return games;
  }

  private async scanSystemDirectory(
    directory: string,
    games: Game[],
  ): Promise<void> {
    const entries = await fs.readdir(directory, { withFileTypes: true });

    for (const entry of entries) {
      const entryPath = path.join(directory, entry.name);

      if (!entry.isFile()) continue;

      const system = path.basename(directory) as System;
      const id = this.createGameId(system, entry.name);
      const title = this.parseTitle(entry.name);
      const coverFile = this.createSlug(title) + ".png";

      games.push({
        id,
        title,
        system,
        romPath: entryPath,
        coverFile,
      });
    }
  }

  private parseTitle(fileName: string): string {
    return fileName.replace(/\.[^.]+$/, "");
  }

  private createSlug(title: string) {
    return title
      .toLowerCase()
      .replace(/[^a-z0-9]+/g, "-")
      .replace(/^-+|-+$/g, "");
  }

  //   TODO: eventually move to hashed IDs or something else
  private createGameId(system: System, filename: string) {
    const name = path.parse(filename).name;

    const slug = name
      .toLowerCase()
      .replace(/[^a-z0-9]+/g, "-")
      .replace(/^-|-$/g, "");

    return `${system.toLowerCase()}-${slug}`;
  }
}
