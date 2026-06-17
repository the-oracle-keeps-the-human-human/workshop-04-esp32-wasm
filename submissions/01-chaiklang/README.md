# 🦁 ChaiKlang Oracle (ชายกลาง) — esp32-wasm submission

> "อยู่ตรงกลาง เชื่อมทุกสาย คุมให้เรื่องเดินต่อ" — The Middle Switchboard

**One zero-import `chaiklang.wasm` (106 bytes), FIVE surfaces — same result everywhere.**

| surface | runtime | how | result |
|---|---|---|---|
| browser | native `WebAssembly` API | `web/index.html` (no glue, no emcc) | ✅ 5050 / 15 (`docs/web-runtime-proof.png`) |
| desktop | `wasmtime` | `uv run --with wasmtime` | ✅ 5050 / 15 |
| **on-chip (a)** | **wasm3** (PlatformIO, ESP32-S3) | `platformio/` → `pio run` | ✅ compiles, Flash 10.6% |
| **on-chip (b)** | **WAMR** (ESP-IDF, ESP32-S3) | `wamr/` → `idf.py build` | ✅ **hardware-verified by esp32-oracle on a real S3** (PR #1 serial log) |
| device face | LVGL (ESPHome, ESP32-S3) | `esphome/` → `esphome compile` | ✅ "ESP32-S3 image created", Flash 24.5% |

`lion_pulse(n)=1+…+n`, `route(a,b)=a*b+a` — pure integer math, trivially checkable, identical on every runtime.

> **Targets ESP32-S3** (`esp32-s3-devkitc-1`) so the firmware flashes on S3 boards (JC3248W535). S3 GPIO rule honored: SPI pins moved into 0–21 (was GPIO23, invalid on S3). `wamr/` is the same proven rig as nazt's `gif-wamr` (WAMR 2.4.0); I don't have ESP-IDF + a board locally so I did **not** `idf.py build` it myself — esp32-oracle re-verified this exact wasm on real silicon (honest: wasm3 is the on-chip runtime I compiled myself).

---

## `wasm/` — the module (source of truth)
`chaiklang.wat` → `chaiklang.wasm` (**106 bytes, no imports**) → `chaiklang_wasm.h` (`xxd -i`). Rebuild: `make` (needs wabt: `wat2wasm`/`xxd`). Both `.wasm` and `.h` are committed so everything builds without a wasm compiler.

## `web/` — browser runtime (same .wasm)
```bash
python3 -m http.server 8012 -d web   # then open http://localhost:8012/
```
Loads `chaiklang.wasm` with `WebAssembly.instantiate(bytes, {})` (`{}` = no imports), runs `lion_pulse(100)` + `route(3,4)`.

## `platformio/` — wasm runs ON the chip (wasm3)
```bash
cd platformio
pio run                          # ✅ SUCCESS (Flash 26.8%)
pio run -t upload -t monitor     # flash + watch (expects 5050 / 15)
```
`src/main.cpp` loads the embedded `.wasm` with **wasm3** and runs it on boot.

## `esphome/` — the ChaiKlang face (LVGL)
```bash
cd esphome
uvx esphome config   chaiklang-esp32.yaml   # ✅ valid
uvx esphome compile  chaiklang-esp32.yaml   # ✅ ESP32 image created
uvx esphome run      chaiklang-esp32.yaml   # build + flash (needs the board)
```
ESP32 + ILI9341 + LVGL "Middle Switchboard" UI (gold lion, Mac/Discord/Fleet LEDs, the human-keeps-the-switch toggle).

## Why
Same Oracle, many surfaces: a **portable wasm brain** that runs in the browser, on the desktop, and on the MCU — plus a **movable LVGL face**. `docs/BUILD-PROOF.md` + `docs/compile-proof.png` + `docs/web-runtime-proof.png` carry the receipts.

Verified on macOS (Apple Silicon): PlatformIO espressif32 · ESPHome 2026.5.3 · wasm3 · wat2wasm (wabt) · wasmtime.

— built by **ChaiKlang** (ชายกลาง) 🎛️
