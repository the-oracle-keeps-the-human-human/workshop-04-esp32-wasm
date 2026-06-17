# Build proof — both versions compiled to ESP32 firmware (no hardware needed)

## PlatformIO (pio run)
RAM:   [=         ]   6.8% (used 22348 bytes from 327680 bytes)
Flash: [===       ]  26.8% (used 351696 bytes from 1310720 bytes)
======================== [SUCCESS] Took 104.74 seconds ========================

## ESPHome (uvx esphome compile)
[0mRAM:   [=         ]   7.3% (used 23760 bytes from 327680 bytes)
[0mFlash: [==        ]  23.1% (used 424375 bytes from 1835008 bytes)
[0mSuccessfully created ESP32 image.
Successfully created combined binary image.

## wasm module verified under wasmtime (same .wasm)
lion_pulse(100)=5050  route(3,4)=15

Verified 2026-06-17 06:57 +07 on macOS Apple Silicon.

---
## ESP32-S3 retarget (Fix A) — both recompiled green

### PlatformIO (pio run, board=esp32-s3-devkitc-1)
RAM 6.6% (21708) · Flash 10.6% (354463 / 3342336) · [SUCCESS] 13.43s

### ESPHome (board=esp32-s3-devkitc-1, S3-safe SPI pins clk12/mosi11/miso13/cs10/dc14/reset9)
RAM 7.7% (25340) · Flash 24.5% (448899 / 1835008) · "Successfully created ESP32-S3 image."

## WAMR on real ESP32-S3 (Fix B) — hardware-verified by esp32-oracle (PR #1 review)
```
I (546) chaiklang: === ChaiKlang on ESP32-S3 via WAMR === wasm=106 bytes
I (546) chaiklang: lion_pulse(100) = 5050   (expect 5050) PASS
I (546) chaiklang: route(3,4) = 15        (expect 15) PASS
```
Host source: wamr/  (adapted from the proven lab/gif-wamr rig; not locally idf.py-built — no ESP-IDF/board here).
