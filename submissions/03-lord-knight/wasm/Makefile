# gifapp.wasm — the on-device WASM reactor (GIF decoder + embedded GIF), built
# with zig. Import-free, small growable memory. Self-contained: the shared
# decoder core is vendored under ./core (no external paths).
#
#   make          # gifapp.wasm  (needs zig 0.14.x)
#   make verify   # run it under wasmtime: selftest -> 6291556 (96x100), run -> 2
#   make header   # regenerate gifapp_wasm.h that both firmwares embed
#   make clean

CORE    = gifapp.cpp core/gifcore.cpp core/AnimatedGIF/AnimatedGIF.cpp
CFLAGS  = -O2 -g0 -DNO_SIMD -fno-exceptions -fno-rtti -fno-jump-tables \
          -I . -I core -I core/AnimatedGIF -include core/compat.h
# zig/LLVM br_table in dead code trips WAMR's validator -> -fno-jump-tables.
EXPORTS = -Wl,--export=gifapp_run -Wl,--export=gifapp_width -Wl,--export=gifapp_height \
          -Wl,--export=gifapp_fb -Wl,--export=gifapp_selftest
# 128KB shadow stack (zig defaults to 16MB!); grow 512KB->2MB (first malloc grows).
MEM     = -Wl,-z,stack-size=131072 -Wl,--initial-memory=524288 -Wl,--max-memory=2097152

.PHONY: all verify header clean
all: gifapp.wasm

gifapp.wasm: gifapp.cpp gif_data.h core/gifcore.cpp core/AnimatedGIF/AnimatedGIF.cpp
	zig c++ -target wasm32-wasi -mexec-model=reactor -Wl,--strip-all $(MEM) $(EXPORTS) $(CFLAGS) $(CORE) -o $@
	@ls -la $@

verify: gifapp.wasm
	@echo "selftest (want 6291556 = 96x100): $$(wasmtime run --invoke gifapp_selftest gifapp.wasm 2>/dev/null | tail -1)"
	@echo "gifapp_run frames (want 2):        $$(wasmtime run --invoke gifapp_run gifapp.wasm 2>/dev/null | tail -1)"

# regenerate the C-array header that BOTH builds embed (platformio/src + esphome/components)
header: gifapp.wasm
	@echo "// auto-generated from gifapp.wasm (xxd -i). const -> flash .rodata." > gifapp_wasm.h
	@xxd -i -n gifapp_wasm gifapp.wasm | sed 's/^unsigned char/const unsigned char/; s/^unsigned int/const unsigned int/' >> gifapp_wasm.h
	@echo "wrote gifapp_wasm.h"

clean:
	rm -f gifapp.wasm gifapp_wasm.h
