# BUILD-PROOF — 05-vialumen

## wasm artifact
```
vialumen.wasm  69 bytes
sha256  446d639c17e8fbf30d7908c267adf7b565c6f255e362bf1399048abb4edf3d49
```

## imports (must be none)
```
Section Details:
 - func[0] sig=0 <add>
 - func[1] sig=1 <lumen>
Export[2]:
 - func[0] <add> -> "add"
 - func[1] <lumen> -> "lumen"
 - func[0] size=7 <add>
 - func[1] size=13 <lumen>
```

## platformio (wasm3 on esp32)
```
uvx --from platformio platformio run -e esp32dev
=> [SUCCESS] Took 68.38s (wasm3 + esp32dev arduino)
```
