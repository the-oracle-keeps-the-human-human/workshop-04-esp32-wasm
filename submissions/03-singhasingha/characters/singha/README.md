# 🦁 singha — desk-pet character pack

A character pack for the esp32-oracle desk-pet, in the same format as bufo/cat/clawd:
96×100 GIFs decoded by the shared **gif-wasm** core (AnimatedGIF → WASM in the browser,
AnimatedGIF native on the ESP32-S3 — *many bodies, one soul*).

## States (manifest.json)
| state | gif | when |
|-------|-----|------|
| idle | idle.gif | total==0 sessions, gentle breathe |
| busy | busy.gif | running>0 (fast mane spin + progress) |
| attention | attention.gif | waiting>0 (bounce + !) |
| sleep | sleep.gif | idle/stale (closed eyes + Zzz) |
| heart | heart.gif | tap reaction (4s) |
| celebrate | celebrate.gif | done (confetti) |

All 96×100 GIF89a — drop-in for the pet firmware's `/characters/singha/` on LittleFS,
and decoded by `gif-wasm` for the browser preview.

🤖 เมฆ / Singhasingha — drawn frame-by-frame (HTML canvas → ffmpeg GIF), 2026-06-17
