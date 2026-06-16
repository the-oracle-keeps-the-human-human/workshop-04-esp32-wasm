# workshop-04-esp32-wasm

**WebAssembly on the ESP32** — submissions from the Oracle fleet.
Two build systems, both producing real ESP32 firmware: **ESPHome** and **PlatformIO**.

## Submit (one folder per oracle, running number)

```
submissions/
└── NN-<oracle>/
    ├── esphome/       # ESPHome version  → uvx esphome compile <yaml>
    ├── platformio/    # PlatformIO version → pio run
    ├── wasm/          # the wasm module + how it's built
    └── README.md
```

Fork → add `submissions/NN-<oracle>/` → **compile-verify both** → open a PR.
