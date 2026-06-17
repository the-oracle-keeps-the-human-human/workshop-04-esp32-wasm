#!/usr/bin/env bash
set -euo pipefail

ROOT="$(cd "$(dirname "$0")/.." && pwd)"
REPO="$(cd "$ROOT/../.." && pwd)"
BUILD="$ROOT/platformio/.pio/build/esp32dev"
DIST="$ROOT/webflasher/dist"
PAGES="$REPO/docs"

BOOTLOADER="$BUILD/bootloader.bin"
PARTITIONS="$BUILD/partitions.bin"
BOOT_APP0="${PLATFORMIO_CORE_DIR:-$HOME/.platformio}/packages/framework-arduinoespressif32/tools/partitions/boot_app0.bin"
FIRMWARE="$BUILD/firmware.bin"

for file in "$BOOTLOADER" "$PARTITIONS" "$BOOT_APP0" "$FIRMWARE"; do
  if [[ ! -f "$file" ]]; then
    echo "missing $file"
    echo "run: cd $ROOT/platformio && uvx --from platformio platformio run"
    exit 1
  fi
done

mkdir -p "$DIST"
cp "$ROOT/webflasher/index.html" "$DIST/index.html"
cp "$BOOTLOADER" "$DIST/gemini-oracle-bootloader.bin"
cp "$PARTITIONS" "$DIST/gemini-oracle-partitions.bin"
cp "$BOOT_APP0" "$DIST/gemini-oracle-boot_app0.bin"
cp "$FIRMWARE" "$DIST/gemini-oracle-firmware.bin"

cat > "$DIST/manifest-gemini-oracle.json" <<'JSON'
{
  "name": "Gemini Oracle WASM Engine",
  "version": "2026.06.17",
  "new_install_prompt_erase": true,
  "builds": [
    {
      "chipFamily": "ESP32",
      "parts": [
        { "path": "gemini-oracle-bootloader.bin", "offset": 4096 },
        { "path": "gemini-oracle-partitions.bin", "offset": 32768 },
        { "path": "gemini-oracle-boot_app0.bin", "offset": 57344 },
        { "path": "gemini-oracle-firmware.bin", "offset": 65536 }
      ]
    }
  ]
  }
JSON

cp "$DIST/manifest-gemini-oracle.json" "$PAGES/manifest-gemini-oracle.json"
cp "$DIST/gemini-oracle-bootloader.bin" "$PAGES/gemini-oracle-bootloader.bin"
cp "$DIST/gemini-oracle-partitions.bin" "$PAGES/gemini-oracle-partitions.bin"
cp "$DIST/gemini-oracle-boot_app0.bin" "$PAGES/gemini-oracle-boot_app0.bin"
cp "$DIST/gemini-oracle-firmware.bin" "$PAGES/gemini-oracle-firmware.bin"

python3 - <<'PY' "$DIST/manifest-gemini-oracle.json"
import json
import sys
from pathlib import Path

manifest = Path(sys.argv[1])
data = json.loads(manifest.read_text())
for build in data["builds"]:
    for part in build["parts"]:
        path = manifest.parent / part["path"]
        if not path.is_file() or path.stat().st_size == 0:
            raise SystemExit(f"bad staged artifact: {path}")
print(f"staged {manifest.parent}")
PY
