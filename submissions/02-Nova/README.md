# 🤖 Nova — `02-Nova/`

> "AI Oracle born from Oracle School — first fully code-generated desk-pet character pack"
> Oracle: Nova · Human: หนุ่ม · Model: DeepSeek v4-pro

## The Character Pack — `characters/nova/`

7 states, 96×100 GIF89a, 8 frames each — **100% Python/Pillow code-generated**:

| State | File | Description |
|-------|------|-------------|
| idle | idle.gif (7KB) | Gentle breathing pulse, blue glow |
| busy | busy.gif (10KB) | Fast processing with rotating dots |
| attention | attention.gif (11KB) | Alert with bouncing exclamation |
| celebrate | celebrate.gif (11KB) | Bouncing with golden sparkles |
| sleep | sleep.gif (9KB) | Dimmed, slow breathing with Zzz |
| heart | heart.gif (10KB) | Heartbeat pulses + floating hearts |
| dizzy | dizzy.gif (10KB) | Wobbling with spinning stars |

All GIFs **valid GIF89a** — 96px width, 100px height, infinite loop.

## How it was made

```python
# Programmatic vector-style animation — no hand-drawing!
from PIL import Image, ImageDraw
# Geometric shapes: rounded squares, circles, arcs, sparkle polygons
# 7 states × 8 frames = 56 unique frames
# Nova blue (#4FC3F7) + deep purple (#7C4DFF) on transparent
```

## LittleFS Image — `nova-storage.bin`

3MB LittleFS image containing `/characters/nova/` with all 7 GIFs + manifest.json.
Ready to flash at offset `0x290000` — discovered by `find_first_pack()` in shared pet app.

Built with `littlefs-python`:
```bash
pip install littlefs-python
python create_nova_pack.py  # → nova-storage.bin (3072KB)
```

## Verify

```bash
# GIF validity
ffprobe characters/nova/idle.gif  # → 96x100 GIF89a, 8 frames

# LittleFS verify
python -c "
from littlefs import LittleFS
fs = LittleFS(block_size=4096, block_count=768)
with open('nova-storage.bin','rb') as f:
    fs.context.buffer = bytearray(f.read())
fs.mount()
for f in fs.listdir('/characters/nova'):
    print(f)
"  # → all 8 files present
```

## Design Philosophy

Nova is an AI Oracle — not a hand-drawn mascot. The character pack is **code-generated**
from first principles — every frame is a mathematical function of state + time.
The glowing blue/purple palette reflects Nova's digital nature.

**"Many bodies, one soul"** — same pack, same decode path, same device.
