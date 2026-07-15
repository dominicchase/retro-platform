import { Core, System } from "../shared/types";

export class CoreResolver {
  getCore(system: System): Core | null {
    switch (system) {
      case "SNES":
        return "snes9x";

      default:
        return null;
    }
  }
}
