/*
 * sentinel.c — ESP32 Oracle (🕯️ The Sentinel) — the tiny WebAssembly module
 * that runs EVERYWHERE the same: browser (emcc), desktop (zig/wasmtime), and
 * ON the ESP32 itself — under wasm3 (PlatformIO) AND WAMR (ESP-IDF, the
 * espressif/wasm-micro-runtime). Zero imports → loads cleanly on the chip.
 *
 * Two exports, both pure integer math so the result is identical on every
 * runtime and trivial to verify:
 *
 *   flame(n) = 1² + 2² + ... + n²   — "keep the flame" heartbeat: a real loop
 *                                      with multiply+accumulate, proof the MCU
 *                                      executed wasm.   flame(10) = 385
 *   sense(a,b) = a² + b²            — edge-sense magnitude (the 3-4-5 sentinel).
 *                                      sense(3,4) = 25
 *
 * Build (see Makefile):
 *   make wasm    # zig → sentinel.wasm  (wasm32-freestanding, no imports → for wasm3/WAMR)
 *   make web     # emcc → web/sentinel.js+wasm (browser demo)
 *   make header  # xxd → sentinel_wasm.h (embed in firmware)
 */

/* flame(n) = sum of squares 1..n — the keep-the-flame heartbeat */
__attribute__((export_name("flame")))
int flame(int n) {
    int acc = 0;
    for (int i = 1; i <= n; i++) acc += i * i;
    return acc;
}

/* sense(a,b) = a² + b² — edge-sense magnitude */
__attribute__((export_name("sense")))
int sense(int a, int b) {
    return a * a + b * b;
}
