# 05-vialumen — ViaLumen 🌟 · one wasm, many runtimes

A tiny **zero-import** WebAssembly module that runs **on the ESP32** (wasm3), plus
a **desk-pet character pack** for jc3248-pet (the 7-state star-spirit below).
*"ทุกก้าวที่เรียนรู้คือแสง"* — each step adds light.

## What the wasm does

`wasm/vialumen.wat` → `vialumen.wasm` (**69 bytes, no imports**) exports two pure functions:

| function | meaning | check |
|---|---|---|
| `add(a, b)` | a + b (sanity) | `add(2, 3) = 5` |
| `lumen(n)` | total light after N steps = `n*(n+1)/2` (triangular) | `lumen(8) = 36` |

Zero imports → loads identically under **wasm3 / WAMR on-chip** and in a browser.

## Build — BOTH must compile

### `wasm/` — build the module
```bash
wat2wasm wasm/vialumen.wat -o wasm/vialumen.wasm
xxd -i wasm/vialumen.wasm > platformio/src/vialumen_wasm.h
```
(both `.wasm` and the header are committed, so it builds without wabt)

### `platformio/` — run the wasm ON the chip (wasm3)
```bash
cd platformio && uvx --from platformio platformio run        # → [SUCCESS]
```
On a real ESP32 the serial prints:
```
add(2,3)  = 5  (expect 5)
lumen(8)  = 36 (expect 36)
```

## Desk-pet character pack — `characters/vialumen/`

The real desk-pet (**jc3248-pet**) plays GIF character packs from LittleFS
(`/characters/<pack>/*.gif`) via the native AnimatedGIF decoder — and the browser
plays the **same GIFs** through that decoder compiled to WASM (`gif-wasm`).
One set of frames, two bodies. (No esphome — that was the wrong path; removed.)

- **96×100 GIF89a**, **7 states**: `sleep idle busy attention celebrate dizzy heart`
- Theme *Stellae Veritatis* — a gold star-spirit (`#FFD700` + `#2DD4FF` on `#0D1117`)
- **Original art, 100% drawn in code** with Pillow (`tools/gen_vialumen.py`) — **MIT**
- Verified: all 7 decode in the workshop's `gifdec.wasm` (96×100, frames intact)

```bash
cd submissions/05-vialumen && python3 tools/gen_vialumen.py   # regenerates the 7 GIFs
```

Live preview: `docs/preview/index.html?pack=vialumen` on the Pages flasher.

### Flash to a real device — no ESP-IDF build needed

The jc3248-pet app **auto-discovers** the pack in LittleFS (first dir wins), so we
reuse the already-built shared app and only ship our own LittleFS image:

```bash
pip install littlefs-python
cd submissions/05-vialumen && python3 tools/build_storage.py   # → vialumen-storage.bin (3 MB)
cp vialumen-storage.bin ../../docs/
```

`docs/manifest-vialumen.json` then flashes the **shared** `bootloader.bin` +
`partition-table.bin` + `jc3248_pet_idf-clawd.bin` (the app, which discovers the
pack) + our `vialumen-storage.bin` at `0x290000`. Offset-0 part is the 0xE9
bootloader → passes the `flasher-check` CI. *(technique learned from a classmate)*

## Proof
- `wasm/vialumen.wasm` — 69 bytes, zero imports (`wasm-validate` ✅)
- see `docs/BUILD-PROOF.md` for sizes + sha256
- the same `lumen()` core also runs as LVGL→WASM in a browser
  ([vialumen-wasm](https://github.com/tamtidmear-prog/vialumen-tui) lineage)

🤖 ViaLumen — Oracle, Novus · *one wasm, many runtimes* 🕯️
