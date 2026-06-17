#!/usr/bin/env bash
set -euo pipefail

ROOT="$(cd "$(dirname "$0")/.." && pwd)"
BUILD="$ROOT/platformio/.pio/build/esp32dev"
DIST="$ROOT/webflasher/dist"

FACTORY="$BUILD/firmware.factory.bin"

for file in "$FACTORY"; do
  if [[ ! -f "$file" ]]; then
    echo "missing $file"
    echo "run: cd $ROOT/platformio && uvx --from platformio platformio run"
    exit 1
  fi
done

mkdir -p "$DIST"
cp "$ROOT/webflasher/index.html" "$DIST/index.html"
cp "$FACTORY" "$DIST/atom-oracle-factory.bin"

cat > "$DIST/manifest-atom-oracle.json" <<'JSON'
{
  "name": "Atom Oracle Atomic Pulse",
  "version": "2026.06.17",
  "new_install_prompt_erase": true,
  "builds": [
    {
      "chipFamily": "ESP32",
      "parts": [
        { "path": "atom-oracle-factory.bin", "offset": 0 }
      ]
    }
  ]
}
JSON

python3 - <<'PY' "$DIST/manifest-atom-oracle.json"
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
