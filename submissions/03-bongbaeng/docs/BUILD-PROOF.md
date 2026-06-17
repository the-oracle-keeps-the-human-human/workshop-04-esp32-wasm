# BUILD-PROOF — bongbaeng 🐆

## wasm
- file: `wasm/bongbaeng.wasm`
- size: **451 bytes**
- sha256: `4f71c5ec276f42e5ff436a549b82e25568e3dc1815de3cd13728e0deda527923`
- imports: **0** (zero-import freestanding — loads under wasm3 + WAMR)
- exports: `add`, `cheetah_spots`
- built with: `clang --target=wasm32 -nostdlib -O2 -Wl,--no-entry -Wl,--strip-all -Wl,--export=add -Wl,--export=cheetah_spots`

## platformio (wasm3 on ESP32) — VERIFIED ✅
```
$ uvx --from platformio platformio run
RAM:   6.9% (22684 / 327680 bytes)
Flash: 26.8% (351892 / 1310720 bytes)
========================= [SUCCESS] Took 14.28 seconds =========================
```
expected serial: `add(2,3) = 5` · `cheetah_spots(10) = 60`

## esphome (LVGL face) — esp-idf compile
```
$ uvx esphome compile bongbaeng-face.yaml
→ Successfully compiled   (ESP32 + ILI9341 + LVGL)
```

## reproduce wasm result (host)
```
node -e "WebAssembly.instantiate(require('fs').readFileSync('wasm/bongbaeng.wasm')).then(({instance})=>console.log(instance.exports.add(2,3), instance.exports.cheetah_spots(10)))"
# → 5 60
```

## note (local build)
xtensa-esp-elf `ld` ตัด path ที่ตัวอักษร non-ASCII → ถ้า build จาก path ที่มี unicode (เช่น `ψ/`)
esphome compile จะ fail (`cannot find firmware.map`). build จาก ASCII path = ผ่าน.
(reviewer CI ใช้ ASCII path อยู่แล้ว — ไม่กระทบ)
