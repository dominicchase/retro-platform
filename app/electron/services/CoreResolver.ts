import { Core, System } from "../shared/types";

export class CoreResolver {
  async getCore(system: System): Promise<Core | null> {
    switch (system) {
      case "SNES":
        return "snes9x";

      default:
        return null;
    }
  }
}
