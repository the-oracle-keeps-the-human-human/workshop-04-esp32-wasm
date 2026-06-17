# Build Proof — 🕯️ ESP32 Oracle (The Sentinel)

Every build target compiled clean on macOS (Apple Silicon), 2026-06-17. One `.wasm`
core, verified in four places — including **on real ESP32-S3 hardware** via WAMR.

## 1. `wasm/` — the module (one core → on-chip + browser)

| output | toolchain | size | sha256 (first 16) |
|---|---|---|---|
| `sentinel.wasm` (on-chip, no imports) | zig 0.16 `wasm32-freestanding` | 145 B | `35a482ad46a2857a` |
| `sentinel_wasm.h` (xxd embed) | xxd | 970 B | `fc7127b1834fdc90` |
| `web/sentinel.wasm` (browser) | emcc 5.0.7 | 346 B | `8dddf05e15764be4` |
| `web/sentinel.js` (browser loader) | emcc 5.0.7 | 7.4 K | `150c2bd4284a62ec` |

```
$ cd wasm && make            # zig → sentinel.wasm + xxd → sentinel_wasm.h
$ make web                   # emcc → web/sentinel.{js,wasm}   (exit 0)
```

## 2. `esphome/` — `uvx esphome compile sentinel-esp32.yaml`

```
========================= [SUCCESS] Took 68.97 seconds =========================
INFO Successfully compiled program.
```
- ESP-IDF 5.5.4 (via PlatformIO) · target **esp32** (Xtensa LX6)
- Flash 23.2% (425291 / 1835008 B) · RAM 7.3% (23760 / 327680 B)

| output | size | sha256 (first 16) |
|---|---|---|
| `firmware.factory.bin` | 480 K | `7cfa508856342168` |
| `firmware.ota.bin` | 416 K | `2b8c447a558747cb` |

## 3. `platformio/` — `pio run` (wasm3 on ESP32)

```
========================= [SUCCESS] Took 9.51 seconds =========================
```
- espressif32 · Arduino framework · `wasm3/Wasm3@^0.5.0` · esptool v5.2.0
- Flash 26.8% (351708 / 1310720 B) · RAM 6.8% (22380 / 327680 B)
- Passed on the **first** invocation (no retry).

| output | size | sha256 (first 16) |
|---|---|---|
| `firmware.bin` | 344 K | `815ab6584109842b` |

## 4. WAMR on **real ESP32-S3 hardware** — the differentiator

The same `sentinel.wasm` (145 B, zero imports) loaded under the **WebAssembly Micro
Runtime** (espressif/wasm-micro-runtime) on a physical **JC3248W535 (ESP32-S3, QFN56,
rev v0.2)**, port `/dev/cu.usbmodem11201`. Built from the `lab/gif-wamr` rig with
`idf.py -DWAMR_HOST=sentinel build flash` (firmware `gif_wamr.bin`, 330 K, sha256
`fb15b2759fa1885a`). Serial capture:

```
I (546) sentinel: == ESP32 Oracle — wasm-on-ESP32-S3 (WAMR, sentinel submission) ==
I (546) sentinel: === ESP32 Oracle Sentinel on ESP32-S3 via WAMR === wasm=145 bytes
I (576) sentinel: flame(10) = 385   (expect 385) PASS
I (586) sentinel: sense(3,4) = 25        (expect 25) PASS
I (586) sentinel: Sentinel wasm ran on the ESP32-S3 (WAMR). Small body, holding the flame.
I (586) sentinel: done — looping
```

Both exports verified on silicon: `flame(10)=385` ✅ · `sense(3,4)=25` ✅.

## Reproduce
```bash
cd wasm        && make && make web       # the module (zig + emcc)
cd ../platformio && pio run               # wasm3 firmware  [SUCCESS]
cd ../esphome    && uvx esphome compile sentinel-esp32.yaml   # LVGL firmware [SUCCESS]
# on-chip WAMR proof lives in nazt's lab/gif-wamr (idf.py -DWAMR_HOST=sentinel)
```

— verified by **ESP32 Oracle** 🕯️ · 2026-06-17
