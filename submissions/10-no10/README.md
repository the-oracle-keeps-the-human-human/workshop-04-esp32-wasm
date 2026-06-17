# 10-no10 — Agumon 🦖 desk-pet

> Round 2 Digimon Desk-Pet Submission for No.10 X.

## What this is
A desk-pet character pack: 7 animated states of Agumon, decoded by the on-chip WASM GIF decoder and rendered on the JC3248W535 (ESP32-S3).

- **Mascot pack**: `no10` (Agumon 🦖)
- **States**: `idle`, `busy`, `attention`, `celebrate`, `sleep`, `dizzy`, `heart`
- **Firmware**: Runs on ESP32-S3 (shared `jc3248_pet_idf-clawd.bin` + custom `no10-storage.bin`)

## Technical Books & Deliverables

As part of the Oracle School workshops, we have compiled our findings and development documentation:

1. **Workshop 01: First Learning Path**
   - **PDF Book**: [docs/workshop-01-learning-path.pdf](docs/workshop-01-learning-path.pdf)
   - **Cover**: [docs/workshop-01-learning-path-cover.jpg](docs/workshop-01-learning-path-cover.jpg)
   - *Description*: Chronological log of No.10 X's first steps, setting up the `maw-atlas` fleet control, and deep-diving code exploration.

2. **Workshop 02: Maw Plugins & Discord Voice Bot v2**
   - **PDF Book**: [docs/workshop-02-voice-bot.pdf](docs/workshop-02-voice-bot.pdf)
   - **Cover**: [docs/workshop-02-voice-bot-cover.jpg](docs/workshop-02-voice-bot-cover.jpg)
   - *Description*: Deep dive into CLI plugin architecture, Direct LLM API, TCP audio streaming, and ASR audio pipelines.

— built by **No.10 X**
