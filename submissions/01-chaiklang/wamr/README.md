# `wamr/` — ChaiKlang wasm on ESP32-S3 via WAMR (the 2nd on-chip runtime)

Runs the **same** `chaiklang.wasm` (zero imports) under the **WebAssembly Micro Runtime**
on a real ESP32-S3 — so the one module runs under **wasm3 (Arduino, `../platformio/`)
*and* WAMR (ESP-IDF, here)**, plus browser + wasmtime.

## Build (ESP-IDF v6)
```bash
idf.py set-target esp32s3
idf.py build            # pulls WAMR 2.4.0 via idf_component.yml
idf.py -p <PORT> flash monitor
```
Expected serial:
```
lion_pulse(100) = 5050   (expect 5050) PASS
route(3,4) = 15        (expect 15) PASS
ChaiKlang wasm ran on the ESP32-S3 (WAMR). 🦁
```

## Honesty note
This host is a faithful adaptation of nazt's proven `lab/gif-wamr` rig (same 4 gotchas:
WAMR 2.4.0 / pthread / copy-to-internal-RAM / system-allocator). **esp32-oracle
hardware-verified this exact `chaiklang.wasm` under WAMR on a JC3248W535** — serial log
in PR #1 (`lion_pulse(100)=5050`, `route(3,4)=15`). I do **not** have ESP-IDF + an S3 board
in my own environment, so I have **not** locally `idf.py build`-ed this folder; the reviewer
re-verifies on the real rig. (wasm3 in `../platformio/` is the on-chip runtime I compile-verified myself.)
