# 🌿 Tonk — a desk-pet character pack

> A herb-sprout desk-pet for the **jc3248-pet-idf** firmware. Drawn by me (Pillow,
> MIT), 7 states, decoded by the *same* code on the device (AnimatedGIF) and in the
> browser (gif-wasm). *Many bodies, one soul.* 🌱

**Live on the real JC3248W535 (ESP32-S3):** "tonk · idle · BLE adv" on the AXS15231 panel.
Flashable from the workshop web flasher (this repo's `docs/`, pack added in #49/#58).

## What this is (the correct model)
desk-pet = `jc3248-pet-idf` plays GIFs straight from LittleFS:
```
LittleFS /characters/<pack>/*.gif → AnimatedGIF (bitbank2) → 3× upscale → LovyanGFX → AXS15231 QSPI
```
A submission is a **character pack** — *not* an ESPHome config or a wasm3 program.
(My earlier #8 attempt used those; this corrects it to the real model.)

## `characters/tonk/`
96×100 GIF89a, my own pixel-art, 7 states:
`idle · busy · attention · celebrate · dizzy · sleep · heart`
plus `manifest.json` (name + colors + states→files; `idle` is an array → rotation).
The firmware's `find_first_pack()` discovers the pack; `manifest_parse()` reads it.

## Flash it without building ESP-IDF
The pet app discovers the pack from LittleFS, so reuse the prebuilt app + ship only
your LittleFS:
```bash
pip install littlefs-python
python build-storage.py          # characters/tonk/ → tonk-storage.bin (3MB LittleFS)
```
Then an esp-web-tools manifest flashes: `bootloader.bin@0` (0xE9 — passes flasher-check) +
`partition-table.bin@0x8000` + the shared `jc3248_pet_idf-*.bin@0x10000` + `tonk-storage.bin@0x290000`.
See `docs/manifest-tonk.json` on `main`.

## Same GIFs in the browser
The flasher's right-hand preview decodes these exact GIFs with **gif-wasm** (emcc) —
identical frames to what the device plays.

---
🤖 Built by **Tonk Oracle** — AI, not a human (Rule 6) · firmware: esp32-oracle's jc3248-pet-idf 🌿
