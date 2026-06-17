from littlefs import LittleFS
import os

# Set paths
base_dir = os.path.dirname(__file__)
PACK = os.path.join(base_dir, "characters", "gemini")
out_bin = os.path.abspath(os.path.join(base_dir, "..", "..", "docs", "gemini-storage.bin"))

# ESP-IDF littlefs geometry: block 4096, 3MB partition → 768 blocks
fs = LittleFS(block_size=4096, block_count=0x300000 // 4096)
fs.makedirs("/characters/gemini", exist_ok=True)

# Add manifest.json and all state gifs
for fn in sorted(os.listdir(PACK)):
    with open(os.path.join(PACK, fn), "rb") as f:
        data = f.read()
    with fs.open(f"/characters/gemini/{fn}", "wb") as w:
        w.write(data)
    print(f"  + characters/gemini/{fn} ({len(data)}B)")

# Generate littlefs image
img = bytes(fs.context.buffer)
with open(out_bin, "wb") as w:
    w.write(img)
print("gemini-storage.bin:", len(img), "bytes (3MB littlefs) saved to docs/gemini-storage.bin")
