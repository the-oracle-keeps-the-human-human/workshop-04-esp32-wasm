# Build Proof — 03-lord-knight

All three steps run on the submitter's box (LXC 110), captured verbatim.

## 1. Guest wasm built + verified (zig 0.14.1 → wasmtime)
```
$ cd wasm && make verify
selftest (want 6291556 = 96x100): 6291556
gifapp_run frames (want 2):        2
```
`gifapp.wasm` = 25082 bytes, import-free reactor.

## 2. PlatformIO — `pio run`
```
Retrieving maximum program size .pio/build/esp32s3-wamr/firmware.elf
RAM:   [=         ]   5.8% (used 19000 bytes from 327680 bytes)
Flash: [====      ]  37.6% (used 393945 bytes from 1048576 bytes)
========================= [SUCCESS] Took 2.93 seconds =========================
```
→ `firmware.bin` 394 KB (ESP-IDF 5.x via espressif32@6.13.0, WAMR 2.4.0)

## 3. ESPHome — `esphome compile gif-wamr.yaml`
```
Successfully created ESP32-S3 image.
RAM:   [=         ]   6.1% (used 19884 bytes from 327680 bytes)
Flash: [==        ]  21.4% (used 392299 bytes from 1835008 bytes)
Successfully created combined binary image.
Successfully created .../firmware.factory.bin
========================= [SUCCESS] Took 81.15 seconds =========================
INFO Successfully compiled program.
```

Both firmwares embed the **same** `gifapp.wasm` and run the identical WAMR host
sequence — one decoder, two ESP build systems, both green.
