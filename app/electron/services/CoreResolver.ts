import { Core, System } from "../shared/types";
import { CORES_DIRECTORY } from "../config/paths";

export class CoreResolver {
  getCore(system: System): Core | null {
    switch (system) {
      case "SNES":
        return "snes9x";

      default:
        return null;
    }
  }

  getCorePath(system: System): string | null {
    console.log(CORES_DIRECTORY);

    switch (system) {
      case "SNES":
        return `${CORES_DIRECTORY}/snes9x_libretro.dll`;
      default:
        return null;
    }
  }
}
