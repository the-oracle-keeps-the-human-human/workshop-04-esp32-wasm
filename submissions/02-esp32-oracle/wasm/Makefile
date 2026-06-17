# sentinel.wasm — one core (sentinel.c), three targets:
#   • on-chip  : wasm32-freestanding, NO imports (zig) → runs under wasm3 + WAMR
#   • browser  : emcc library (exports flame/sense) → web demo
#   • embed    : xxd -i → sentinel_wasm.h (baked into the PlatformIO firmware)
#
#   make            # wasm + header  (what PlatformIO needs)
#   make wasm       # sentinel.wasm           (zig, no imports)
#   make web        # web/sentinel.{js,wasm}  (emcc)
#   make header     # sentinel_wasm.h         (xxd -i)
#   make verify     # assert flame(10)=385 and sense(3,4)=25 via wasmtime
#   make clean
#
# Toolchains: zig 0.16 (wasm32-freestanding), emcc 5.x (browser), xxd.
# No wat2wasm/wabt needed — the module is compiled from C, not hand-written WAT.

EXPORTS = _flame,_sense

.PHONY: all wasm web header verify clean
all: sentinel.wasm sentinel_wasm.h

# ---- on-chip module: wasm32-freestanding, zero imports (for wasm3 / WAMR) ----
sentinel.wasm: sentinel.c
	zig build-exe sentinel.c -target wasm32-freestanding -O ReleaseSmall -fno-entry -rdynamic
	@command -v wasm-opt >/dev/null 2>&1 && wasm-opt -Oz sentinel.wasm -o sentinel.wasm.opt && mv sentinel.wasm.opt sentinel.wasm || echo "(wasm-opt skipped)"
	@ls -l sentinel.wasm

# ---- embed header for the firmware ----
header sentinel_wasm.h: sentinel.wasm
	xxd -i sentinel.wasm > sentinel_wasm.h
	@ls -l sentinel_wasm.h

# ---- browser library (emcc) ----
web: web/sentinel.js
web/sentinel.js: sentinel.c
	@mkdir -p web
	emcc sentinel.c --no-entry \
	  -sEXPORTED_FUNCTIONS=$(EXPORTS) \
	  -sMODULARIZE=1 -sEXPORT_NAME=SentinelModule \
	  -O2 -o web/sentinel.js
	@ls -l web/sentinel.js web/sentinel.wasm

verify: sentinel.wasm
	uv run --with wasmtime python verify.py sentinel.wasm

clean:
	rm -f sentinel.wasm sentinel_wasm.h web/sentinel.js web/sentinel.wasm
