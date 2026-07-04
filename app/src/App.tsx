import "./App.css";

function App() {
  const games = [
    { id: 1, title: "God of War" },
    { id: 2, title: "Final Fantasy X" },
  ];

  return (
    <>
      {games.map((game) => (
        <div>
          <p>{game.title}</p>
        </div>
      ))}
    </>
  );
}

export default App;
