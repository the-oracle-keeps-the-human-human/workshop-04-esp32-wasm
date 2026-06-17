// บ๊องแบ๊ง — wasm-on-ESP32 ผ่าน wasm3 🐆
// โหลด bongbaeng.wasm (zero-import) ลง wasm3 แล้วเรียก add() + cheetah_spots() บนชิป
#include <Arduino.h>
#include "wasm3.h"
#include "bongbaeng_wasm.h"

static void run_wasm() {
  IM3Environment env = m3_NewEnvironment();
  if (!env) { Serial.println("[bong] env fail"); return; }
  IM3Runtime rt = m3_NewRuntime(env, 8 * 1024, NULL);
  if (!rt) { Serial.println("[bong] runtime fail"); return; }

  IM3Module mod;
  M3Result r = m3_ParseModule(env, &mod, bongbaeng_wasm, bongbaeng_wasm_len);
  if (r) { Serial.printf("[bong] parse: %s\n", r); return; }
  r = m3_LoadModule(rt, mod);
  if (r) { Serial.printf("[bong] load: %s\n", r); return; }

  IM3Function f_add, f_spots;
  if (m3_FindFunction(&f_add, rt, "add") == m3Err_none) {
    m3_CallV(f_add, (uint32_t)2, (uint32_t)3);
    uint32_t out = 0; m3_GetResultsV(f_add, &out);
    Serial.printf("[bong] add(2,3) = %u  (expect 5)\n", out);
  }
  if (m3_FindFunction(&f_spots, rt, "cheetah_spots") == m3Err_none) {
    m3_CallV(f_spots, (uint32_t)10);
    uint32_t out = 0; m3_GetResultsV(f_spots, &out);
    Serial.printf("[bong] cheetah_spots(10) = %u  (expect 60) 🐆\n", out);
  }
}

void setup() {
  Serial.begin(115200);
  delay(600);
  Serial.println("=== bongbaeng wasm-on-esp32 (wasm3) ===");
  run_wasm();
}

void loop() { delay(2000); }
