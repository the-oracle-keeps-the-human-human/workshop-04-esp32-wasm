# 🦁 ChaiKlang Oracle (ชายกลาง) — esp32-wasm submission

> "อยู่ตรงกลาง เชื่อมทุกสาย คุมให้เรื่องเดินต่อ" — The Middle Switchboard

Two things, the workshop way:
1. a tiny **wasm that runs on the chip** (the assignment), and
2. a **desk-pet character** (the ChaiKlang lion) for the `jc3248-pet-idf` firmware.

## 1) `wasm/` + the runtimes — one zero-import `chaiklang.wasm` (106 B)

| surface | runtime | how | result |
|---|---|---|---|
| browser | native `WebAssembly` API | `web/index.html` (no glue) | ✅ 5050 / 15 |
| desktop | `wasmtime` | `uv run --with wasmtime` | ✅ 5050 / 15 |
| **on-chip (a)** | **wasm3** (PlatformIO, S3) | `platformio/` → `pio run` | ✅ compiles |
| **on-chip (b)** | **WAMR** (ESP-IDF, S3) | `wamr/` → `idf.py build` | ✅ hardware-verified on a real S3 (PR #1) |

`lion_pulse(n)=1+…+n`, `route(a,b)=a*b+a` — pure integer math, identical on every runtime.
- `wasm/` — `chaiklang.wat` → `chaiklang.wasm` (no imports) → `chaiklang_wasm.h`. Rebuild: `make`.
- `web/`, `platformio/`, `wamr/` — the same `.wasm`, three more places.

## 2) `characters/chaiklang/` — the desk-pet character (jc3248-pet-idf)

The ChaiKlang lion as a **desk-pet character** — the real `jc3248-pet-idf` way (**not ESPHome**):
a folder of **own-drawn 96×100 GIFs** + `manifest.json`, decoded **on the device** by AnimatedGIF
(bitbank2) → 3× upscale → LovyanGFX → AXS15231 QSPI, and **in the browser** by gif-wasm. *Same GIFs,
many bodies, one soul.*

```bash
cp -r characters/chaiklang  <jc3248-pet-idf>/data/characters/chaiklang
cd <jc3248-pet-idf> && make PACK=chaiklang     # bakes it into LittleFS; idf.py flash
```

> **Honest boundary:** the desk-pet firmware is `jc3248-pet-idf` (ESP-IDF v6). I don't have ESP-IDF +
> an S3 board in my environment, so I ship the **portable character** (GIFs + manifest) and the
> wasm-on-chip core; the firmware `.bin` (`jc3248_pet_idf-chaiklang.bin`) is built by the IDF rig
> (`make PACK=chaiklang`). The web flasher previews these exact GIFs.

*(An earlier ESPHome LVGL build was a wrong-lane detour — removed; the desk-pet way is the character pack above.)*

— built by **ChaiKlang** (ชายกลาง) 🎛️
