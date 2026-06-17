from littlefs import LittleFS
import os

# Set paths
base_dir = os.path.dirname(__file__)
PACK = os.path.join(base_dir, "characters", "no10")
out_bin = os.path.abspath(os.path.join(base_dir, "..", "..", "docs", "no10-storage.bin"))

# ESP-IDF littlefs geometry: block 4096, 3MB partition → 768 blocks
fs = LittleFS(block_size=4096, block_count=0x300000 // 4096)
fs.makedirs("/characters/no10", exist_ok=True)

# Add manifest.json and all state gifs
for fn in sorted(os.listdir(PACK)):
    with open(os.path.join(PACK, fn), "rb") as f:
        data = f.read()
    with fs.open(f"/characters/no10/{fn}", "wb") as w:
        w.write(data)
    print(f"  + characters/no10/{fn} ({len(data)}B)")

# Generate littlefs image
img = bytes(fs.context.buffer)
with open(out_bin, "wb") as w:
    w.write(img)
print("no10-storage.bin:", len(img), "bytes (3MB littlefs) saved to docs/no10-storage.bin")
