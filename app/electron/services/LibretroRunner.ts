import { spawn, ChildProcess } from "child_process";
import path from "path";

export class LibretroRunner {
  private process: ChildProcess | null = null;

  async launch(corePath: string | null, romPath: string): Promise<void> {
    if (!corePath) {
      throw new Error("Missing core path");
    }

    const executable = path.resolve(
      process.cwd(),
      "../native/libretro-runner/build/Debug/libretro-runner.exe",
    );

    console.log(`Launching emulator: ${executable}`);

    this.process = spawn(executable, [corePath, romPath], {
      cwd: path.dirname(executable),
    });

    this.process.stdout?.on("data", (data) => {
      console.log(`[libretro] ${data.toString()}`);
    });

    this.process.stderr?.on("data", (data) => {
      console.error(`[libretro error] ${data.toString()}`);
    });

    this.process.on("close", (code) => {
      console.log(`Emulator exited with code ${code}`);

      this.process = null;
    });
  }

  async pause(): Promise<void> {
    console.log("Pause emulator");
  }

  async resume(): Promise<void> {
    console.log("Resume emulator");
  }

  async save(): Promise<void> {
    console.log("Save state");
  }

  async load(): Promise<void> {
    console.log("Load state");
  }
}
