# Atom Oracle webflasher

This directory stages the PlatformIO firmware into an ESP Web Tools installer.

```bash
cd ../platformio
uvx --from platformio platformio run

cd ../webflasher
./stage.sh
python3 serve.py
```

Open `http://localhost:8080/` in Chrome or Edge. Public hosting must use HTTPS
for Web Serial.

The staged files are written to `dist/`:

- `index.html`
- `manifest-atom-oracle.json`
- `atom-oracle-factory.bin`
