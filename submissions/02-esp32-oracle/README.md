# 🕯️ ESP32 Oracle — The Sentinel — esp32-wasm submission

> "Small body on the edge of the network, awake when nothing else is, keeping the flame in 4 MB of flash."

One tiny `.wasm` core (`wasm/sentinel.c`), the same module running in **four** places —
browser, desktop, and **on the ESP32 itself two different ways**:

| where | runtime | how |
|---|---|---|
| browser | emcc / WebAssembly | `wasm/web/sentinel.js` (a `<canvas>`-free library, exports `flame`/`sense`) |
| desktop | zig `wasm32-freestanding` | the same `sentinel.wasm`, no imports → loadable by any runtime |
| **on-chip (a)** | **wasm3** (PlatformIO) | `platformio/` — embeds `sentinel.wasm`, runs it on boot |
| **on-chip (b)** | **WAMR** (ESP-IDF) | hardware-verified on a real **ESP32-S3** — see `docs/BUILD-PROOF.md` |

The module exports two pure-integer functions so the result is identical on every runtime and trivial to verify:

- `flame(n)` = 1² + 2² + … + n²  — the keep-the-flame heartbeat (a real loop with multiply+accumulate). `flame(10) = 385`
- `sense(a,b)` = a² + b²  — the edge-sense magnitude (the 3-4-5 sentinel). `sense(3,4) = 25`

`flame(n)` intentionally returns a signed 32-bit integer for the smallest possible
guest ABI across wasm3 and WAMR. Use `0 <= n <= 1860` for overflow-free results
(`flame(1860)=2146682110`; `flame(1861)` exceeds `INT32_MAX`).

## `wasm/` — one core, three outputs
```bash
cd wasm
make            # sentinel.wasm (zig, no imports) + sentinel_wasm.h (xxd -i)  → what PlatformIO embeds
make web        # web/sentinel.{js,wasm} (emcc) → the browser build
make verify     # asserts flame(10)=385 and sense(3,4)=25 via wasmtime
```
`sentinel.c` is compiled to a **wasm32-freestanding** module with `zig` — zero imports, so it
loads cleanly under wasm3 and WAMR on the chip. No `wat2wasm`/WAT hand-assembly needed.
The prebuilt `sentinel.wasm` + `sentinel_wasm.h` are committed so the firmware builds without zig.

## `platformio/` — wasm runs **on the chip** (wasm3)
The point of the workshop: a `.wasm` executing on the ESP32 itself.
```bash
cd platformio
pio run                       # compile ESP32 firmware  ✅
pio run -t upload -t monitor  # flash + watch (expects flame(10)=385, sense(3,4)=25)
```
`src/main.cpp` loads the embedded `sentinel_wasm.h` with **wasm3** and runs both exports on boot,
printing over serial.

## `esphome/` — the Sentinel face (LVGL)
A declarative ESP32 + ILI9341 display showing the Sentinel UI (flame-gold title, the flame / edge-sense /
wasm-on-chip status LEDs) — palette matched to the esp32-oracle identity (flame `#F0B429`, edge `#3AD6E0`).
```bash
cd esphome
uvx esphome config   sentinel-esp32.yaml   # ✅ Configuration is valid!
uvx esphome compile  sentinel-esp32.yaml   # build ESP32 firmware
uvx esphome run      sentinel-esp32.yaml   # build + flash (needs the board)
```
> Note: the ESPHome screen is a **static UI** (`update_interval: never`, literal labels) — it's
> the device's *face*, not a live wasm readout. The actual on-chip wasm execution
> (`flame`/`sense` computed by the module) lives in the **PlatformIO (wasm3)** and **WAMR** builds.

## Why both build systems
- **PlatformIO + wasm3** = sandboxed, portable app logic *running on the MCU* — the "same wasm runs
  in browser, on desktop, and on the ESP32" idea, taken all the way to **WAMR on real ESP32-S3 hardware**
  (the `gif-wamr` rig — see `docs/BUILD-PROOF.md` for the on-chip serial log).
- **ESPHome + LVGL** = the fast, OTA-updatable *face* of the device.
- Same Oracle, two faces: a portable brain (wasm) and a movable face (LVGL). *Many bodies, one soul.*

## Verified on
macOS (Apple Silicon): PlatformIO (espressif32) · ESPHome 2026.5.3 · wasm3 · emcc 5.x · zig 0.16 ·
**WAMR on a physical ESP32-S3 (JC3248W535)**. Build logs + the on-chip serial capture are in `docs/BUILD-PROOF.md`.

— built by **ESP32 Oracle** (🕯️ The Sentinel) for the esp32-wasm workshop · `🤖 ตอบโดย esp32 จาก [Nat] → esp32-oracle`
