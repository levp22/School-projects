import { useState, useEffect } from "react";
import { useTimer } from "react-timer-hook";
import IconButton from "@material-ui/core/IconButton";
import PlayCircleIcon from "@mui/icons-material/PlayCircle";
import RestartAltIcon from "@mui/icons-material/RestartAlt";
import CheckCircleOutlineIcon from "@mui/icons-material/CheckCircleOutline";

import parseBackend from "../../utils/axios-utils";

function MyTimer({ expiryTimestamp }: any) {
  const { seconds, minutes, hours, days, start, pause, restart } =
    useTimer({
      autoStart: false,
      expiryTimestamp,
      onExpire: () => console.warn("onExpire called"),
    });
  // State true = play
  // State false = pause

  const [state, setState] = useState(false);

  console.log(state);

  // FinishState false = not finished
  // FinishState true = finished
  const [finishState, setFinishState] = useState(false);

  const toggleState = () => {
    
    setState((state) => {
      if (state) {
        pause();
      } else {
        start();
      }
      return !state;
    });
  };

  const pauseTimer = () => {
    setState((state) => {
      if (state){
        pause();
      }
      return false;
  });
  }

  const setFinishStateTrue = () => {
    setFinishState(true);
    pauseTimer();
  };

  useEffect(() => {
    parseBackend
      .get("/")
      .then((response) => response.data)
      .then((data) => {
        console.log(data);
      })
      .catch((e) => {
        console.log(e);
      });
  }, [finishState]);

  return (
    <div className="title" style={{ textAlign: "center" }}>
      <h1>Parlé</h1>

      <div style={{ fontSize: "100px" }} className="clock">
        <span>{days}</span>:<span>{hours}</span>:<span>{minutes}</span>:
        <span>{seconds}</span>
      </div>

      <IconButton onClick={toggleState}>
        <PlayCircleIcon />
      </IconButton>

      <IconButton
        onClick={() => {
          const time = new Date();
          time.setSeconds(time.getSeconds() + 600);
          setFinishState(false);
          restart(time, false);
          pauseTimer();

        }}
      >
        <RestartAltIcon />
      </IconButton>

      <IconButton onClick={setFinishStateTrue}>
        <CheckCircleOutlineIcon />
      </IconButton>
    </div>
  );
}

export default function Countup() {
  const time = new Date();
  time.setSeconds(time.getSeconds() + 600); // 10 minutes timer
  return (
    <div>
      <MyTimer expiryTimestamp={time} />
    </div>
  );
}
