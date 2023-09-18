// Taken and inspired from https://medium.com/front-end-weekly/recording-audio-in-mp3-using-reactjs-under-5-minutes-5e960defaf10

import { Button, ButtonGroup, Box } from "@mui/material";
import parseBackend from "../../utils/axios-utils";
import { useState } from "react";

export function Sound() {
  const MicRecorder = require("mic-recorder-to-mp3");
  const [parleData, setParleData] = useState('');

  // New instance
  const recorder = new MicRecorder({
    bitRate: 128,
  });
  const startRecording = () => {
    // Start recording. Browser will request permission to use your microphone.
    recorder
      .start()
      .then(() => {
        // something else
      })
      .catch((e: any) => {
        console.error(e);
      });
  };

  const stopRecording = () => {
    // Once you are done singing your best song, stop and get the mp3.
    recorder
      .stop()
      .getMp3()
      .then(([buffer, blob]: any) => {
        // do what ever you want with buffer and blob
        // Example: Create a mp3 file and play
        const file = new File(buffer, "audio.mp3", {
          type: blob.type,
          lastModified: Date.now(),
        });

        var FileSaver = require("file-saver");

        FileSaver.saveAs(file, "audio.mp3");

        const player = new Audio(URL.createObjectURL(file));
        player.play();

        mockDataReturn();
      })
      .catch((e: any) => {
        alert("We could not retrieve your message");
        console.log(e);
      });

    const mockDataReturn = () => {
      parseBackend
        .post("/parle-score")
        .then((response) => response.data)
        .then(data => {
            setParleData(JSON.stringify(data));
        })
        .then((data) => {
            console.log(data)
        })
        .catch((e) => {
          console.log(e);
        });
    };
  };

  return (
    <div>
      <Box
        sx={{
          display: "flex",
          flexDirection: "column",
          alignItems: "center",
          "& > *": {
            m: 1,
          },
        }}
      >
        <ButtonGroup variant="text" aria-label="text button group">
          <Button onClick={startRecording}>Start Recording</Button>
          <Button onClick={stopRecording}>Stop Recording</Button>
        </ButtonGroup>
      </Box>

      <span style={{ textAlign: "center" }}>
        <textarea rows={15} cols={60} name="description">
          Enter presentation script here...
        </textarea>
      </span>

      <span style={{ textAlign: "center" }}>
        <textarea rows={15} cols={60} name="description" value={parleData ? parleData : ''}>
        </textarea>
      </span>

      <h3>Presentation Score:</h3>
      
    </div>
  );
}
