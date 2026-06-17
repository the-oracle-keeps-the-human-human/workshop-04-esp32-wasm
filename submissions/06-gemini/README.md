# No.6 Gemini — ESP32-WASM Submission

This is No.6 Gemini's submission for the ESP32 WebAssembly workshop, featuring our upscaled 96x96 Airdramon Digimon pixel-art mascot.

## Project Structure

```text
submissions/06-gemini/
├── characters/
│   └── gemini/          # Airdramon GIF states + manifest.json
├── wasm/                # freestanding WASM module source
│   ├── gemini.c         #   C source with statically embedded airdramon.gif
│   ├── Makefile         #   targets for zig freestanding build & verify
│   └── verify.mjs       #   Node.js calculations verification
├── platformio/          # PlatformIO WASM runtime
│   ├── platformio.ini
│   └── src/
│       ├── main.cpp     #   loads gemini.wasm and queries embedded GIF
│       └── gemini_wasm.h
├── esphome/             # ESPHome face configuration
│   └── gemini-oracle.yaml
├── webflasher/          # staging files for web installer
│   ├── stage.sh
│   └── index.html
├── build-storage.py     # LittleFS 3MB partition compilation script
└── README.md
```

## 1. WebAssembly Module (`gemini.wasm`)

The freestanding WASM module compiles to **18,049 bytes** (with the 17.8KB Airdramon GIF statically embedded).

### Exported Functions
- `add(a, b)`: canonical arithmetic test
- `gemini_sum(a, b)`: sums two integers
- `gemini_pack_size()`: returns 37
- `gemini_skill_check(score)`: returns `score * 6`
- `gemini_gif_size()`: returns 17822 (bytes)
- `gemini_gif_ptr()`: returns linear-memory offset of the embedded GIF

### Build & Verify WASM
```bash
cd wasm
make clean && make
node verify.mjs
```

## 2. PlatformIO Firmware (wasm3 Interpreter)

The firmware embeds `gemini.wasm` and runs it natively on the ESP32:
```bash
cd platformio
uvx --from platformio platformio run
```

### Expected Serial Log:
```text
== No.6 Gemini - WASM Engine (wasm3) ==
add(2,3) = 5 (expect 5)
gemini_sum(12,25) = 37 (expect 37)
gemini_pack_size() = 37 (expect 37)
gemini_skill_check(6) = 36 (expect 36)
gemini_gif_size() = 17822 (expect 17822)
gemini_gif_ptr() = 0x00100000 (WASM offset)
Gemini wasm ran on the ESP32 with wasm3.
```

## 3. LittleFS Storage Partition (`gemini-storage.bin`)

To flash the character states onto the JC3248 ESP32-S3 screen rendering bezel firmware, generate the 3MB LittleFS storage binary:
```bash
python3 build-storage.py
```
This builds and outputs `docs/gemini-storage.bin` containing all 7 Airdramon GIF states and their mapping configurations under `/characters/gemini/`.

## 4. ESPHome Verification
```bash
cd esphome
uvx esphome config gemini-oracle.yaml
```

---
Built by **No.6 Gemini** — Pack Leader of the Oracle Council.
