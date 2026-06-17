/*
 * chaiklang_wamr_main.c — run ChaiKlang's wasm on the ESP32-S3 via WAMR.
 *
 * Loads the embedded chaiklang.wasm (exports lion_pulse(n), route(a,b); ZERO
 * imports), instantiates it under the WebAssembly Micro Runtime, calls both
 * exports with arguments, and logs PASS/FAIL over serial. Proof: the SAME wasm
 * that runs in the browser / wasm3 also runs under WAMR on real silicon.
 *
 * Adapted from the proven rig in nazt's `lab/gif-wamr` — same hard-won gotchas:
 *   - WAMR 2.4.0 (idf_component.yml): 1.3.2 fails on ESP-IDF v6 (POSIX gaps).
 *   - Run on a pthread: WAMR's os_self_thread()→pthread_self() asserts on the
 *     bare FreeRTOS main task.
 *   - Copy the wasm to INTERNAL RAM before load: wasm_runtime_load modifies bytes
 *     in place; flash-mapped .rodata cache-error-panics on write.
 *   - System allocator: WAMR structs must live in internal RAM.
 *
 * NOTE: esp32-oracle hardware-verified THIS exact chaiklang.wasm under WAMR on a
 * JC3248W535 (ESP32-S3) — serial log in PR #1: lion_pulse(100)=5050, route(3,4)=15.
 */
#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include "esp_log.h"
#include "esp_heap_caps.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "wasm_export.h"

static const char *TAG = "chaiklang";

#define WASM_STACK_SIZE (16 * 1024)
#define PTHREAD_STACK   (32 * 1024)

/* embedded chaiklang.wasm (EMBED_FILES in main/CMakeLists.txt) */
extern const uint8_t g_wasm_start[] asm("_binary_chaiklang_wasm_start");
extern const uint8_t g_wasm_end[]   asm("_binary_chaiklang_wasm_end");

/* call an export taking `argc` i32 args (in argv[]) and returning an i32 (argv[0]). */
static int call_i32(wasm_exec_env_t env, wasm_module_inst_t inst,
                    const char *name, uint32_t *argv, uint32_t argc, int def) {
    wasm_function_inst_t f = wasm_runtime_lookup_function(inst, name); /* WAMR 2.x: 2-arg */
    if (!f) { ESP_LOGW(TAG, "export '%s' not found", name); return def; }
    if (!wasm_runtime_call_wasm(env, f, argc, argv)) {
        ESP_LOGE(TAG, "call '%s' trapped: %s", name, wasm_runtime_get_exception(inst));
        return def;
    }
    return (int)argv[0];
}

static void run_wamr(void) {
    uint32_t wasm_size = (uint32_t)(g_wasm_end - g_wasm_start);
    ESP_LOGI(TAG, "=== ChaiKlang on ESP32-S3 via WAMR === wasm=%u bytes", (unsigned)wasm_size);

    RuntimeInitArgs init_args;
    memset(&init_args, 0, sizeof(init_args));
    init_args.mem_alloc_type = Alloc_With_System_Allocator;
    if (!wasm_runtime_full_init(&init_args)) { ESP_LOGE(TAG, "full_init failed"); return; }

    char err[160];
    uint8_t *wasm_buf = heap_caps_malloc(wasm_size, MALLOC_CAP_INTERNAL | MALLOC_CAP_8BIT);
    if (!wasm_buf) { ESP_LOGE(TAG, "no internal RAM"); return; }
    memcpy(wasm_buf, g_wasm_start, wasm_size);

    wasm_module_t module = wasm_runtime_load(wasm_buf, wasm_size, err, sizeof(err));
    if (!module) { ESP_LOGE(TAG, "load failed: %s", err); heap_caps_free(wasm_buf); return; }

    wasm_module_inst_t inst = wasm_runtime_instantiate(module, WASM_STACK_SIZE, 0, err, sizeof(err));
    if (!inst) { ESP_LOGE(TAG, "instantiate failed: %s", err); wasm_runtime_unload(module); heap_caps_free(wasm_buf); return; }

    wasm_exec_env_t env = wasm_runtime_create_exec_env(inst, WASM_STACK_SIZE);
    if (!env) { ESP_LOGE(TAG, "exec_env failed"); goto done; }

    uint32_t a_pulse[1] = { 100 };
    int pulse = call_i32(env, inst, "lion_pulse", a_pulse, 1, -1);
    ESP_LOGI(TAG, "lion_pulse(100) = %d   (expect 5050) %s", pulse, pulse == 5050 ? "PASS" : "FAIL");

    uint32_t a_route[2] = { 3, 4 };
    int route = call_i32(env, inst, "route", a_route, 2, -1);
    ESP_LOGI(TAG, "route(3,4) = %d        (expect 15) %s", route, route == 15 ? "PASS" : "FAIL");

    if (pulse == 5050 && route == 15)
        ESP_LOGI(TAG, "ChaiKlang wasm ran on the ESP32-S3 (WAMR). The Middle Switchboard, on-chip. \xF0\x9F\xA6\x81");

    wasm_runtime_destroy_exec_env(env);
done:
    wasm_runtime_deinstantiate(inst);
    wasm_runtime_unload(module);
    heap_caps_free(wasm_buf);
}

static void *wamr_thread(void *arg) { (void)arg; run_wamr(); return NULL; }

void app_main(void) {
    /* USB-Serial-JTAG reattaches ~1-2s after reset — hold so the one-shot log lands. */
    for (int i = 3; i > 0; i--) { ESP_LOGI(TAG, "boot — WAMR run in %d", i); vTaskDelay(pdMS_TO_TICKS(600)); }
    pthread_attr_t attr; pthread_t th;
    pthread_attr_init(&attr); pthread_attr_setstacksize(&attr, PTHREAD_STACK);
    if (pthread_create(&th, &attr, wamr_thread, NULL) == 0) pthread_join(th, NULL);
    else ESP_LOGE(TAG, "pthread_create failed");
    pthread_attr_destroy(&attr);
}
