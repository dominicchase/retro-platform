import { useEffect, useState } from "react";
import "./library.css";
import { Game } from "../../../electron/shared/types";

export function Library() {
  const [games, setGames] = useState<Game[]>([]);

  useGetGames();

  console.log("games: ", games);

  return (
    <div className="library">
      <div className="games-container">
        {games.map((game) => (
          <div className="game" key={game.id}>
            <h3 className="mb-3">{game.title}</h3>
            <h5 className="mb-4">{game.system}</h5>
            <img
              width={256}
              src={`retro://artwork/covers/${game.coverFile}`}
              onClick={() => launchGame(game.id)}
              alt={game.title}
            />
          </div>
        ))}
      </div>
    </div>
  );

  function useGetGames() {
    useEffect(() => {
      window.api.getGames("SNES").then((games) => {
        setGames(games);
      });
    }, []);
  }

  function launchGame(gameId: string) {
    window.api.launchGame(gameId);
  }
}
