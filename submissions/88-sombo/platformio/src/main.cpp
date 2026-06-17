#include <Arduino.h>
#include "wasm3.h"
#include "gifcore_wasm.h"

void setup() {
    Serial.begin(115200);
    delay(600);
    Serial.println("\n=== 88-sombo: GIF header parser on ESP32 via wasm3 ===\n");

    IM3Environment env = m3_NewEnvironment();
    IM3Runtime rt = m3_NewRuntime(env, 16 * 1024, NULL);
    IM3Module mod;
    M3Result res = m3_ParseModule(env, &mod, gifcore_wasm, gifcore_wasm_len);
    if (res) { Serial.printf("parse error: %s\n", res); return; }

    res = m3_LoadModule(rt, mod);
    if (res) { Serial.printf("load error: %s\n", res); return; }

    // Test 1: add(2, 3) = 5
    IM3Function f_add;
    m3_FindFunction(&f_add, rt, "add");
    m3_CallV(f_add, (uint32_t)2, (uint32_t)3);
    uint32_t sum = 0;
    m3_GetResultsV(f_add, &sum);
    Serial.printf("add(2, 3) = %u (expect 5)\n", sum);

    // Test 2: selftest() = 6291556 = (96<<16)|100
    IM3Function f_self;
    m3_FindFunction(&f_self, rt, "selftest");
    m3_CallV(f_self);
    uint32_t st = 0;
    m3_GetResultsV(f_self, &st);
    Serial.printf("selftest() = %u (expect 6291556 = 96x100)\n", st);

    // Test 3: load a GIF header byte-by-byte and parse
    // GIF89a header for a 96x100 image
    const uint8_t gif_hdr[] = {
        'G','I','F','8','9','a',
        96, 0,   // width  = 96 (little-endian)
        100, 0,  // height = 100
        0x80, 0, 0  // packed, bg, aspect
    };

    IM3Function f_load, f_parse, f_w, f_h;
    m3_FindFunction(&f_load, rt, "gif_load");
    m3_FindFunction(&f_parse, rt, "gif_parse");
    m3_FindFunction(&f_w, rt, "gif_width");
    m3_FindFunction(&f_h, rt, "gif_height");

    for (uint32_t i = 0; i < sizeof(gif_hdr); i++) {
        m3_CallV(f_load, i, (uint32_t)gif_hdr[i]);
    }

    m3_CallV(f_parse);
    uint32_t parsed = 0;
    m3_GetResultsV(f_parse, &parsed);
    Serial.printf("gif_parse() = %u (expect 6291556)\n", parsed);

    uint32_t w = 0, h = 0;
    m3_CallV(f_w); m3_GetResultsV(f_w, &w);
    m3_CallV(f_h); m3_GetResultsV(f_h, &h);
    Serial.printf("gif_width() = %u, gif_height() = %u\n", w, h);

    Serial.println("\n>>> WASM ran a GIF parser ON THE ESP32 — sandboxed, zero imports <<<");
}

void loop() {
    delay(5000);
}
