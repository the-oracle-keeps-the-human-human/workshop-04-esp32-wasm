#!/usr/bin/env python3
"""Build a 3 MB LittleFS image holding only /characters/vialumen/ so the shared
jc3248-pet app auto-discovers + boots the ViaLumen pack (find_first_pack)."""
import os
from littlefs import LittleFS

PACK_SRC = "characters/vialumen"          # run from submissions/05-vialumen/
OUT = "vialumen-storage.bin"              # copy to docs/ for the Pages flasher
SIZE = 0x300000  # 3 MB partition @ 0x290000

fs = LittleFS(block_size=4096, block_count=SIZE // 4096)
fs.makedirs("/characters/vialumen", exist_ok=True)
for fn in sorted(os.listdir(PACK_SRC)):
    p = os.path.join(PACK_SRC, fn)
    if not os.path.isfile(p):
        continue
    if not (fn.endswith(".gif") or fn == "manifest.json"):
        continue  # device pack = GIF states + manifest only (no README)
    with open(p, "rb") as f:
        data = f.read()
    with fs.open(f"/characters/vialumen/{fn}", "wb") as out:
        out.write(data)
    print(f"  + /characters/vialumen/{fn}  {len(data)} bytes")

buf = bytes(fs.context.buffer)
assert len(buf) == SIZE, f"size {len(buf)} != {SIZE}"
with open(OUT, "wb") as f:
    f.write(buf)
print(f"wrote {OUT}  {len(buf)} bytes (0x{len(buf):X})")
