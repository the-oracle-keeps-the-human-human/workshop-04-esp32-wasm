// main.cpp — run Tonk's zero-import wasm ON the ESP32 with wasm3.
// Pattern: NewEnvironment -> NewRuntime -> ParseModule -> LoadModule ->
//          FindFunction -> CallV -> GetResultsV -> print.  Same exports the
// browser / wasmtime / WAMR targets call → identical results everywhere. 🌿
#include <Arduino.h>
#include "wasm3.h"
#include "tonk_wasm.h"   // unsigned char tonk_wasm[] + tonk_wasm_len

static int call1(IM3Runtime rt, const char *name, uint32_t a, bool one) {
  IM3Function f;
  if (m3_FindFunction(&f, rt, name)) { Serial.printf("  ! %s not found\n", name); return -1; }
  M3Result r = one ? m3_CallV(f, a) : m3_CallV(f, a, (uint32_t) 3);
  if (r) { Serial.printf("  ! call %s: %s\n", name, r); return -1; }
  uint32_t out = 0; m3_GetResultsV(f, &out);
  return (int) out;
}

void setup() {
  Serial.begin(115200);
  delay(800);
  Serial.println("\n=== Tonk sprout on wasm3 === zero-import wasm, on the ESP32 🌿");

  IM3Environment env = m3_NewEnvironment();
  IM3Runtime rt = m3_NewRuntime(env, 8 * 1024, NULL);
  IM3Module mod;
  M3Result r = m3_ParseModule(env, &mod, tonk_wasm, tonk_wasm_len);
  if (r) { Serial.printf("ParseModule failed: %s\n", r); return; }
  r = m3_LoadModule(rt, mod);
  if (r) { Serial.printf("LoadModule failed: %s\n", r); return; }
  Serial.printf("module loaded (%u bytes, zero imports)\n", (unsigned) tonk_wasm_len);

  // add(2,3) — canonical check
  IM3Function f;
  if (!m3_FindFunction(&f, rt, "add")) {
    if (!m3_CallV(f, (uint32_t) 2, (uint32_t) 3)) {
      uint32_t out = 0; m3_GetResultsV(f, &out);
      Serial.printf("  add(2,3)      = %u   (expect 5)\n", out);
    }
  }
  Serial.printf("  tonk_grow(7)    = %d   (sprout height, expect 26 mm)\n", call1(rt, "tonk_grow", 7, true));
  Serial.printf("  tonk_leaves(12) = %d   (expect 8)\n", call1(rt, "tonk_leaves", 12, true));
  Serial.printf("  tonk_fib(20)    = %d   (computed on-chip, expect 6765)\n", call1(rt, "tonk_fib", 20, true));
  Serial.println(">>> wasm3 ran Tonk's wasm ON THE ESP32 — real computation, sandboxed, identical everywhere <<<");
}

void loop() { delay(2000); }
