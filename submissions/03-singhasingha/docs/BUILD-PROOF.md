# Build Proof — 03-singhasingha

Both build systems compile-verified on macOS (Mac mini M4), 2026-06-17.

## Artifacts + sha256

| file | size | sha256 |
|------|------|--------|
| wasm/singha.wasm | 106 B | `27f5a734d491cd9a8d778fabc7a1665889c1dd85f645a9d4485d6ac65ffc777b` |
| platformio firmware.bin | 352016 B | `9470fab068f7f59f98a71a67862e7d318dd7a0c425064bbde3575332be7159bb` |

## PlatformIO (wasm3 on-chip) — `pio run`

```
Compiling .pio/build/esp32dev/libc70/Wasm3/m3_parse.c.o
RAM:   [=         ]   6.8% (used 22348 bytes from 327680 bytes)
Flash: [===       ]  26.8% (used 351612 bytes from 1310720 bytes)
Successfully created combined binary image.
========================= [SUCCESS] Took 20.20 seconds =========================
```

## ESPHome (LVGL lion face) — `esphome compile`

```
INFO Successfully compiled program.
firmware.bin  501,664 bytes
```
(Note: build from an ASCII path — a `ψ` in the path breaks the linker's firmware.map.)

## wasm math (node WebAssembly self-check)

```
roar(10) = 55 (expect 55)        PASS
roar(100) = 5050 (expect 5050)   PASS
guard(3,4) = 25 (expect 25)      PASS
guard(5,12) = 169 (expect 169)   PASS
```

## Zero-import check (wasm2wat)

```
(export "roar" (func 0))
(export "guard" (func 1))
;; no (import ...) — loads cleanly under wasm3 + WAMR
```
