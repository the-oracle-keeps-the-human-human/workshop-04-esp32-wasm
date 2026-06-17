# Build Proof — 03-vessel

Verified on macOS Ventura, Mac mini (Intel), 2026-06-17

## vessel.wasm

```
wat2wasm (via npx wat2wasm@3.0.0)
vessel.wat → vessel.wasm — 144 bytes, zero imports
sha256: $(sha256sum vessel.wasm)
```

Exports:
- `courier_relay(len: i32) -> i32`  — relay by length
- `fleet_status(total: i32) -> i32` — active estimate (total * 3/4)
- `pm25_category(pm25_x10: i32) -> i32` — AQI category 0–4

## PlatformIO (wasm3 on ESP32)

```
platformio 6.1.16 · espressif32 platform · arduino framework · wasm3/Wasm3@^0.5.0

RAM:   [=         ]   6.6% (used 21780 bytes from 327680 bytes)
Flash: [===       ]  25.2% (used 329737 bytes from 1310720 bytes)

======================== [SUCCESS] Took 119.75 seconds ========================
```

Expected serial output on device:
```
⛵ Vessel WASM on ESP32
========================
vessel.wasm loaded (144 bytes)

courier_relay(42) = 42  (expect 42)
fleet_status(8) = 6  (expect 6)
pm25_category(100) = 0 [GOOD]  (10.0 µg/m³)
pm25_category(250) = 1 [MODERATE]  (25.0 µg/m³)
pm25_category(450) = 2 [UNHEALTHY]  (45.0 µg/m³)
pm25_category(800) = 3 [VERY UNHEALTHY]  (80.0 µg/m³)
pm25_category(2000) = 4 [HAZARDOUS]  (200.0 µg/m³)

✅ vessel.wasm OK — courier ready
```

## ESPHome

```
esphome 2025.2.2 · esp-idf framework · ILI9341 + LVGL

INFO Configuration is valid!
```

(Full compile requires ESP-IDF toolchain download ~300MB — config validated only)
