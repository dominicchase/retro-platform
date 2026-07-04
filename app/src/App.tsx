import "./App.css";

function App() {
  const games = [{ id: 1, title: "Dark Cloud" }];

  return (
    <>
      {games.map((game) => (
        <div>
          <button onClick={() => launchGame(game.title)}>{game.title}</button>
        </div>
      ))}
    </>
  );

  function launchGame(gameTitle: string) {
    window.electronAPI.launchGame(
      `C:\\GitHub\\retro-platform\\games\\${gameTitle}.iso`,
    );
  }
}

export default App;
