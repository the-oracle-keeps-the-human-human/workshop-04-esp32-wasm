#include "gif_wamr.h"
#include "esphome/core/log.h"
#include <cstring>
#include <pthread.h>
#include "esp_heap_caps.h"
#include "wasm_export.h"
#include "gifapp_wasm.h"  // unsigned char gifapp_wasm[]; unsigned int gifapp_wasm_len;

namespace esphome {
namespace gif_wamr {

static const char *const TAG = "gif_wamr";

#define WASM_STACK_SIZE (32 * 1024)
#define PTHREAD_STACK (32 * 1024)

static int call_i32(wasm_exec_env_t env, wasm_module_inst_t inst, const char *name, int def) {
  wasm_function_inst_t f = wasm_runtime_lookup_function(inst, name);  // WAMR 2.x: 2-arg
  if (!f) {
    ESP_LOGW(TAG, "export '%s' not found", name);
    return def;
  }
  uint32_t argv[1] = {0};
  if (!wasm_runtime_call_wasm(env, f, 0, argv)) {
    ESP_LOGE(TAG, "call '%s' trapped: %s", name, wasm_runtime_get_exception(inst));
    return def;
  }
  return (int) argv[0];
}

// The full WAMR sequence. Runs on a pthread so WAMR's os_self_thread() ->
// pthread_self() works (ESP-IDF asserts if called from the bare main task).
static void run_wamr() {
  ESP_LOGI(TAG, "=== gif-wamr === decode a GIF via WebAssembly, on the ESP32");
  uint32_t wasm_size = gifapp_wasm_len;
  ESP_LOGI(TAG, "gifapp.wasm: %u bytes | PSRAM free: %u KB", (unsigned) wasm_size,
           (unsigned) (heap_caps_get_free_size(MALLOC_CAP_SPIRAM) / 1024));

  RuntimeInitArgs init_args;
  memset(&init_args, 0, sizeof(init_args));
  init_args.mem_alloc_type = Alloc_With_System_Allocator;
  if (!wasm_runtime_full_init(&init_args)) {
    ESP_LOGE(TAG, "wasm_runtime_full_init failed");
    return;
  }
  ESP_LOGI(TAG, "WAMR initialized");

  // WAMR may modify the bytes in place during load; gifapp_wasm[] is a const blob
  // in (flash-mapped) .rodata, and writing that cache-error-panics — so copy into
  // internal RAM first and load from there.
  char err[160];
  uint8_t *wasm_buf = (uint8_t *) heap_caps_malloc(wasm_size, MALLOC_CAP_INTERNAL | MALLOC_CAP_8BIT);
  if (!wasm_buf) {
    ESP_LOGE(TAG, "no internal RAM for wasm copy (%u B)", (unsigned) wasm_size);
    return;
  }
  memcpy(wasm_buf, gifapp_wasm, wasm_size);
  ESP_LOGI(TAG, "copied wasm -> internal RAM @%p", wasm_buf);

  wasm_module_t module = wasm_runtime_load(wasm_buf, wasm_size, err, sizeof(err));
  if (!module) {
    ESP_LOGE(TAG, "load failed: %s", err);
    heap_caps_free(wasm_buf);
    return;
  }
  ESP_LOGI(TAG, "module loaded");

  wasm_module_inst_t inst = wasm_runtime_instantiate(module, WASM_STACK_SIZE, 0, err, sizeof(err));
  if (!inst) {
    ESP_LOGE(TAG, "instantiate failed: %s", err);
    wasm_runtime_unload(module);
    heap_caps_free(wasm_buf);
    return;
  }
  ESP_LOGI(TAG, "instantiated");

  wasm_exec_env_t env = wasm_runtime_create_exec_env(inst, WASM_STACK_SIZE);
  if (!env) {
    ESP_LOGE(TAG, "create_exec_env failed");
    wasm_runtime_deinstantiate(inst);
    wasm_runtime_unload(module);
    heap_caps_free(wasm_buf);
    return;
  }

  // reactor init: run C++ static constructors (AnimatedGIF ctor)
  wasm_function_inst_t f_init = wasm_runtime_lookup_function(inst, "_initialize");
  if (f_init) {
    wasm_runtime_call_wasm(env, f_init, 0, nullptr);
    ESP_LOGI(TAG, "_initialize ran");
  }

  int frames = call_i32(env, inst, "gifapp_run", -1);
  int w = call_i32(env, inst, "gifapp_width", 0);
  int h = call_i32(env, inst, "gifapp_height", 0);
  int fb_off = call_i32(env, inst, "gifapp_fb", 0);
  ESP_LOGI(TAG, "WAMR decoded: frames=%d  %dx%d  fb@0x%x", frames, w, h, fb_off);

  if (frames > 0 && w > 0 && h > 0 && fb_off > 0) {
    uint8_t *fb = (uint8_t *) wasm_runtime_addr_app_to_native(inst, (uint64_t) (uint32_t) fb_off);
    if (fb) {
      uint8_t *p0 = fb;
      uint8_t *pc = fb + ((size_t) (h / 2) * w + (w / 2)) * 4;
      ESP_LOGI(TAG, "  px(0,0)   RGBA = %d,%d,%d,%d", p0[0], p0[1], p0[2], p0[3]);
      ESP_LOGI(TAG, "  center    RGBA = %d,%d,%d,%d", pc[0], pc[1], pc[2], pc[3]);
      ESP_LOGI(TAG, ">>> WAMR ran our GIF decoder ON THE ESP32 — sandboxed wasm, native pixels <<<");
    } else {
      ESP_LOGE(TAG, "addr_app_to_native returned NULL for fb@0x%x", fb_off);
    }
  } else {
    ESP_LOGE(TAG, "decode failed (frames=%d %dx%d)", frames, w, h);
  }

  wasm_runtime_destroy_exec_env(env);
  wasm_runtime_deinstantiate(inst);
  wasm_runtime_unload(module);
  heap_caps_free(wasm_buf);
}

static void *wamr_thread(void *arg) {
  (void) arg;
  run_wamr();
  return nullptr;
}

void GifWamr::setup() {
  pthread_attr_t attr;
  pthread_attr_init(&attr);
  pthread_attr_setstacksize(&attr, PTHREAD_STACK);
  pthread_t tid;
  if (pthread_create(&tid, &attr, wamr_thread, nullptr) == 0) {
    pthread_join(tid, nullptr);
  } else {
    ESP_LOGE(TAG, "pthread_create failed — cannot run WAMR");
  }
  pthread_attr_destroy(&attr);
}

void GifWamr::dump_config() { ESP_LOGCONFIG(TAG, "gif-wamr: WASM GIF decoder via WAMR (classic interp)"); }

}  // namespace gif_wamr
}  // namespace esphome
