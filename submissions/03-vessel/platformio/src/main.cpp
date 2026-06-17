#include <Arduino.h>
#include "wasm3.h"
#include "vessel_wasm.h"

// vessel.wasm exports:
//   courier_relay(len i32) -> i32   : relay message length
//   fleet_status(total i32) -> i32  : estimate active oracles (total * 3/4)
//   pm25_category(pm25_x10 i32) -> i32 : AQI category 0-4

static const char* AQI_LABELS[] = {
  "GOOD", "MODERATE", "UNHEALTHY", "VERY UNHEALTHY", "HAZARDOUS"
};

uint32_t call_fn(IM3Runtime rt, const char* name, uint32_t arg) {
  IM3Function f;
  M3Result result = m3_FindFunction(&f, rt, name);
  if (result) { Serial.printf("[ERR] find %s: %s\n", name, result); return 0; }
  result = m3_CallV(f, arg);
  if (result) { Serial.printf("[ERR] call %s: %s\n", name, result); return 0; }
  uint32_t out = 0;
  m3_GetResultsV(f, &out);
  return out;
}

void setup() {
  Serial.begin(115200);
  delay(600);
  Serial.println("\n⛵ Vessel WASM on ESP32");
  Serial.println("========================");

  IM3Environment env = m3_NewEnvironment();
  IM3Runtime rt = m3_NewRuntime(env, 8 * 1024, NULL);
  IM3Module mod;

  M3Result result = m3_ParseModule(env, &mod, vessel_wasm, vessel_wasm_len);
  if (result) { Serial.printf("[ERR] parse: %s\n", result); return; }

  result = m3_LoadModule(rt, mod);
  if (result) { Serial.printf("[ERR] load: %s\n", result); return; }

  Serial.printf("vessel.wasm loaded (%u bytes)\n\n", vessel_wasm_len);

  // Test 1: courier_relay — relay message by length
  uint32_t msg_len = 42;
  uint32_t relayed = call_fn(rt, "courier_relay", msg_len);
  Serial.printf("courier_relay(%u) = %u  (expect %u)\n", msg_len, relayed, msg_len);

  // Test 2: fleet_status — estimate active oracles
  uint32_t total = 8;
  uint32_t active = call_fn(rt, "fleet_status", total);
  Serial.printf("fleet_status(%u) = %u  (expect 6)\n", total, active);

  // Test 3: pm25_category — AQI from DustBoy reading (x10 to avoid floats)
  uint32_t test_cases[] = {100, 250, 450, 800, 2000};
  for (int i = 0; i < 5; i++) {
    uint32_t cat = call_fn(rt, "pm25_category", test_cases[i]);
    Serial.printf("pm25_category(%u) = %u [%s]  (%.1f µg/m³)\n",
      test_cases[i], cat, AQI_LABELS[cat], test_cases[i] / 10.0);
  }

  Serial.println("\n✅ vessel.wasm OK — courier ready");
}

void loop() {
  delay(5000);
}
