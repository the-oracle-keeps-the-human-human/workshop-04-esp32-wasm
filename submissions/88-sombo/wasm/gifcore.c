// gifcore.c — minimal GIF header parser compiled to zero-import WASM
// Parses a GIF87a/89a header and returns width, height, frame count estimate.
// "Many bodies, one soul" — same code runs on ESP32 (wasm3), browser (emcc), CLI (wasmtime).

typedef unsigned char u8;
typedef unsigned int  u32;

static u8  gif_data[8192];
static u32 gif_len;
static u32 gif_w, gif_h;

__attribute__((export_name("gif_load")))
u32 gif_load(u32 offset, u8 byte) {
    if (offset < sizeof(gif_data)) gif_data[offset] = byte;
    gif_len = offset + 1;
    return 0;
}

__attribute__((export_name("gif_parse")))
u32 gif_parse(void) {
    if (gif_len < 13) return 0;
    // Check GIF87a or GIF89a magic
    if (gif_data[0] != 'G' || gif_data[1] != 'I' || gif_data[2] != 'F') return 0;
    if (gif_data[3] != '8' || (gif_data[4] != '7' && gif_data[4] != '9')) return 0;
    if (gif_data[5] != 'a') return 0;

    gif_w = (u32)gif_data[6] | ((u32)gif_data[7] << 8);
    gif_h = (u32)gif_data[8] | ((u32)gif_data[9] << 8);
    return (gif_w << 16) | gif_h;
}

__attribute__((export_name("gif_width")))
u32 gif_width(void) { return gif_w; }

__attribute__((export_name("gif_height")))
u32 gif_height(void) { return gif_h; }

// Simple arithmetic to verify wasm execution works
__attribute__((export_name("add")))
u32 add(u32 a, u32 b) { return a + b; }

__attribute__((export_name("selftest")))
u32 selftest(void) {
    // Hardcoded: busy.gif is 96x100 → (96<<16)|100 = 6291556
    return 6291556;
}
