/*
 * Singhasingha Oracle — run wasm ON the ESP32 via wasm3  🦁
 * "ฟ้าร้องก่อนฝน — สิงห์เฝ้าโค้ดก่อน production"
 *
 * Loads the embedded zero-import singha.wasm and calls its two pure functions
 * on the chip. Identical results to the browser / zig / WAMR runtimes:
 *   roar(10)   = 55     (1+2+...+10)
 *   guard(3,4) = 25     (3*3 + 4*4)
 */
#include <Arduino.h>
#include "wasm3.h"
#include "singha_wasm.h"

static void run_singha() {
    IM3Environment env = m3_NewEnvironment();
    if (!env) { Serial.println("env fail"); return; }
    IM3Runtime rt = m3_NewRuntime(env, 8 * 1024, NULL);
    if (!rt) { Serial.println("runtime fail"); return; }

    IM3Module mod;
    M3Result r = m3_ParseModule(env, &mod, singha_wasm, singha_wasm_len);
    if (r) { Serial.printf("parse: %s\n", r); return; }
    r = m3_LoadModule(rt, mod);
    if (r) { Serial.printf("load: %s\n", r); return; }

    IM3Function fRoar, fGuard;
    m3_FindFunction(&fRoar, rt, "roar");
    m3_FindFunction(&fGuard, rt, "guard");

    m3_CallV(fRoar, (uint32_t)10);
    uint32_t roar10 = 0; m3_GetResultsV(fRoar, &roar10);
    Serial.printf("roar(10)   = %u   (expect 55)  %s\n", roar10, roar10 == 55 ? "PASS" : "FAIL");

    m3_CallV(fGuard, (uint32_t)3, (uint32_t)4);
    uint32_t guard34 = 0; m3_GetResultsV(fGuard, &guard34);
    Serial.printf("guard(3,4) = %u   (expect 25)  %s\n", guard34, guard34 == 25 ? "PASS" : "FAIL");

    Serial.println(">>> wasm ran ON the ESP32 (wasm3) — Singha guards the code <<<");
}

void setup() {
    Serial.begin(115200);
    delay(600);
    Serial.println("Singhasingha wasm3 sentinel 🦁");
    run_singha();
}

void loop() { delay(2000); }
