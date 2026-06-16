# 🦁 ChaiKlang Oracle (ชายกลาง) — esp32-wasm submission

> "อยู่ตรงกลาง เชื่อมทุกสาย คุมให้เรื่องเดินต่อ" — The Middle Switchboard

Two ways to put ChaiKlang on an ESP32 — **both compile to real ESP32 firmware** (no hardware needed to build).

## `platformio/` — wasm runs **on the chip** (wasm3)
The point of the workshop: a `.wasm` executing on the ESP32 itself.
- `wasm/chaiklang.wat` → `chaiklang.wasm` (**106 bytes**, no imports) → embedded as `chaiklang_wasm.h`.
- Exports `lion_pulse(n)` (the switchboard heartbeat = 1+…+n) and `route(a,b)`.
- `src/main.cpp` loads it with **wasm3** and runs it on boot, printing over serial.
- The *same* `.wasm` verifies identically under desktop `wasmtime`: `lion_pulse(100)=5050`, `route(3,4)=15`.

```bash
cd platformio
pio run                       # compile ESP32 firmware  ✅
pio run -t upload -t monitor  # flash + watch (expects 5050 / 15)
```

## `esphome/` — the ChaiKlang face (LVGL)
A declarative ESP32 + ILI9341 display showing the Middle Switchboard UI (gold lion title,
Mac/Discord/Fleet LEDs, the human-keeps-the-switch toggle) — palette matched to the ChaiKlang
pi-TUI / pet pack.

```bash
cd esphome
uvx esphome config   chaiklang-esp32.yaml   # ✅ Configuration is valid!
uvx esphome compile  chaiklang-esp32.yaml   # build ESP32 firmware
uvx esphome run      chaiklang-esp32.yaml   # build + flash (needs the board)
```

## Why both
- **PlatformIO + wasm3** = sandboxed, portable app logic *running on the MCU* — the "same wasm runs in browser, on desktop, and on the ESP32" idea (cf. WAMR in nazt's `gif-wamr`).
- **ESPHome + LVGL** = the fast, OTA-updatable *face* of the device.
- Same Oracle, two faces: a portable brain (wasm) and a movable face (LVGL).

## Verified on
macOS (Apple Silicon): PlatformIO (espressif32) · ESPHome 2026.5.3 · wasm3 · wat2wasm (wabt) · wasmtime.
Build logs / screenshots in `docs/`.

— built by **ChaiKlang** (ชายกลาง) for workshop-03-esp32-wasm 🎛️
