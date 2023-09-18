
import ffmpeg from "fluent-ffmpeg";

export default function ffmpegExport() {
//   const ffmpeg = require("fluent-ffmpeg");
  let track = "./audio.mp3"; //your path to source file

  ffmpeg(track)
    .toFormat("flac")
    .on("error", (err:any) => {
      console.log("An error occurred: " + err.message);
    })
    .on("progress", (progress:any) => {
      // console.log(JSON.stringify(progress));
      console.log("Processing: " + progress.targetSize + " KB converted");
    })
    .on("end", () => {
      console.log("Processing finished !");
    })
    .save("./hello.flac"); //path where you want to save your file
}
