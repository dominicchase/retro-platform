import fs from "node:fs/promises";
import path from "node:path";

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

      const title = this.parseTitle(entry.name);
      const coverFile = this.createSlug(title) + ".png";

      games.push({
        title,
        // TODO: generalize system here
        system: "SNES",
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
}
