import "./App.css";
import src from "../../data/artwork/covers/chrono-trigger.jpg";

function App() {
  const games = [
    { id: 1, title: "Chrono Trigger", cover: "chrono-trigger.jpg" },
  ];

  return (
    <>
      {games.map((game) => (
        <div>
          <img
            width={400}
            src={src}
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
