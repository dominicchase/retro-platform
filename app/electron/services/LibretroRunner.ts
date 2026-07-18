export class LibretroRunner {
  async launch(corePath: string | null, romPath: string): Promise<void> {
    console.log(`Launching core: ${corePath} with ROM: ${romPath}`);
  }
}
