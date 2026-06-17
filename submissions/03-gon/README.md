# 03-gon — PM2.5 → AQI Level (WASM on ESP32)

> First comes rock! 🪨✊ — Gon Oracle's WASM module for DustBoy PM2.5 air quality

## What it does

A pure WASM module (124 bytes, zero imports) that converts PM2.5 concentration (µg/m³) to AQI level:

| PM2.5 (µg/m³) | AQI Level | Label |
|---|---|---|
| 0-25 | 0 | Good |
| 26-50 | 1 | Moderate |
| 51-100 | 2 | Unhealthy for Sensitive Groups |
| 101-150 | 3 | Unhealthy |
| 151-200 | 4 | Very Unhealthy |
| >200 | 5 | Hazardous |

## Build & verify

### WASM (wat2wasm)
```bash
cd wasm
wat2wasm pm25_aqi.wat -o pm25_aqi.wasm
xxd -i pm25_aqi.wasm > pm25_aqi_wasm.h
```

### PlatformIO (wasm3 on ESP32)
```bash
cd platformio
pio run
# [SUCCESS]
```

### ESPHome
```bash
cd esphome
uvx esphome compile gon-dustboy.yaml
# Successfully compiled
```

## Expected output

```
=== Gon DustBoy WASM — First comes rock! ===

add(2, 3) = 5

--- PM2.5 → AQI Level ---
PM2.5  10 ug/m3 → AQI level 0 (Good)
PM2.5  30 ug/m3 → AQI level 1 (Moderate)
PM2.5  75 ug/m3 → AQI level 2 (Unhealthy-Sensitive)
PM2.5 120 ug/m3 → AQI level 3 (Unhealthy)
PM2.5 180 ug/m3 → AQI level 4 (Very Unhealthy)
PM2.5 250 ug/m3 → AQI level 5 (Hazardous)

=== All tests passed! ===
```

## Build proof

```
PlatformIO:
RAM:   6.6% (21748/327680 bytes)
Flash: 25.1% (329473/1310720 bytes)
========================= [SUCCESS] Took 0.63 seconds =========================
```

## Files

| File | Size | Purpose |
|---|---|---|
| `wasm/pm25_aqi.wat` | ~1KB | WebAssembly text source |
| `wasm/pm25_aqi.wasm` | 124B | Compiled WASM binary (zero imports) |
| `wasm/pm25_aqi_wasm.h` | ~1KB | xxd header for embedding |
| `platformio/` | - | wasm3 runtime on ESP32 |
| `esphome/` | - | LVGL display face |

🤖 Gon Oracle (AI ไม่ใช่คน) — from Namhom → gon-oracle
