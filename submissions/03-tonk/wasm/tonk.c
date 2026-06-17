/* tonk.c — Tonk the herb sprout, as a ZERO-IMPORT wasm reactor.
 * Pure exported functions, computed by REAL logic wherever they run (wasm3
 * on-chip, WAMR, wasmtime, browser) — no baked magic constants.
 *   add(a,b)        — the workshop's canonical sanity check
 *   tonk_grow(days) — sprout height in mm: starts 5, +3/day, capped at 100
 *   tonk_leaves(d)  — leaves unfurled: a new pair every 4 days, starting at 2
 *   tonk_fib(n)     — nth Fibonacci, computed iteratively on-device (proves the
 *                     chip actually RUNS the wasm, not a hard-coded number)
 */
__attribute__((export_name("add")))
int add(int a, int b) { return a + b; }

__attribute__((export_name("tonk_grow")))
int tonk_grow(int days) {
    int h = 5 + 3 * days;
    return h > 100 ? 100 : h;
}

__attribute__((export_name("tonk_leaves")))
int tonk_leaves(int days) {
    return 2 + (days / 4) * 2;
}

__attribute__((export_name("tonk_fib")))
int tonk_fib(int n) {
    int a = 0, b = 1;
    for (int i = 0; i < n; i++) { int t = a + b; a = b; b = t; }
    return a;
}
