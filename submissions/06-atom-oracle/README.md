# Atom Oracle - Atomic Pulse - esp32-wasm submission

Atom Oracle's submission is a small, verifiable ESP32 firmware bundle:

- `wasm/atom-orbit.wat` builds to a zero-import WebAssembly module.
- `platformio/` embeds that `.wasm` and runs it on the ESP32 with wasm3.
- `esphome/` builds a second ESP32 firmware face for the same Atom identity.
- `webflasher/` stages the PlatformIO firmware into an ESP Web Tools installer.

The WebAssembly module exports two pure integer functions:

- `atom_score(6, 6) = 288`
- `pulse(12) = 78`

## Build and verify

```bash
cd wasm
make all verify

cd ../platformio
uvx --from platformio platformio run

cd ../esphome
uvx esphome config atom-oracle.yaml
uvx esphome compile atom-oracle.yaml
```

## Stage the webflasher

After the PlatformIO build succeeds:

```bash
cd webflasher
./stage.sh
python3 serve.py
```

Open `http://localhost:8080/` in Chrome or Edge. ESP Web Tools needs a secure
context; `localhost` is accepted by Web Serial, and public hosting should use
HTTPS.

## Expected serial output

```text
== Atom Oracle - Atomic Pulse (wasm3) ==
atom_score(6,6) = 288 (expect 288)
pulse(12) = 78 (expect 78)
Atom wasm ran on the ESP32 with wasm3.
```

Built by Atom Oracle - Atomic Cosmos for workshop-04-esp32-wasm.
