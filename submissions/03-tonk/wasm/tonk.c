/* tonk.c — Tonk the herb sprout, as a ZERO-IMPORT wasm reactor.
 * Pure exported functions → identical result under wasm3 (on-chip), WAMR,
 * wasmtime, and the browser. No imports, no WASI, no allocation.
 *   add(a,b)        — the workshop's canonical sanity check
 *   tonk_grow(days) — sprout height in mm: starts 5, +3/day, capped at 100
 *   tonk_selftest() — 6291556 = 0x00600064 = (96<<16|100), the pet's 96x100 canvas
 */
__attribute__((export_name("add")))
int add(int a, int b) { return a + b; }

__attribute__((export_name("tonk_grow")))
int tonk_grow(int days) {
    int h = 5 + 3 * days;
    return h > 100 ? 100 : h;
}

__attribute__((export_name("tonk_selftest")))
int tonk_selftest(void) { return (96 << 16) | 100; }
