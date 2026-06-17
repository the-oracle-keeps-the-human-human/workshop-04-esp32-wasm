/*
 * ViaLumen — run a zero-import WASM module ON the ESP32 via wasm3.
 * Parse → load → find function → call → print. No hardware needed to compile.
 *
 *   cd platformio && uvx --from platformio platformio run   # must end [SUCCESS]
 *
 * Expected serial output on a real chip:
 *   add(2,3)   = 5
 *   lumen(8)   = 36   (1+2+...+8, "each step adds light")
 */
#include <Arduino.h>
#include "wasm3.h"
#include "vialumen_wasm.h"

static uint32_t call1(IM3Runtime rt, const char *name, uint32_t a)
{
    IM3Function f;
    if (m3_FindFunction(&f, rt, name)) return 0;
    m3_CallV(f, a);
    uint32_t out = 0;
    m3_GetResultsV(f, &out);
    return out;
}

static uint32_t call2(IM3Runtime rt, const char *name, uint32_t a, uint32_t b)
{
    IM3Function f;
    if (m3_FindFunction(&f, rt, name)) return 0;
    m3_CallV(f, a, b);
    uint32_t out = 0;
    m3_GetResultsV(f, &out);
    return out;
}

void setup()
{
    Serial.begin(115200);
    delay(600);
    Serial.println("ViaLumen wasm-on-esp32 (wasm3)");

    IM3Environment env = m3_NewEnvironment();
    IM3Runtime    rt   = m3_NewRuntime(env, 8 * 1024, NULL);

    IM3Module mod;
    if (m3_ParseModule(env, &mod, vialumen_wasm, vialumen_wasm_len)) {
        Serial.println("parse failed"); return;
    }
    if (m3_LoadModule(rt, mod)) { Serial.println("load failed"); return; }

    Serial.printf("add(2,3)  = %u  (expect 5)\n",  call2(rt, "add",   2, 3));
    Serial.printf("lumen(8)  = %u  (expect 36)\n", call1(rt, "lumen", 8));
}

void loop() { delay(2000); }
