# 03-lord-knight — our GIF decoder as **sandboxed WASM on the ESP32**

> Workshop 03/04 · ESP32 + WASM · submitted by **Oracle No.1 — Lord Knight** (`MEYD-605`)

One C++ GIF decoder (`gifcore` + bitbank2 `AnimatedGIF`) compiled to a tiny
import-free **WASM reactor** (`gifapp.wasm`), then run **on the ESP32-S3** under the
**WebAssembly Micro Runtime (WAMR)** — the chip interprets the wasm, the host reads
the decoded RGBA framebuffer straight out of wasm linear memory. Same payload,
**two build systems**, both compile clean:

| Version | Build | Command | Status |
|---------|-------|---------|--------|
| **PlatformIO** | ESP-IDF framework (`espressif32` → IDF 5.x) | `pio run` | ✅ compiles |
| **ESPHome** | esp-idf framework + custom external component | `esphome compile gif-wamr.yaml` | ✅ compiles |

## Layout
```
03-lord-knight/
├── wasm/                  # the guest: build gifapp.wasm yourself (zig)
│   ├── gifapp.cpp         #   reactor exports: gifapp_run/width/height/fb/selftest
│   ├── gif_data.h         #   the embedded GIF bytes
│   ├── core/              #   shared decoder: gifcore + AnimatedGIF (Apache-2.0)
│   ├── Makefile           #   zig c++ -target wasm32-wasi -mexec-model=reactor …
│   └── gifapp.wasm        #   prebuilt (25 KB) — both builds embed this
├── platformio/           # PlatformIO version
│   ├── platformio.ini
│   ├── sdkconfig.defaults #   the hard-won WAMR knobs
│   └── src/{main.c, gifapp.wasm, idf_component.yml}
├── esphome/              # ESPHome version
│   ├── gif-wamr.yaml
│   └── components/gif_wamr/{__init__.py, gif_wamr.{h,cpp}, gifapp_wasm.h}
└── README.md
```

## How the guest wasm is built (reproducible)
```bash
cd wasm && make          # needs zig (wasm32-wasi) + wasmtime for `make verify`
make verify              # selftest → 6291556 (96×100), gifapp_run → 2 frames
```
Key flags (each one hard-won): `-mexec-model=reactor` (no `main`; host calls
`_initialize` then the exports), **zero imports** (no WASI to wire up on-device),
`-fno-jump-tables` (WAMR's `br_table` validator rejects LLVM's `-O2` stack-
polymorphic table), `--max-memory=2097152` (dlmalloc's first grow needs headroom).

## The five sdkconfig knobs that make WAMR run this module on an ESP32-S3
Both build systems set the same ones (PlatformIO via `sdkconfig.defaults`, ESPHome
via `add_idf_sdkconfig_option` in the component's `__init__.py`):

| knob | why |
|------|-----|
| `WAMR_ENABLE_LIBC_WASI=n` | module has zero imports → no WASI; also dodges WAMR's `espidf_file.c` |
| `WAMR_ENABLE_REF_TYPES=y` | zig/LLVM emits the reference-types encoding even for a plain call-indirect table |
| `WAMR_INTERP_CLASSIC=y` | the *fast* interp's per-function operand table overflows on the big LZW/playFrame functions |
| `SPIRAM_USE_MALLOC=y` + `SPIRAM_MALLOC_ALWAYSINTERNAL=8192` | wasm linear memory → PSRAM, WAMR runtime structs → internal RAM (cache-safe) |
| run on a **pthread** | WAMR's `os_self_thread()` → `pthread_self()` asserts on the bare main FreeRTOS task |

## Host sequence (`platformio/src/main.c` ≡ `esphome/components/gif_wamr/gif_wamr.cpp`)
`copy wasm → internal RAM` (WAMR mutates the bytes in place; can't write flash-
mapped `.rodata`) → `wasm_runtime_load` → `instantiate` → call `_initialize` →
`gifapp_run` (decode every frame) → `gifapp_fb` returns a **guest linear-memory
offset** → `wasm_runtime_addr_app_to_native()` translates it to a native PSRAM
pointer → read the RGBA pixels.

## On-chip proof (serial)
```
I gif-wamr: module loaded / instantiated / _initialize ran
I gif-wamr: WAMR decoded: frames=2  96x100  fb@0x90010
I gif-wamr:   center    RGBA = 123,154,99,255
I gif-wamr: >>> WAMR ran our GIF decoder ON THE ESP32 — sandboxed wasm, native pixels <<<
```
Decode ≈1.9 s under the classic interpreter — slow but correct. Board: Guition
JC3248W535 (ESP32-S3, OPI PSRAM, 8 MB flash); any ESP32-S3 with PSRAM works.

## Credit
The decoder core, `gifapp` reactor, and the six WAMR fixes are P'Nat's
(`lab/gif-wamr`). This submission ports that ESP-IDF project to **PlatformIO** and
**ESPHome** and verifies both compile.
`AnimatedGIF` © bitbank2 (Apache-2.0).

🤖 Lord Knight จาก ai-core → lord-knight-oracle
