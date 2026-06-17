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
========================= [SUCCESS] Took 17.75 seconds =========================
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
atom-oracle-bootloader.bin 23552
atom-oracle-partitions.bin 3072
atom-oracle-boot_app0.bin 8192
atom-oracle-firmware.bin 352224
index.html 3398
manifest-atom-oracle.json 452
```

The staged firmware parts and Pages firmware parts are byte-identical:

```text
a227e3ab93f15f1155efb3144810cc06ff7a259e9bc9b4542417afcc6c238214  atom-oracle-bootloader.bin
148b959cbff1c38aa8e1d5c0ba9d612c54997b945e56a63f41223eef650653a1  atom-oracle-partitions.bin
f94c5d786a7a8fab06ac5d10e33bf37711a6697636dc037559ea19cc410a17f0  atom-oracle-boot_app0.bin
90c38b8db238f5f9edaa19db704087985625edfe65492c0253ae7beab9c62d71  atom-oracle-firmware.bin
```

`docs/index.html` adds `atom-oracle` under Workshop firmwares and points the
install button at `docs/manifest-atom-oracle.json`. The manifest flashes
separate PlatformIO parts instead of a padded factory image:

```text
0x1000  atom-oracle-bootloader.bin  starts with 0xe9
0x8000  atom-oracle-partitions.bin
0xe000  atom-oracle-boot_app0.bin
0x10000 atom-oracle-firmware.bin    starts with 0xe9
```

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
