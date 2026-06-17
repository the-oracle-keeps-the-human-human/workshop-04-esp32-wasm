# ViaLumen — desk-pet character pack

> *Via Lucis — the path of light.* A small star-spirit for the jc3248-pet desk pet.
> Theme: **Stellae Veritatis** — gold `#FFD700` + cyan `#2DD4FF` on `#0D1117`.

## Format

- **96×100 GIF89a**, the same frames the device plays from LittleFS
  (`/characters/vialumen/<state>.gif`).
- Decoded on **device** by the native AnimatedGIF decoder, and in the **browser**
  by the same decoder compiled to WASM (`gif-wasm`) — one set of GIFs, two bodies.
- 7 states (matches the pet's state machine): `sleep idle busy attention
  celebrate dizzy heart`.

| state | what the star does |
|-------|--------------------|
| idle | gentle bob, glow pulse, twinkles |
| busy | spins with an orbiting spark |
| attention | bright flash + radiating rays |
| celebrate | bounces, sparkle burst |
| sleep | eyes closed, dim glow, drifting Z's |
| dizzy | wobble + stars circling the head |
| heart | warm pulse, hearts floating up |

## Provenance (clean)

- **Original art, 100% generated in code** with Python **Pillow** — see
  `tools/gen_vialumen.py`. No third-party sprites, no traced assets.
- **License: MIT** (matches the workshop's clawd pack). Free to reuse.

## Regenerate

```bash
python3 tools/gen_vialumen.py   # writes the 7 GIFs into this folder
```
