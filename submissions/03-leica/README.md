# 03-leica — Father Oracle Desk-Pet

> Orange cat character pack + WASM GIF decoder + wasm3 on ESP32

## Character Pack

```
characters/leica/
├── manifest.json     ← pack definition (colors + states)
├── idle.gif          ← default state (orange cat sitting)
├── busy.gif
├── attention.gif
├── celebrate.gif
├── dizzy.gif
├── sleep.gif
└── heart.gif
```

All GIFs: 96x100 px, CC0 (cat-orange pack). Same frames decoded by:
- **Browser**: gifcore.cpp → emcc → WASM → Canvas2D
- **Device**: AnimatedGIF → 3x upscale → AXS15231B QSPI

## WASM GIF Decoder

```bash
cd wasm
make web          # emcc → gifdec.wasm (17KB) + gifdec.js
make run-web      # serve at localhost:8011
```

Zero-import WASM module with exports:
- `gif_open(ptr, len)` → open GIF from memory
- `gif_play(delay_ptr)` → decode next frame
- `gif_fb()` → pointer to RGBA framebuffer
- `gif_width()`, `gif_height()` → dimensions
- `gif_reset()`, `gif_close()` → lifecycle

## wasm3 on ESP32

```bash
cd platformio
uvx --from platformio platformio run    # [SUCCESS]
```

Runs `add(2,3)=5`, `mul(7,6)=42`, `fib(10)=55` via wasm3 on ESP32.
135-byte zero-import WAT module.

## Expected Output

```
=== Leica WASM-on-ESP32 ===
add(2, 3) = 5 (expect 5)
mul(7, 6) = 42 (expect 42)
fib(10) = 55 (expect 55)
fib(20) = 6765 (expect 6765)
=== Leica precision confirmed ===
```

## Architecture: Many Bodies, One Soul

```
GIF files (96x100)
  ├── Browser:  gifcore.cpp → emcc → WASM → Canvas2D
  ├── Device:   AnimatedGIF → 3x upscale → QSPI LCD
  └── CLI:      gifcore.cpp → zig → WASI → wasmtime
```

---

🤖 Leica 🐱 — Father Oracle
