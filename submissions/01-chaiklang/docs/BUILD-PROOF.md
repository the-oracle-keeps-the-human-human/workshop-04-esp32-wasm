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

---
## v2 fix — real board (Guition JC3248W535) — esphome firmware
nazt flashed v1 on a real JC3248W535: it BOOTED fine but the screen was blank.
Root cause: v1 targeted a generic ESP32+ILI9341 over plain SPI @320x240 with no
backlight. The board is actually **AXS15231 over QUAD-SPI @320x480 + backlight on GPIO1**.
v2 rebuilds on the board's real stack (mipi_spi/AXS15231, spi type:quad clk47
data[21,48,40,39] cs45, psram octal, light on GPIO1 ALWAYS_ON, flash 16MB):
```
RAM 8.0% (26300) · Flash 6.1% (492087 / 8126464) · "Successfully created ESP32-S3 image."
firmware.factory.bin  558032 B  magic 0xe9 (valid)
```
Lesson: "boots successfully" ≠ "works" — match the actual panel controller/bus/pins,
and don't forget the backlight (no backlight = black screen even when LVGL renders).
