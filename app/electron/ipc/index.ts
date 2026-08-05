import { registerScannerIpc } from "./scanner";
import { registerLauncherIpc } from "./launcher";
import { registerEmulatorIpc } from "./emulator";

export function registerIpcHandlers() {
  registerScannerIpc();
  registerLauncherIpc();
  registerEmulatorIpc();
}
