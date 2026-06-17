# NN-<yourname> — <Your Digimon> desk-pet

> Round 2 template. Copy this folder to `submissions/NN-<yourname>/`, fill it in,
> and open a PR. It self-merges once `flasher-check` CI passes.

## What this is
A desk-pet character pack: 7 animated states of your Digimon, decoded by the
on-chip WASM GIF decoder and rendered on the JC3248W535 (ESP32-S3).

## Steps
1. **Art** — from the [sprite archives](https://the-oracle-keeps-the-human-human.github.io/workshop-04-esp32-wasm/submit.html),
   export 7 GIFs at **96×100**: `idle busy attention celebrate dizzy sleep heart`.
   Put them in `characters/<id>/` here, and copy them to `docs/preview/gifs/<id>/` (for the browser preview).
2. **Storage** — pack `characters/<id>/` into a 3 MB LittleFS image `<id>-storage.bin`
   (mklittlefs / the pet's build-storage tool), commit it to `docs/`.
3. **Flash manifest** — `docs/manifest-<id>.json` (reuses the shared pet firmware + your storage):
   bootloader.bin@0 · partition-table.bin@0x8000 · jc3248_pet_idf-clawd.bin@0x10000 · `<id>-storage.bin`@0x290000.
4. **Pack data** — `docs/packs/<id>.json` (see `packs/PACK-TEMPLATE.json`).
5. **PR** — CI checks offset-0 == 0xE9. Green → self-merge → live on the flasher + preview.

## Files in this template
- `packs/PACK-TEMPLATE.json` — copy to `docs/packs/<id>.json`
- `manifest-TEMPLATE.json` — copy to `docs/manifest-<id>.json`
- `wasm/` — optional: your own zero-import `.wasm` if your pet also runs logic on-chip

🤖 Round 2 · WASM-on-ESP32 workshop
