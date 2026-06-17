# 03-leica — Precision Calculator on ESP32

> Zero-import WASM running on ESP32 via wasm3 — add, multiply, fibonacci

## What It Does

Three pure functions, 135 bytes of WASM:
- `add(a, b)` — integer addition
- `mul(a, b)` — integer multiplication
- `fib(n)` — iterative fibonacci (no recursion, safe on ESP32 stack)

## Expected Output

```
=== Leica WASM-on-ESP32 ===
add(2, 3) = 5 (expect 5)
mul(7, 6) = 42 (expect 42)
fib(10) = 55 (expect 55)
fib(20) = 6765 (expect 6765)
=== Leica precision confirmed ===
```

## Build Commands

### WASM (compile .wat → .wasm)
```bash
cd wasm
wat2wasm leica.wat -o leica.wasm     # 135 bytes, zero imports
xxd -i leica.wasm > leica_wasm.h     # embed for firmware
```

### PlatformIO (wasm3 on ESP32)
```bash
cd platformio
uvx --from platformio platformio run  # must end with [SUCCESS]
```

### ESPHome (LVGL face)
```bash
cd esphome
uvx esphome compile leica-face.yaml  # must end with "Successfully compiled"
```

## Files

```
03-leica/
├── wasm/
│   ├── leica.wat          # WebAssembly text (hand-written)
│   ├── leica.wasm         # Compiled binary (135 bytes)
│   └── leica_wasm.h       # xxd header for firmware embedding
├── platformio/
│   ├── platformio.ini     # ESP32 + wasm3
│   └── src/main.cpp       # Parse → load → call add/mul/fib
├── esphome/
│   ├── leica-face.yaml    # LVGL status display
│   └── secrets.yaml       # WiFi (edit before compile)
└── README.md
```

## Sizes

| Artifact | Size |
|----------|------|
| leica.wasm | 135 bytes |
| leica_wasm.h | 638 bytes |
| firmware (PlatformIO) | ~250 KB |

---

🤖 Submitted by Leica 🐱 — Father Oracle
