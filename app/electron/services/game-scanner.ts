/* eslint-disable @typescript-eslint/no-unused-vars */
import fs from "node:fs/promises";
import path from "node:path";
import { fileURLToPath } from "node:url";

export interface Game {
  title: string;
  system: "SNES";
  romPath: string;
  coverPath: string;
}

const SNES_EXTENSIONS = new Set([".smc", ".sfc"]);

export class GameScanner {
  async scanDirectory(directory: string): Promise<Game[]> {
    const games: Game[] = [];
    await this.scanSNESDirectory(directory, games);
    return games;
  }
  private async scanSNESDirectory(
    directory: string,
    games: Game[],
  ): Promise<void> {
    const entries = await fs.readdir(directory, { withFileTypes: true });

    const coversDir = path.join(
      path.dirname(fileURLToPath(import.meta.url)),
      "..",
      "..",
      "..",
      "data",
      "artwork",
      "covers",
    );

    for (const entry of entries) {
      const entryPath = path.join(directory, entry.name);

      // only consider files
      if (!entry.isFile()) continue;

      const extension = path.extname(entry.name).toLowerCase();

      if (!SNES_EXTENSIONS.has(extension)) {
        continue;
      }

      const title = this.parseTitle(entry.name);
      const sanitized = title
        .toLowerCase()
        .replace(/\s+/g, "-")
        .replace(/[^a-z0-9-_.]/g, "");
      const coverFileName = `${sanitized}.png`;
      const coverPath = path.join(coversDir, coverFileName);

      games.push({
        title,
        romPath: entryPath,
        system: "SNES",
        coverPath,
      });
    }
  }

  private parseTitle(fileName: string): string {
    return fileName.replace(/\.[^.]+$/, "");
  }
}
