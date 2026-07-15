import { useEffect, useState } from "react";
import "./library.css";

export function Library() {
  const [games, setGames] = useState<Game[]>([]);

  useGetGames();

  return (
    <div className="library">
      <div className="games-container">
        {games.map((game) => (
          <div className="game">
            <h3 className="mb-3">{game.title}</h3>
            <h5 className="mb-4">{game.system}</h5>
            <img
              width={256}
              src={`retro://artwork/covers/${game.coverFile}`}
              onClick={() => launchGame(game.title)}
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

  function launchGame(gameTitle: string) {
    console.log(gameTitle);
    // window.electronAPI.launchGame(
    //   `C:\\GitHub\\retro-platform\\games\\${gameTitle}.iso`,
    // );
  }
}
