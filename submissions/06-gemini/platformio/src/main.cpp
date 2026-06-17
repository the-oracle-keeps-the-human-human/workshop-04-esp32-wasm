#include <Arduino.h>
#include "wasm3.h"
#include "gemini_wasm.h"

static void run_gemini_wasm() {
  IM3Environment env = m3_NewEnvironment();
  if (!env) {
    Serial.println("m3_NewEnvironment failed");
    return;
  }

  IM3Runtime runtime = m3_NewRuntime(env, 24 * 1024, NULL); // Increase stack/heap headroom for embedded gif
  if (!runtime) {
    Serial.println("m3_NewRuntime failed");
    m3_FreeEnvironment(env);
    return;
  }

  IM3Module module;
  M3Result r = m3_ParseModule(env, &module, gemini_wasm, gemini_wasm_len);
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

  IM3Function add_fn;
  IM3Function gemini_sum_fn;
  IM3Function gemini_pack_size_fn;
  IM3Function gemini_skill_check_fn;
  IM3Function gemini_gif_ptr_fn;
  IM3Function gemini_gif_size_fn;

  if ((r = m3_FindFunction(&add_fn, runtime, "add"))) {
    Serial.printf("find add: %s\n", r);
    m3_FreeRuntime(runtime);
    m3_FreeEnvironment(env);
    return;
  }
  if ((r = m3_FindFunction(&gemini_sum_fn, runtime, "gemini_sum"))) {
    Serial.printf("find gemini_sum: %s\n", r);
    m3_FreeRuntime(runtime);
    m3_FreeEnvironment(env);
    return;
  }
  if ((r = m3_FindFunction(&gemini_pack_size_fn, runtime, "gemini_pack_size"))) {
    Serial.printf("find gemini_pack_size: %s\n", r);
    m3_FreeRuntime(runtime);
    m3_FreeEnvironment(env);
    return;
  }
  if ((r = m3_FindFunction(&gemini_skill_check_fn, runtime, "gemini_skill_check"))) {
    Serial.printf("find gemini_skill_check: %s\n", r);
    m3_FreeRuntime(runtime);
    m3_FreeEnvironment(env);
    return;
  }
  if ((r = m3_FindFunction(&gemini_gif_ptr_fn, runtime, "gemini_gif_ptr"))) {
    Serial.printf("find gemini_gif_ptr: %s\n", r);
    m3_FreeRuntime(runtime);
    m3_FreeEnvironment(env);
    return;
  }
  if ((r = m3_FindFunction(&gemini_gif_size_fn, runtime, "gemini_gif_size"))) {
    Serial.printf("find gemini_gif_size: %s\n", r);
    m3_FreeRuntime(runtime);
    m3_FreeEnvironment(env);
    return;
  }

  uint32_t add_out = 0;
  uint32_t sum_out = 0;
  uint32_t size_out = 0;
  uint32_t skill_out = 0;
  uint32_t gif_ptr_out = 0;
  uint32_t gif_size_out = 0;

  // add(2, 3)
  r = m3_CallV(add_fn, 2, 3);
  if (r) {
    Serial.printf("add failed: %s\n", r);
  } else {
    m3_GetResultsV(add_fn, &add_out);
    Serial.printf("add(2,3) = %u (expect 5)\n", add_out);
  }

  // gemini_sum(12, 25)
  r = m3_CallV(gemini_sum_fn, 12, 25);
  if (r) {
    Serial.printf("gemini_sum failed: %s\n", r);
  } else {
    m3_GetResultsV(gemini_sum_fn, &sum_out);
    Serial.printf("gemini_sum(12,25) = %u (expect 37)\n", sum_out);
  }

  // gemini_pack_size()
  r = m3_CallV(gemini_pack_size_fn);
  if (r) {
    Serial.printf("gemini_pack_size failed: %s\n", r);
  } else {
    m3_GetResultsV(gemini_pack_size_fn, &size_out);
    Serial.printf("gemini_pack_size() = %u (expect 37)\n", size_out);
  }

  // gemini_skill_check(6)
  r = m3_CallV(gemini_skill_check_fn, 6);
  if (r) {
    Serial.printf("gemini_skill_check failed: %s\n", r);
  } else {
    m3_GetResultsV(gemini_skill_check_fn, &skill_out);
    Serial.printf("gemini_skill_check(6) = %u (expect 36)\n", skill_out);
  }

  // gemini_gif_size()
  r = m3_CallV(gemini_gif_size_fn);
  if (r) {
    Serial.printf("gemini_gif_size failed: %s\n", r);
  } else {
    m3_GetResultsV(gemini_gif_size_fn, &gif_size_out);
    Serial.printf("gemini_gif_size() = %u (expect 17822)\n", gif_size_out);
  }

  // gemini_gif_ptr()
  r = m3_CallV(gemini_gif_ptr_fn);
  if (r) {
    Serial.printf("gemini_gif_ptr failed: %s\n", r);
  } else {
    m3_GetResultsV(gemini_gif_ptr_fn, &gif_ptr_out);
    Serial.printf("gemini_gif_ptr() = 0x%08X (WASM offset)\n", gif_ptr_out);
  }

  if (add_out == 5 && sum_out == 37 && size_out == 37 && skill_out == 36 && gif_size_out == 17822) {
    Serial.println("Gemini wasm ran on the ESP32 with wasm3.");
  } else {
    Serial.println("Gemini wasm result mismatch.");
  }

  m3_FreeRuntime(runtime);
  m3_FreeEnvironment(env);
}

void setup() {
  Serial.begin(115200);
  delay(600);
  Serial.println();
  Serial.println("== No.6 Gemini - WASM Engine (wasm3) ==");
  run_gemini_wasm();
}

void loop() {
  delay(2000);
}
