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
