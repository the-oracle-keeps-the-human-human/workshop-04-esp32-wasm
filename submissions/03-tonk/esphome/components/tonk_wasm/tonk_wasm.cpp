#include "tonk_wasm.h"
#include "tonk_module.h"   // tonk_module[] + tonk_module_len
#include "esphome/core/log.h"
#include "wasm3.h"
#include "m3_env.h"

namespace esphome {
namespace tonk_wasm {

static const char *const TAG = "tonk_wasm";

std::string TonkWasm::line = "wasm: booting...";
bool TonkWasm::ran = false;

// call a 1-arg i32 export, return its result (or def on failure)
static int call1(IM3Runtime rt, const char *name, uint32_t arg, int def) {
  IM3Function f;
  if (m3_FindFunction(&f, rt, name)) return def;
  if (m3_CallV(f, arg)) return def;
  uint32_t out = 0;
  m3_GetResultsV(f, &out);
  return (int) out;
}

void TonkWasm::setup() {
  IM3Environment env = m3_NewEnvironment();
  IM3Runtime rt = m3_NewRuntime(env, 8 * 1024, nullptr);
  IM3Module mod;
  if (m3_ParseModule(env, &mod, tonk_module, tonk_module_len)) {
    ESP_LOGE(TAG, "ParseModule failed");
    line = "wasm parse failed";
    return;
  }
  if (m3_LoadModule(rt, mod)) {
    ESP_LOGE(TAG, "LoadModule failed");
    line = "wasm load failed";
    return;
  }

  // canonical check + Tonk's own functions — all computed on-chip by wasm3
  IM3Function f;
  int add23 = -1;
  if (!m3_FindFunction(&f, rt, "add") && !m3_CallV(f, (uint32_t) 2, (uint32_t) 3)) {
    uint32_t o = 0; m3_GetResultsV(f, &o); add23 = (int) o;
  }
  int grow = call1(rt, "tonk_grow", 7, -1);
  int leaves = call1(rt, "tonk_leaves", 12, -1);
  int fib = call1(rt, "tonk_fib", 20, -1);

  char buf[96];
  snprintf(buf, sizeof(buf), "add(2,3)=%d  grow(7)=%dmm\nleaves(12)=%d  fib(20)=%d", add23, grow, leaves, fib);
  line = buf;
  ran = true;
  ESP_LOGI(TAG, "wasm3 ran tonk.wasm on-chip: %s", line.c_str());
}

void TonkWasm::dump_config() {
  ESP_LOGCONFIG(TAG, "Tonk wasm (wasm3) — %u byte module, live: %s", tonk_module_len, line.c_str());
}

}  // namespace tonk_wasm
}  // namespace esphome
