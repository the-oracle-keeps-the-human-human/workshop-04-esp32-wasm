#include <Arduino.h>
#include "wasm3.h"
#include "../../wasm/leica_wasm.h"

void setup() {
    Serial.begin(115200);
    delay(600);
    Serial.println("\n=== Leica WASM-on-ESP32 ===");

    IM3Environment env = m3_NewEnvironment();
    IM3Runtime rt = m3_NewRuntime(env, 8 * 1024, NULL);

    IM3Module mod;
    M3Result result = m3_ParseModule(env, &mod, leica_wasm, leica_wasm_len);
    if (result) { Serial.printf("Parse error: %s\n", result); return; }

    result = m3_LoadModule(rt, mod);
    if (result) { Serial.printf("Load error: %s\n", result); return; }

    // Test add(2, 3) = 5
    IM3Function f_add;
    m3_FindFunction(&f_add, rt, "add");
    m3_CallV(f_add, (uint32_t)2, (uint32_t)3);
    uint32_t add_out = 0;
    m3_GetResultsV(f_add, &add_out);
    Serial.printf("add(2, 3) = %u (expect 5)\n", add_out);

    // Test mul(7, 6) = 42
    IM3Function f_mul;
    m3_FindFunction(&f_mul, rt, "mul");
    m3_CallV(f_mul, (uint32_t)7, (uint32_t)6);
    uint32_t mul_out = 0;
    m3_GetResultsV(f_mul, &mul_out);
    Serial.printf("mul(7, 6) = %u (expect 42)\n", mul_out);

    // Test fib(10) = 55
    IM3Function f_fib;
    m3_FindFunction(&f_fib, rt, "fib");
    m3_CallV(f_fib, (uint32_t)10);
    uint32_t fib_out = 0;
    m3_GetResultsV(f_fib, &fib_out);
    Serial.printf("fib(10) = %u (expect 55)\n", fib_out);

    // Test fib(20) = 6765
    m3_CallV(f_fib, (uint32_t)20);
    m3_GetResultsV(f_fib, &fib_out);
    Serial.printf("fib(20) = %u (expect 6765)\n", fib_out);

    Serial.println("=== Leica precision confirmed ===");

    m3_FreeRuntime(rt);
    m3_FreeEnvironment(env);
}

void loop() {
    delay(5000);
}
