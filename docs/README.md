# Desk-pet Web Flasher

Browser USB flasher for the JC3248W535 desk-pet — pick a character pack
(bufo / cat / cat-orange / cat-pet) and flash it from a Chrome/Edge tab, no
ESP-IDF or esptool needed. Plug the pet into any machine with a Chromium
browser, open the page, click.

Pattern learned from `agents/1-waveshare7/webflasher` (esp-web-tools@9.4.3).
Adapted for "multiple firmware": one selectable button, per-pack manifests
sharing the bootloader / partition-table / 3 MB LittleFS storage (all packs
live in that one image — only the boot default differs).

Committed source: `index.html`, `serve.sh`, `stage.sh`, `README.md`.
Build artifacts (gitignored): `*.bin`, `manifest-*.json`.

## Use

```sh
# 1. build one firmware per pack  → ../dist-firmware/
../tools/build-packs.sh

# 2. stage bins here + generate the per-pack manifests
./stage.sh

# 3. serve on localhost (Web Serial needs https or localhost)
./serve.sh                 # → http://localhost:8123/

# 4. open the URL in desktop Chrome / Edge / Opera:
#    choose a pack → CONNECT → pick /dev/cu.usbmodem… → confirm ESP32-S3 → INSTALL
```

## Flash layout (build/flash_args)

| offset    | image                              |
|-----------|------------------------------------|
| `0x0`     | `bootloader.bin`                   |
| `0x8000`  | `partition-table.bin`              |
| `0x10000` | `jc3248_pet_idf-<pack>.bin` (app)  |
| `0x290000`| `storage.bin` (3 MB, all packs)    |

## Notes

- **Browser**: desktop Chrome / Edge / Opera only (Web Serial). Firefox & Safari are out.
- **Port**: use the **native USB-Serial-JTAG** port (the short `usbmodemXXXX`) so
  auto-reset works on macOS.
- **All packs ship in every image** — `PET_DEFAULT_PACK` only sets which boots,
  so flashing e.g. `cat-orange` still carries the others on the FS.
- Cat packs are **CC0**; `clawd` (the Claude mascot) is **MIT** (anthropics/claude-desktop-buddy)
  — see each pack's `PROVENANCE.md` under `lab/buddy/characters/`.
