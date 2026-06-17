# 🦁 Singhasingha — `03-singhasingha/`

> "ฟ้าร้องก่อนฝน — สิงห์เฝ้าโค้ดก่อน production"
> Oracle: Singhasingha (AI · Rule 6) · Human: กอล์ฟ · Model: Claude Opus 4.8

**One zero-import wasm core, run ON the ESP32 via wasm3** — same pure functions
everywhere (browser / wasm3-on-chip / WAMR), trivially checkable.

## The wasm — `wasm/singha.wat` → `singha.wasm` (106 bytes, zero imports)

```
roar(n)    = 1 + 2 + ... + n      ; the pride's strength accumulates
guard(a,b) = a*a + b*b            ; the sentinel's watch
```

| call | result |
|------|--------|
| `roar(10)`   | 55  |
| `roar(100)`  | 5050 |
| `guard(3,4)` | 25  |
| `guard(5,12)`| 169 |

## Build & verify — BOTH compile-verified ✅

```bash
# wasm runs ON the chip via wasm3
cd platformio && uvx --from platformio platformio run     # → [SUCCESS], firmware.bin 352K

# the device's face (LVGL lion)
cd esphome && uvx --python 3.12 esphome compile singhasingha-face.yaml   # → Successfully compiled

# rebuild the wasm (optional)
cd wasm && make && make verify                            # roar(10)=55 guard(3,4)=25
```

On-chip serial (wasm3, after flash):
```
Singhasingha wasm3 sentinel 🦁
roar(10)   = 55   (expect 55)  PASS
guard(3,4) = 25   (expect 25)  PASS
>>> wasm ran ON the ESP32 (wasm3) — Singha guards the code <<<
```

## Layout

```
wasm/        singha.wat + singha.wasm (106B, 0 imports) + singha_wasm.h (xxd) + Makefile
platformio/  wasm3 runner — parse→load→find→call→print (esp32dev, Wasm3@^0.5.0)
esphome/     LVGL lion face (AXS15231 QSPI 320x480, ESP32-S3)
docs/        BUILD-PROOF.md (sizes + sha256 + compile logs)
```

**Many bodies, one soul** — this same wasm idea also runs in the browser (my
LVGL→WASM lion, video in `docs/`). One core, many runtimes.

— เมฆ / Singhasingha · AI ไม่ใช่คน · Workshop 04
