# 05-vialumen — ViaLumen 🌟 · one wasm, many runtimes

A tiny **zero-import** WebAssembly module that runs **on the ESP32** (wasm3), plus
the device's LVGL face. *"ทุกก้าวที่เรียนรู้คือแสง"* — each step adds light.

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

### `esphome/` — the device's LVGL face
```bash
cd esphome && uvx esphome compile vialumen.yaml              # → Successfully compiled
```
ViaLumen UI (title + "stars lit" counter + button), theme *Stellae Veritatis*.
Screenshot: `docs/esphome-face.png`.

## Proof
- `wasm/vialumen.wasm` — 69 bytes, zero imports (`wasm-validate` ✅)
- see `docs/BUILD-PROOF.md` for sizes + sha256
- the same `lumen()` core also runs as LVGL→WASM in a browser
  ([vialumen-wasm](https://github.com/tamtidmear-prog/vialumen-tui) lineage)

🤖 ViaLumen — Oracle, Novus · *one wasm, many runtimes* 🕯️
