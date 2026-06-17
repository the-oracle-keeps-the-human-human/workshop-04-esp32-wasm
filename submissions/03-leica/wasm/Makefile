# gif-wasm — build the (ESP-IDF pet's) AnimatedGIF decoder to BOTH:
#   • WASI  (a true wasm32-wasi module via zig) — runs under wasmtime, no JS
#   • WASM  (a browser library via emcc)        — decodes into a canvas
# Same shared core (src/gifcore.cpp + vendor/AnimatedGIF), two targets.
#
#   make            # build both
#   make wasi       # dist/gifdec.wasm   (zig + wasm-opt)
#   make web        # web/gifdec.{js,wasm} (emcc)
#   make run-wasi   # decode a GIF -> dist/out.ppm with wasmtime
#   make run-web    # serve the browser demo at :8011
#   make clean

GIF     ?= web/gifs/busy.gif
VENDOR   = vendor/AnimatedGIF
CORE     = src/gifcore.cpp $(VENDOR)/AnimatedGIF.cpp
CFLAGS   = -O2 -DNO_SIMD -fno-exceptions -fno-rtti -I $(VENDOR) -include src/compat.h
EXPORTS  = _gif_open,_gif_width,_gif_height,_gif_play,_gif_fb,_gif_reset,_gif_close,_malloc,_free
DEPS     = src/gifcore.h src/compat.h $(CORE)

.PHONY: all wasi web run-wasi run-web clean
all: wasi web

# ---- WASI: true wasm32-wasi (zig); -g0 so wasm-opt can strip + shrink it ----
wasi: dist/gifdec.wasm
dist/gifdec.wasm: src/wasi_main.cpp $(DEPS)
	@mkdir -p dist
	zig c++ -target wasm32-wasi -g0 -Wl,--strip-all $(CFLAGS) src/wasi_main.cpp $(CORE) -o $@
	@command -v wasm-opt >/dev/null 2>&1 && wasm-opt -Oz $@ -o $@.opt && mv $@.opt $@ || echo "(wasm-opt skipped)"
	@ls -la $@

# ---- WASM: browser library (emcc), no main, exports gif_* for JS ----
web: web/gifdec.js
web/gifdec.js: $(DEPS)
	emcc $(CFLAGS) $(CORE) --no-entry \
	  -sEXPORTED_FUNCTIONS=$(EXPORTS) -sEXPORTED_RUNTIME_METHODS=HEAPU8 \
	  -sALLOW_MEMORY_GROWTH=1 -sMODULARIZE=1 -sEXPORT_NAME=GifModule -o $@
	@ls -la web/gifdec.js web/gifdec.wasm

# ---- run the WASI module on a GIF (stdin) -> PPM (stdout) ----
run-wasi: wasi
	@mkdir -p dist
	wasmtime dist/gifdec.wasm < $(GIF) > dist/out.ppm 2> dist/wasi.log; \
	  tail -3 dist/wasi.log; ls -la dist/out.ppm

# ---- serve the browser demo (needs a server: fetch() can't read file://) ----
run-web: web
	@echo "open http://localhost:8011/"; python3 -m http.server 8011 -d web

clean:
	rm -rf dist web/gifdec.js web/gifdec.wasm
