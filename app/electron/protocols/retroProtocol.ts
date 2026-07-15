import { protocol } from "electron";
import path from "node:path";
import fs from "node:fs/promises";

export function registerRetroProtocol() {
  protocol.handle("retro", async (request) => {
    const url = new URL(request.url);
    const relativePath = path.join(url.hostname, url.pathname.slice(1));
    const filePath = path.join(process.cwd(), "..", "data", relativePath);
    const file = await fs.readFile(filePath);

    return new Response(file, {
      headers: {
        "Content-Type": "image/png",
      },
    });
  });
}
