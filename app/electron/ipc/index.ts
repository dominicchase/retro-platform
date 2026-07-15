import { registerScannerIpc } from "./scanner";
import { registerLauncherIpc } from "./launcher";

export function registerIpcHandlers() {
  registerScannerIpc();
  registerLauncherIpc();
}
