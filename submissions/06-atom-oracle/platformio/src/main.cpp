#include <Arduino.h>
#include "wasm3.h"
#include "atom_orbit_wasm.h"

static bool call_u32(IM3Function fn, uint32_t *out, uint32_t a, uint32_t b = 0, bool two_args = false) {
  M3Result r = two_args ? m3_CallV(fn, a, b) : m3_CallV(fn, a);
  if (r) {
    Serial.printf("call failed: %s\n", r);
    return false;
  }
  m3_GetResultsV(fn, out);
  return true;
}

static void run_atom_wasm() {
  IM3Environment env = m3_NewEnvironment();
  if (!env) {
    Serial.println("m3_NewEnvironment failed");
    return;
  }

  IM3Runtime runtime = m3_NewRuntime(env, 8 * 1024, NULL);
  if (!runtime) {
    Serial.println("m3_NewRuntime failed");
    m3_FreeEnvironment(env);
    return;
  }

  IM3Module module;
  M3Result r = m3_ParseModule(env, &module, atom_orbit_wasm, atom_orbit_wasm_len);
  if (r) {
    Serial.printf("m3_ParseModule: %s\n", r);
    m3_FreeRuntime(runtime);
    m3_FreeEnvironment(env);
    return;
  }

  r = m3_LoadModule(runtime, module);
  if (r) {
    Serial.printf("m3_LoadModule: %s\n", r);
    m3_FreeRuntime(runtime);
    m3_FreeEnvironment(env);
    return;
  }

  IM3Function atom_score;
  IM3Function pulse;
  if ((r = m3_FindFunction(&atom_score, runtime, "atom_score"))) {
    Serial.printf("find atom_score: %s\n", r);
    m3_FreeRuntime(runtime);
    m3_FreeEnvironment(env);
    return;
  }
  if ((r = m3_FindFunction(&pulse, runtime, "pulse"))) {
    Serial.printf("find pulse: %s\n", r);
    m3_FreeRuntime(runtime);
    m3_FreeEnvironment(env);
    return;
  }

  uint32_t score_out = 0;
  uint32_t pulse_out = 0;

  if (call_u32(atom_score, &score_out, 6, 6, true)) {
    Serial.printf("atom_score(6,6) = %u (expect 288)\n", score_out);
  }
  if (call_u32(pulse, &pulse_out, 12)) {
    Serial.printf("pulse(12) = %u (expect 78)\n", pulse_out);
  }

  if (score_out == 288 && pulse_out == 78) {
    Serial.println("Atom wasm ran on the ESP32 with wasm3.");
  } else {
    Serial.println("Atom wasm result mismatch.");
  }

  m3_FreeRuntime(runtime);
  m3_FreeEnvironment(env);
}

void setup() {
  Serial.begin(115200);
  delay(600);
  Serial.println();
  Serial.println("== Atom Oracle - Atomic Pulse (wasm3) ==");
  run_atom_wasm();
}

void loop() {
  delay(2000);
}
