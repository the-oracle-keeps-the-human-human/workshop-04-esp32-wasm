# 🍺 Weizen Oracle — desk-pet character pack

**Theme: Unfiltered Weizen** — cloudy gold wheat beer, foam on top, yeast left in the glass.
A desk-pet for the **jc3248-pet** (Guition JC3248W535, ESP32-S3 + AXS15231 QSPI).

> Re-read the source after อ.Nat's correction: this is **not** ESPHome and **not** a wasm3
> serial printer. A desk-pet character is a folder of GIFs decoded by one engine in two bodies.

## The pipeline (from `lab/jc3248-pet-idf`)
```
LittleFS  /characters/<pack>/*.gif
   → AnimatedGIF decoder (bitbank2)        device:  native → 3× upscale → LovyanGFX → AXS15231 QSPI
   → gif-wasm (emcc)                        browser: same GIFs → Canvas2D (the web preview)
   = many bodies, one soul
```

## What's here
```
characters/weizen/
  manifest.json            # name + colors + the 7 canonical states
  sleep.gif idle.gif busy.gif attention.gif celebrate.gif dizzy.gif heart.gif   # 96×100 GIF89a
  PROVENANCE.md            # 100% original art (MIT), no upstream sprites
  build-weizen-pack.sh     # rebuilds every gif (Python + Pillow, headless-friendly)
  gen_weizen_pack.py       # the generator (every pixel is code)
```

The format matches bufo/cat/clawd exactly: **96×100**, the seven states
(`sleep · idle · busy · attention · celebrate · dizzy · heart`), `manifest.json` mapping states →
files, drawn on the manifest bg `#15110B`.

## Verify
- **Browser (gif-wasm):** these GIFs decode in the workshop preview (`docs/preview/`, `?pack=weizen`)
  — the same decoder family the device uses.
- **Rebuild:** `cd characters/weizen && ./build-weizen-pack.sh` → 7 fresh GIFs.

## On-device flash
A desk-pet flashes the shared pet image: `bootloader + partition-table + jc3248_pet_idf-<pack>.bin
+ storage.bin`, where `storage.bin` (LittleFS) holds **all** packs. To boot weizen on glass, drop
`characters/weizen/` into the pet's `/characters` and rebuild `storage.bin` (+ a weizen default-app
bin) — the pack here is ready for that bake.

🍺 หลายแก้ว เบียร์เดียวกัน — many glasses, one beer. Weizen Oracle (AI · Rule 6 — not a human).
