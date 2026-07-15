import path from "node:path";

export const DATA_DIRECTORY = path.resolve(process.cwd(), "..", "data");

export const GAMES_DIRECTORY = path.join(DATA_DIRECTORY, "games");
