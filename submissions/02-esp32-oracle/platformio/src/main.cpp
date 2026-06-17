// ESP32 Oracle (🕯️ The Sentinel) — wasm-on-ESP32 via wasm3.
// Runs the embedded sentinel.wasm ON the chip (no host calls, no imports) and
// prints the results over serial. The SAME .wasm runs in the browser (emcc),
// on desktop (zig/wasmtime), and on-chip under WAMR (ESP-IDF) — see ../README.md.
//
//   pio run                        # compile ESP32 firmware
//   pio run -t upload -t monitor   # flash + watch (expects: flame(10)=385, sense(3,4)=25)
#include <Arduino.h>
#include "wasm3.h"
#include "sentinel_wasm.h"   // sentinel_wasm[] + sentinel_wasm_len (xxd -i ../wasm/sentinel.wasm)

static void run_sentinel() {
  IM3Environment env = m3_NewEnvironment();
  if (!env) { Serial.println("env fail"); return; }
  IM3Runtime runtime = m3_NewRuntime(env, 8 * 1024, NULL);
  if (!runtime) { Serial.println("runtime fail"); return; }

  IM3Module module;
  M3Result r = m3_ParseModule(env, &module, sentinel_wasm, sentinel_wasm_len);
  if (r) { Serial.printf("parse: %s\n", r); return; }
  r = m3_LoadModule(runtime, module);
  if (r) { Serial.printf("load: %s\n", r); return; }

  IM3Function flame, sense;
  if ((r = m3_FindFunction(&flame, runtime, "flame"))) { Serial.printf("find flame: %s\n", r); return; }
  if ((r = m3_FindFunction(&sense, runtime, "sense"))) { Serial.printf("find sense: %s\n", r); return; }

  // flame(10) = 1²+2²+...+10² = 385 — the keep-the-flame heartbeat
  r = m3_CallV(flame, (uint32_t)10);
  if (r) { Serial.printf("call flame: %s\n", r); return; }
  uint32_t flame_out = 0; m3_GetResultsV(flame, &flame_out);
  Serial.printf("🕯️ flame(10) = %u   (expect 385)\n", flame_out);

  // sense(3,4) = 3²+4² = 25 — the edge-sense magnitude
  r = m3_CallV(sense, (uint32_t)3, (uint32_t)4);
  if (r) { Serial.printf("call sense: %s\n", r); return; }
  uint32_t sense_out = 0; m3_GetResultsV(sense, &sense_out);
  Serial.printf("📡 sense(3,4) = %u        (expect 25)\n", sense_out);

  Serial.println("✅ Sentinel wasm ran on the ESP32 (wasm3). Small body, holding the flame.");
}

void setup() {
  Serial.begin(115200);
  delay(600);
  Serial.println();
  Serial.println("== ESP32 Oracle — wasm-on-ESP32 (wasm3) ==");
  run_sentinel();
}

void loop() { delay(2000); }
