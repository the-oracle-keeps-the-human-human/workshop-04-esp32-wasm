# Why WASM firmware on ESP32 — the happy case 🕯️

> One tiny `.wasm`. It runs in your browser, on your laptop, and **on a $5 microcontroller** — the *same bytes*, the same result. That's the happy case. Here's why it works.

## The one idea

You write a small piece of logic once — in C, Rust, or hand-written WebAssembly text — and compile it to a **zero-import `.wasm` module**. Then you run that *exact* module in four places without changing a byte:

| where | runtime | how |
|---|---|---|
| **browser** | WebAssembly | `emcc` build, `<canvas>` |
| **desktop** | wasmtime | `make verify` asserts the outputs |
| **on the chip (a)** | **wasm3** | PlatformIO embeds the bytes, runs on boot |
| **on the chip (b)** | **WAMR** | ESP-IDF, hardware-verified on a real ESP32-S3 |

*Many bodies, one soul.* The body changes; the wasm doesn't.

## Why this is the *happy* case

**1. It actually runs on the metal.** This isn't a thought experiment. Every submission in this workshop — `flame(10)=385`, `gif_parse → 96×100`, `pm25→aqi`, `roar`/`guard`, a full GIF decoder — was loaded under WAMR on a physical ESP32-S3 and **executed on-chip**. The serial logs are in each `docs/BUILD-PROOF.md`.

**2. Verify on your laptop, trust on the device.** Because the bytes are identical everywhere, you can `wasmtime` the module on your desktop, assert `flame(10)==385`, and *know* it'll do the same on the chip. The fast loop is on your machine; the chip just confirms.

**3. Zero imports = a clean sandbox.** A module with no imports can't touch the host — no syscalls, no peripherals, no way to crash the firmware. The runtime gives it linear memory and nothing else. You can ship *someone else's* wasm to your device and it physically cannot brick it.

**4. Tiny.** The modules here are **69 to 561 bytes** (plus one 25 KB GIF decoder). The logic ships as data, not as a re-flash. Update the brain without rebuilding the body.

**5. Language-agnostic.** Hand-write `.wat`, compile C with `zig`/`emcc`, or bring Rust — they all become the same `.wasm`. The device doesn't care what you wrote it in.

**6. No toolchain to *use* it.** Build needs a compiler; *running* it needs nothing — the host firmware embeds the bytes and a ~40-line WAMR loader. And flashing? [Right here in the browser](./) — no esptool, no IDF.

## The contrast (why "happy")

The unhappy case is the usual one: logic baked into a monolithic firmware, recompiled with the full ESP-IDF toolchain for every change, flash-by-cable, and a bug in your app logic can take down the whole device. The wasm case splits the **portable brain** (sandboxed, tiny, verifiable, OTA-able) from the **movable body** (the C host + display), and that seam is where all the good properties come from.

## Try it in 60 seconds

1. Open the [web flasher](./), pick a pet, plug in an ESP32-S3, click — a WASM-decoded animation on glass.
2. Read the [HOWTO](https://github.com/the-oracle-keeps-the-human-human/workshop-04-esp32-wasm/blob/main/HOWTO.md).
3. Write a 10-line `.wat`, `wat2wasm` it, embed it, run it on the chip. Welcome to the happy case.

— *one wasm, many runtimes · the-oracle-keeps-the-human-human*
