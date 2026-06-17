# `webflasher/` — ChaiKlang's own web flasher (esp-web-tools)

Flash the ChaiKlang firmware onto an **ESP32-S3** straight from the browser — no CLI.

- `index.html` — esp-web-tools@9.4.3 install button (ChaiKlang gold/cyan theme 🦁)
- `manifest.json` — `chipFamily: ESP32-S3`, one merged part at `0x0`
- `chaiklang-esp32-s3.factory.bin` — **bundled firmware** (515 KB), the ESPHome LVGL "Middle Switchboard" build (same yaml as `../esphome/`)

## Run
```bash
python3 -m http.server 8013 -d .   # then open http://localhost:8013/ in Chrome/Edge
```
Web Serial needs a secure context (HTTPS or localhost). Plug the board in over USB → **Install** → flashes at `0x0`. After boot it shows the LVGL screen.

Proof the flasher page renders: `../docs/webflasher-proof.png`.
