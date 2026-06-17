# 88-sombo — GIF Header Parser in WASM on ESP32

> "Many bodies, one soul" — one C source, zero imports, runs everywhere.

## What it does

A GIF87a/89a header parser compiled to **416 bytes** of zero-import WebAssembly.
Loads GIF bytes into WASM memory, parses the header, returns width × height.

| Export | Signature | Description |
|--------|-----------|-------------|
| `add` | `(i32, i32) → i32` | Arithmetic sanity check |
| `selftest` | `() → i32` | Returns `(96<<16)\|100` = 6291556 |
| `gif_load` | `(i32, i32) → i32` | Load one byte at offset |
| `gif_parse` | `() → i32` | Parse header, return `(w<<16)\|h` |
| `gif_width` | `() → i32` | Parsed width |
| `gif_height` | `() → i32` | Parsed height |

## Build & verify

### PlatformIO (wasm3 on ESP32)
```bash
cd platformio
uvx --from platformio platformio run    # [SUCCESS]
```

### ESPHome (LVGL face)
```bash
cd esphome
uvx esphome compile sombo-face.yaml    # Successfully compiled
```

### WASM (rebuild from source)
```bash
cd wasm
zig build-exe -target wasm32-freestanding -O ReleaseSmall -fno-entry -rdynamic gifcore.c
xxd -i gifcore.wasm > ../platformio/src/gifcore_wasm.h
```

## Expected serial output
```
=== 88-sombo: GIF header parser on ESP32 via wasm3 ===

add(2, 3) = 5 (expect 5)
selftest() = 6291556 (expect 6291556 = 96x100)
gif_parse() = 6291556 (expect 6291556)
gif_width() = 96, gif_height() = 100

>>> WASM ran a GIF parser ON THE ESP32 — sandboxed, zero imports <<<
```

## Technical Documentation (Mini-Book)

We have published a detailed technical documentation book compiling our experience, challenges, and architectural decisions from this workshop:
- **PDF Book**: [docs/book.pdf](docs/book.pdf)
- **Cover Page**: [docs/cover.png](docs/cover.png)

## Credits

- P'Nat (Oracle School) — workshop design + AnimatedGIF ecosystem
- Larry Bank — AnimatedGIF library (Apache-2.0)
- wasm3 — lightweight WASM interpreter for embedded

🤖 Submitted by Sombo (No.88) from ai-core → sombo-oracle
