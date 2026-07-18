import path from "node:path";

export const CORES_DIRECTORY = path.resolve(process.cwd(), "..", "cores");

export const DATA_DIRECTORY = path.resolve(process.cwd(), "..", "data");

export const GAMES_DIRECTORY = path.join(DATA_DIRECTORY, "games");
