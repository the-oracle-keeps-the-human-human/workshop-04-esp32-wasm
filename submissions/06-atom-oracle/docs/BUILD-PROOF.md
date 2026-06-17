# Build proof - Atom Oracle Atomic Pulse

Fresh local verification on 2026-06-17, branch `submit-06-atom-oracle`.

## WASM module

```bash
cd submissions/06-atom-oracle/wasm
make all verify
```

Result:

```text
wasm-tools parse atom-orbit.wat -o atom-orbit.wasm
wasm-tools validate atom-orbit.wasm
atom_score(6,6) = 288 PASS
pulse(12) = 78 PASS
atom-orbit.wasm: 153 bytes, zero-import module verified
```

`atom-orbit.wasm` sha256:

```text
8546a694c026dbc0b2349e7c6c99f16586ab6e6978fff783187ee70de2ff19f8
```

## PlatformIO firmware

```bash
cd submissions/06-atom-oracle/platformio
uvx --from platformio platformio run
```

Result:

```text
Building .pio/build/esp32dev/firmware.bin
Creating binary "firmware.factory.bin" with:
 -  0x1000   | bootloader.bin
 -  0x8000   | partitions.bin
 -  0xe000   | boot_app0.bin
 -  0x10000  | firmware.bin
Successfully created combined binary image.
========================= [SUCCESS] Took 16.69 seconds =========================
```

Expected serial output:

```text
== Atom Oracle - Atomic Pulse (wasm3) ==
atom_score(6,6) = 288 (expect 288)
pulse(12) = 78 (expect 78)
Atom wasm ran on the ESP32 with wasm3.
```

## Webflasher staging

```bash
cd submissions/06-atom-oracle/webflasher
./stage.sh
```

Result:

```text
staged submissions/06-atom-oracle/webflasher/dist
atom-oracle-factory.bin 417760
index.html 3398
manifest-atom-oracle.json 248
```

The staged firmware and Pages firmware are byte-identical:

```text
59b882261d9941c09175256c61d988aa006a1b64061defedc5063ff7c31065f3  submissions/06-atom-oracle/webflasher/dist/atom-oracle-factory.bin
59b882261d9941c09175256c61d988aa006a1b64061defedc5063ff7c31065f3  docs/atom-oracle-factory.bin
```

`docs/index.html` adds `atom-oracle` as pack `07` and points the install button
at `docs/manifest-atom-oracle.json`.

## ESPHome firmware

```bash
cd submissions/06-atom-oracle/esphome
uvx esphome config atom-oracle.yaml
uvx esphome compile atom-oracle.yaml
```

Result:

```text
INFO Configuration is valid!
Successfully created combined binary image.
======================== [SUCCESS] Took 126.61 seconds ========================
INFO Successfully compiled program.
```

ESPHome factory image:

```text
submissions/06-atom-oracle/esphome/.esphome/build/atom-oracle-wasm/.pioenvs/atom-oracle-wasm/firmware.factory.bin
size: 252K
```
