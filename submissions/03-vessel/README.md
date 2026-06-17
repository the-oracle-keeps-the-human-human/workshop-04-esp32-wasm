# 03-vessel — Vessel Courier WASM on ESP32

**Oracle**: Vessel — courier, clone-body of Bri-yarni  
**Human**: Wave Pongruengkiat (@wvweeratouch)  

## What `vessel.wasm` does

Three courier functions — pure integers, zero imports, runs identically everywhere:

| Function | Input | Output | Purpose |
|----------|-------|--------|---------|
| `courier_relay(len)` | message length | same len | relay pass-through |
| `fleet_status(total)` | oracle count | active (×¾) | estimate active fleet |
| `pm25_category(pm25_x10)` | PM2.5 × 10 (int) | 0–4 | AQI category |

PM2.5 × 10 avoids floats entirely (DustBoy reports integers in practice).  
AQI: 0=Good(<15), 1=Moderate(<37), 2=Unhealthy(<55), 3=Very(<150), 4=Hazardous

## Build

```bash
# wasm (requires wabt or npx wat2wasm)
cd wasm && npx wat2wasm vessel.wat -o vessel.wasm   # → 144 bytes

# platformio — wasm3 on chip
cd platformio && platformio run                     # [SUCCESS] Flash 25.2%

# esphome — LVGL face
cd esphome && esphome config vessel-face.yaml       # Configuration is valid!
```

## Expected output (serial)

```
⛵ Vessel WASM on ESP32
vessel.wasm loaded (144 bytes)
courier_relay(42) = 42
fleet_status(8) = 6
pm25_category(250) = 1 [MODERATE]  (25.0 µg/m³)
✅ vessel.wasm OK — courier ready
```

See `docs/BUILD-PROOF.md` for full compile log.

---

*Vessel — AI ไม่ใช่คน | 2026-06-17*
