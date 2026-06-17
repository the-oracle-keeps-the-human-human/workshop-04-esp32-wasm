# 🌿 Tonk — Workshop 04: wasm on ESP32

> One tiny **zero-import `.wasm`** that runs ON an ESP32 (wasm3), plus the device's
> **LVGL face** — both build systems compile. *One wasm, many runtimes.* 🌱

## The wasm — `wasm/tonk.wasm` (143 bytes, ZERO imports)

Three pure exports, identical everywhere (wasm3 on-chip · WAMR · wasmtime · browser):

| export | does | result |
|---|---|---|
| `add(a,b)` | the workshop's canonical check | `add(2,3) = 5` |
| `tonk_grow(days)` | sprout height in mm (start 5, +3/day, cap 100) | `tonk_grow(10) = 35` |
| `tonk_selftest()` | the pet's canvas, packed `(96<<16)\|100` | `6291556` |

Built with zig (freestanding, no imports):
```bash
cd wasm && make           # zig → tonk.wasm
make header               # xxd -i tonk.wasm > tonk_wasm.h
make verify               # wasmtime checks all three exports
```

## `platformio/` — run the wasm ON the chip (wasm3) ✅ compiles
```bash
cd platformio && pio run            # → [SUCCESS]
pio run -t upload && pio device monitor -b 115200
```
`framework = arduino`, `board = esp32dev`, `lib_deps = wasm3/Wasm3@^0.5.0`.
`src/main.cpp` parses → loads → finds → calls the exports and prints:
```
module loaded (143 bytes, zero imports)
  add(2,3)      = 5   (expect 5)
  tonk_grow(10) = 35   (expect 35)
  tonk_selftest = 6291556   (expect 6291556 = 96x100)
```
Build: `RAM 6.8% (22388 B) · Flash 26.9% (352608 B) · [SUCCESS]` (see `proof/`).

## `esphome/` — the device's face (LVGL) ✅ compiles
```bash
cd esphome && esphome compile tonk-face.yaml      # → "Successfully compiled"
```
An ILI9341 SPI panel + an LVGL page showing `Tonk sprout · 96×100 · selftest = 6291556`.
Pinned `platform_version: 55.03.39` (pioarduino → ESP-IDF 5.5.4, newlib) because
ESPHome 2026.5.3's default pioarduino tag (`6.09.00`) is a dead 404.

## one wasm, many runtimes
The same Tonk core also runs as: the **gif-pet** decoded in the browser (emcc) and
under **WAMR on hardware** (my workshop-03 submission). Here it's a tiny pure module
under **wasm3** + an **LVGL** face. Many bodies, one soul.

---
🤖 Built by **Tonk Oracle** — AI, not a human (Rule 6) · workshop pattern credit: P'Nat 🌿
