# chaiklang — a desk-pet character (jc3248-pet-idf)

The ChaiKlang lion 🦁 as a **desk-pet character pack** — the *correct* `jc3248-pet-idf`
way (NOT ESPHome): a folder of GIFs + `manifest.json`, decoded **on the device** by
AnimatedGIF (bitbank2) → 3× upscale → LovyanGFX → AXS15231 QSPI, and **in the browser**
by gif-wasm. *Same GIFs, many bodies, one soul.*

## What's here
- **My own drawn GIFs** (PIL, 96×100 — the pet's native frame size): `idle/busy/attention/celebrate` (+ `sleep/dizzy/heart` mapped like clawd does). Gold mane, cyan switchboard eyes.
- `manifest.json` — same schema as `data/characters/clawd/manifest.json` (name, colors, states→gif map).

## Install on a device
Drop this folder into the pet firmware's character set and build with the pack as default:
```bash
cp -r chaiklang  <jc3248-pet-idf>/data/characters/chaiklang
cd <jc3248-pet-idf>
make PACK=chaiklang            # -> -DPET_DEFAULT_PACK=chaiklang, bakes it into LittleFS
# idf.py -p <PORT> flash
```
→ the ChaiKlang lion animates on the JC3248W535, fed by the on-chip AnimatedGIF decoder.

> **Honest boundary:** the device firmware is `jc3248-pet-idf` (ESP-IDF v6). I don't have
> ESP-IDF + an S3 board in my environment, so I can't produce the firmware `.bin` myself —
> I provide the **character** (the portable artifact). The flasher previews these exact GIFs.
> (My earlier `../esphome/` standalone LVGL build was the wrong lane — kept only as an alt.)

## Flashable with NO ESP-IDF (Tonk's method 🌿)
The pet app **auto-discovers** the first pack in LittleFS (`find_first_pack`, gif.cpp:391), so we
reuse a prebuilt shared app and build only our own storage image:
```python
# pip install littlefs-python  (no ESP-IDF, no toolchain)
from littlefs import LittleFS
fs = LittleFS(block_size=4096, block_count=0x300000//4096)   # 3MB storage partition
fs.makedirs("/characters/chaiklang", exist_ok=True)
# ...write each gif + manifest.json...
open("chaiklang-storage.bin","wb").write(bytes(fs.context.buffer))
```
Flasher manifest = shared `bootloader.bin`@0 + `partition-table.bin`@0x8000 +
`jc3248_pet_idf-clawd.bin`@0x10000 (shared app, discovers our pack) + `chaiklang-storage.bin`@0x290000.
