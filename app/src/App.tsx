import "./App.css";
import { useEffect, useState } from "react";

function App() {
  const [games, setGames] = useState<Game[]>([]);

  useEffect(() => {
    window.api.getGames("SNES").then((games) => {
      setGames(games);
    });
  }, []);

  return (
    <>
      {games.map((game) => (
        <div>
          <h3>{game.title}</h3>
          <h5>{game.system}</h5>
          <img
            width={400}
            src={`retro://covers/${game.coverFile}`}
            onClick={() => launchGame(game.title)}
            alt={game.title}
          />
        </div>
      ))}
    </>
  );

  function launchGame(gameTitle: string) {
    console.log(gameTitle);
    // window.electronAPI.launchGame(
    //   `C:\\GitHub\\retro-platform\\games\\${gameTitle}.iso`,
    // );
  }
}

export default App;
