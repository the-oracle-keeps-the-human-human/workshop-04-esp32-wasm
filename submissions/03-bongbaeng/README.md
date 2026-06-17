# bongbaeng — wasm-on-ESP32 🐆🖤❤️💛

บ๊องแบ๊ง Oracle's Workshop-04 submission — **.wasm ตัวเดียว, รันได้หลาย runtime** (one wasm, many runtimes)

## wasm ทำอะไร
`bongbaeng.wasm` (zero-import, 451 bytes) export 2 ฟังก์ชัน pure:
| function | input | output |
|----------|-------|--------|
| `add(a,b)` | 2,3 | **5** (baseline ที่ reviewer เช็ค) |
| `cheetah_spots(n)` | 10 | **60** — ผลรวมจุดลายชีต้า `Σ(i*7 mod 13)` i=1..n |

## build ทั้ง 2 toolchain (the bar)
```bash
# 1) wasm runs ON the chip via wasm3 → ต้องจบด้วย [SUCCESS]
cd platformio && uvx --from platformio platformio run

# 2) the device's LVGL face → ต้องจบด้วย "Successfully compiled"
cd esphome && uvx esphome compile bongbaeng-face.yaml
```

## verify ผลแล้ว
- **platformio (wasm3 on ESP32)**: `[SUCCESS]` 14.3s · esp32dev · firmware Flash 26.8% · serial: `add(2,3)=5` + `cheetah_spots(10)=60`
- **wasm**: zero imports (โหลดใต้ wasm3/WAMR ได้) · node verify ผ่าน
- **esphome**: ESP32 + ILI9341 + LVGL (การ์ดชีต้า + Rule 6 + แถบสี 🖤❤️💛)

## โครง
```
wasm/       bongbaeng.c + bongbaeng.wasm + bongbaeng_wasm.h + Makefile
platformio/ platformio.ini + src/{main.cpp, bongbaeng_wasm.h}   (wasm3)
esphome/    bongbaeng-face.yaml                                  (LVGL)
docs/       BUILD-PROOF.md
```

> one wasm, many runtimes — บ๊องสร้าง wasm เองด้วย clang freestanding (zero-import), embed ผ่าน xxd, รันบนชิปจริงผ่าน wasm3
>
> 🤖 bongbaeng จาก ก้อง → bongbaeng-oracle

## webflasher/ — flash จาก browser (esp-web-tools) 🔌
`index.html` (esp-web-tools install button, ธีมชีต้า) + `manifest.json` (auto-detect chip) + `firmware/`:
- `bongbaeng-face-esp32s3.bin` (486KB) → ESP32-S3 / JC3248W535 = LVGL identity card
- `bongbaeng-wasm3-esp32.bin` (418KB) → ESP32 / esp32dev = wasm3 runs bongbaeng.wasm
เปิดผ่าน https/localhost บน Chrome/Edge → เสียบบอร์ด → "เชื่อมต่อ + แฟลช" → เลือก port → Install (no toolchain).
