async function resolveRomUrl() {
  let res;

  try {
    res = await fetch("./rom.json", { cache: "no-store" });
  } catch (err) {
    throw {
      kind: "rom-json-missing",
      detail: `Failed to fetch ./rom.json (${err?.message ?? err})`
    };
  }

  if (!res.ok) {
    throw {
      kind: "rom-json-missing",
      detail: `./rom.json not found (HTTP ${res.status})`
    };
  }

  let data;
  try {
    data = await res.json();
  } catch {
    throw {
      kind: "rom-json-invalid",
      detail: "./rom.json exists but is not valid JSON"
    };
  }

  const rom = data?.rom;
  if (typeof rom !== "string" || rom.trim() === "") {
    throw {
      kind: "rom-json-invalid",
      detail: 'Expected: { "rom": "your-game.gba" }'
    };
  }

  const romPath = rom.startsWith("./") ? rom : `./${rom}`;

  const romCheck = await fetch(romPath, { method: "HEAD", cache: "no-store" });
  if (!romCheck.ok) {
    throw {
      kind: "rom-missing",
      detail: `ROM file ${romPath} not found (HTTP ${romCheck.status})`
    };
  }

  return romPath + "?v=" + String(Date.now());
}

function showErrorOnPage(title, message) {
  const box = document.createElement("div");
  box.style.maxWidth = "800px";
  box.style.padding = "20px";
  box.style.background = "#1e1e1e";
  box.style.color = "#eee";
  box.style.border = "1px solid #444";
  box.style.borderRadius = "6px";
  box.style.fontFamily = "system-ui, sans-serif";

  const h = document.createElement("h2");
  h.textContent = title;

  const p = document.createElement("p");
  p.textContent = message;

  const hint = document.createElement("pre");
  hint.textContent =
`What to check:
• Did the project compile successfully?
• Are there errors in the GitHub Actions / build logs?
• Was a .gba file produced?

If the build failed, the ROM will not exist.`;
  hint.style.background = "#111";
  hint.style.padding = "12px";
  hint.style.borderRadius = "4px";
  hint.style.whiteSpace = "pre-wrap";

  box.appendChild(h);
  box.appendChild(p);
  box.appendChild(hint);

  document.body.prepend(box);
}

function configureAndLoadEmulator(romUrl) {
  window.EJS_player = "#game";
  window.EJS_core = "gba";
  window.EJS_gameUrl = romUrl;
  window.EJS_gameName = "game";
  window.EJS_pathtodata = "https://cdn.emulatorjs.org/4.2.3/data/";
  window.EJS_startOnLoaded = true;
  window.EJS_disableDatabases = true;
  window.EJS_DEBUG_XX = true;

  const s = document.createElement("script");
  s.src = "https://cdn.emulatorjs.org/4.2.3/data/loader.js";
  document.head.appendChild(s);
}

async function startFromButton() {
  const btn = document.getElementById("start");
  if (btn) {
    btn.disabled = true;
    btn.textContent = "Loading…";
  }

  let romUrl;
  try {
    romUrl = await resolveRomUrl();
  } catch (err) {
    console.error("[Emulator startup failed]", err);

    if (err.kind === "rom-json-missing" || err.kind === "rom-json-invalid") {
      showErrorOnPage(
        "Game could not be started",
        "The emulator could not find rom.json, or it is invalid. Check the build logs for compilation errors."
      );
    } else if (err.kind === "rom-missing") {
      showErrorOnPage(
        "Game could not be started",
        "The ROM file listed in rom.json could not be found. Check the build logs for compilation errors."
      );
    } else {
      showErrorOnPage(
        "Game could not be started",
        "An unexpected error occurred while loading the game. Check the build logs for compilation errors."
      );
    }

    if (btn) {
      btn.disabled = false;
      btn.textContent = "Start";
    }
    return;
  }

  // Remove the button (optional) and start emulator
  btn?.remove();
  configureAndLoadEmulator(romUrl);
}

document.addEventListener("DOMContentLoaded", () => {
  const btn = document.getElementById("start");
  if (!btn) {
    showErrorOnPage("Setup error", "Missing Start button with id=\"start\".");
    return;
  }
  btn.addEventListener("click", startFromButton, { once: true });
});
