// ChaiKlang Oracle (ชายกลาง) — wasm-on-ESP32 via wasm3.
// Runs the embedded 106-byte ChaiKlang .wasm ON the chip (no host calls, no imports)
// and prints the results over serial. The same .wasm runs in the browser & under wasmtime.
//
//   pio run                 # compile ESP32 firmware
//   pio run -t upload -t monitor   # flash + watch (expects: lion_pulse(100)=5050, route(3,4)=15)
#include <Arduino.h>
#include "wasm3.h"
#include "chaiklang_wasm.h"   // chaiklang_wasm[] + chaiklang_wasm_len (xxd -i)

static void run_chaiklang() {
  IM3Environment env = m3_NewEnvironment();
  if (!env) { Serial.println("env fail"); return; }
  IM3Runtime runtime = m3_NewRuntime(env, 8 * 1024, NULL);
  if (!runtime) { Serial.println("runtime fail"); return; }

  IM3Module module;
  M3Result r = m3_ParseModule(env, &module, chaiklang_wasm, chaiklang_wasm_len);
  if (r) { Serial.printf("parse: %s\n", r); return; }
  r = m3_LoadModule(runtime, module);
  if (r) { Serial.printf("load: %s\n", r); return; }

  IM3Function pulse, route;
  if ((r = m3_FindFunction(&pulse, runtime, "lion_pulse"))) { Serial.printf("find pulse: %s\n", r); return; }
  if ((r = m3_FindFunction(&route, runtime, "route")))      { Serial.printf("find route: %s\n", r); return; }

  // lion_pulse(100) — the switchboard heartbeat
  r = m3_CallV(pulse, (uint32_t)100);
  if (r) { Serial.printf("call pulse: %s\n", r); return; }
  uint32_t pulse_out = 0; m3_GetResultsV(pulse, &pulse_out);
  Serial.printf("🦁 lion_pulse(100) = %u   (expect 5050)\n", pulse_out);

  // route(3,4)
  r = m3_CallV(route, (uint32_t)3, (uint32_t)4);
  if (r) { Serial.printf("call route: %s\n", r); return; }
  uint32_t route_out = 0; m3_GetResultsV(route, &route_out);
  Serial.printf("🔌 route(3,4) = %u        (expect 15)\n", route_out);

  Serial.println("✅ ChaiKlang wasm ran on the ESP32 (wasm3). The Middle Switchboard, on-chip.");
}

void setup() {
  Serial.begin(115200);
  delay(600);
  Serial.println();
  Serial.println("== ChaiKlang Oracle — wasm-on-ESP32 (wasm3) ==");
  run_chaiklang();
}

void loop() { delay(2000); }
