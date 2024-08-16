import { useState } from "react";
import reactLogo from "./assets/react.svg";
import viteLogo from "/vite.svg";
import useWebSocket from "react-use-websocket";
import "./App.css";

const WS_URL = "ws://172.20.10.2/ws";

function App() {
  const [count, setCount] = useState(0);
  const [distance, setDistance] = useState(0);
  const { sendMessage } = useWebSocket(WS_URL, {
    onOpen: () => {
      console.log("WebSocket connection established.");
    },
    onMessage: (message) => {
      setDistance(message.data);
    },
  });

  return (
    <>
      <div>
        <a href="https://vitejs.dev" target="_blank">
          <img src={viteLogo} className="logo" alt="Vite logo" />
        </a>
        <a href="https://react.dev" target="_blank">
          <img src={reactLogo} className="logo react" alt="React logo" />
        </a>
      </div>
      <h1>Distance: {distance}cm</h1>
      <div className="card">
        <button
          onClick={() => {
            sendMessage(`0${count % 2}`);
            setCount((count) => count + 1);
          }}
        >
          count is {count}
        </button>
        <p>
          Edit <code>src/App.tsx</code> and save to test HMR
        </p>
      </div>
      <p className="read-the-docs">
        Click on the Vite and React logos to learn more
      </p>
    </>
  );
}

export default App;
