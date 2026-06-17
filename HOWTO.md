# 🛠️ How to submit to the ESP32-WASM workshop

> Goal: build a tiny **`.wasm` that runs ON an ESP32**, prove it **compiles with both build systems**, open a PR. No hardware needed to *build* — only to *flash*.

---

## 0. Install the tools (once)

You only need [`uv`](https://docs.astral.sh/uv/) + **one** wasm compiler.

```bash
# uv gives you uvx (runs esphome + platformio with zero global installs)
curl -LsSf https://astral.sh/uv/install.sh | sh

# pick ONE way to make a .wasm:
brew install wabt     # wat2wasm — hand-write WebAssembly text   (used by 01-chaiklang)
brew install zig      # zig      — compile C → freestanding wasm (used by 02-esp32-oracle)
# or emscripten (emcc) if you already have it — for the browser build
```

That's it. `uvx esphome` and `uvx platformio` download everything else on first run.

---

## 1. Fork & clone

```bash
gh repo fork the-oracle-keeps-the-human-human/workshop-04-esp32-wasm --clone
cd workshop-04-esp32-wasm
git checkout -b submit-<yourname>
```

## 2. Make your folder (running number, one per person)

```
submissions/
└── NN-<yourname>/
    ├── wasm/         # your .wasm module + how it's built
    ├── platformio/   # wasm runs ON the chip (wasm3)  → pio run
    ├── esphome/      # the device's face (LVGL)        → uvx esphome compile
    └── README.md
```

## 3. Write your wasm — keep it ZERO imports

Zero imports = it loads cleanly under wasm3 (and WAMR) on the chip. Export 1–2 **pure** functions so the result is identical everywhere and easy to check.

**Option A — hand-written WAT** (smallest, no compiler logic):
```wat
(module
  (func $add (export "add") (param i32 i32) (result i32)
    (i32.add (local.get 0) (local.get 1))))
```
```bash
wat2wasm mymod.wat -o mymod.wasm
```

**Option B — C compiled with zig** (write real C):
```c
__attribute__((export_name("add")))
int add(int a, int b) { return a + b; }
```
```bash
zig build-exe mymod.c -target wasm32-freestanding -O ReleaseSmall -fno-entry -rdynamic
# → mymod.wasm   (a few hundred bytes, no imports)
```

## 4. Embed the wasm into firmware

```bash
xxd -i mymod.wasm > mymod_wasm.h     # gives  unsigned char mymod_wasm[]  +  ..._len
```
Commit both `mymod.wasm` and `mymod_wasm.h` so it builds without your wasm compiler.

## 5. `platformio/` — run the wasm ON the chip (wasm3)

`platformio.ini`:
```ini
[env:esp32dev]
platform = espressif32
board = esp32dev
framework = arduino
monitor_speed = 115200
lib_deps = wasm3/Wasm3@^0.5.0
build_flags = -Dd_m3HasWASI=0 -Dd_m3HasTracer=0
```
`src/main.cpp` (the pattern: parse → load → find function → call → print):
```cpp
#include <Arduino.h>
#include "wasm3.h"
#include "mymod_wasm.h"
void setup() {
  Serial.begin(115200); delay(600);
  IM3Environment env = m3_NewEnvironment();
  IM3Runtime rt = m3_NewRuntime(env, 8*1024, NULL);
  IM3Module mod; m3_ParseModule(env, &mod, mymod_wasm, mymod_wasm_len);
  m3_LoadModule(rt, mod);
  IM3Function f; m3_FindFunction(&f, rt, "add");
  m3_CallV(f, (uint32_t)2, (uint32_t)3);
  uint32_t out = 0; m3_GetResultsV(f, &out);
  Serial.printf("add(2,3) = %u (expect 5)\n", out);
}
void loop(){ delay(2000); }
```
**Verify:**
```bash
cd platformio && uvx --from platformio platformio run     # must end with [SUCCESS]
```

## 6. `esphome/` — the device's face (LVGL)

A declarative ESP32 + display UI. Minimal skeleton — see `01-chaiklang` / `02-esp32-oracle` for a full LVGL page.
```yaml
esphome:
  name: myface
esp32:
  board: esp32dev
  framework: { type: esp-idf }
logger:
# ... spi + display + lvgl pages (copy from an example) ...
```
**Verify:**
```bash
cd esphome && uvx esphome compile myface.yaml              # must end with "Successfully compiled"
```

## 7. ✅ The bar — BOTH must compile

```bash
cd platformio && uvx --from platformio platformio run      # [SUCCESS]
cd ../esphome  && uvx esphome compile *.yaml               # Successfully compiled
```
> A reviewer bot checks out your PR, compiles **every** target, and only approves if compile passes — and (bonus) hardware-verifies the `.wasm` under WAMR on a real ESP32-S3. So make sure it's green before you open the PR.

## 8. Write your README + proof

`README.md`: what your wasm does, the two build commands, and the expected output (e.g. `add(2,3)=5`). Optional `docs/BUILD-PROOF.md` with sizes + sha256 scores points.

## 9. Commit & open the PR

```bash
git add submissions/NN-<yourname>
git commit -m "submit(<yourname>): wasm-on-esp32"
git push -u origin submit-<yourname>
gh pr create --base main --fill
```

---

## 📚 Copy from these worked examples
- **`submissions/01-chaiklang/`** — WAT → wat2wasm → wasm3 + an ESPHome LVGL face. The minimal path.
- **`submissions/02-esp32-oracle/`** — one C core → **4 runtimes** (emcc browser + zig + wasm3 + WAMR-on-hardware) + ESPHome. The "go deep" path; see its `docs/BUILD-PROOF.md`.

## ❓ Common gotchas
- **Module won't load on-chip?** Your wasm has imports. Rebuild with no imports (freestanding / no WASI).
- **`pio run` first-run error** about a build path? Run it once more — the cold cache sometimes trips, the warm run succeeds.
- **`xxd` symbol name** must match your `#include` (filename `mymod.wasm` → `mymod_wasm[]`).
- You **don't need a board to build** — only to flash. Submit on compile-pass alone.

Happy hacking 🕯️ — *one wasm, many runtimes.*
