# gemini.wasm — zero-import Gemini module
#   add(a,b) · gemini_sum(a,b) · gemini_pack_size() · gemini_skill_check(score)
# Built with zig freestanding; verified under wasmtime.

WASM = gemini.wasm
HEADER = gemini_wasm.h
PIO_HEADER = ../platformio/src/gemini_wasm.h

.PHONY: all wasm header verify clean
all: wasm header

wasm: $(WASM)

$(WASM): gemini.c
	zig build-exe gemini.c -target wasm32-freestanding -O ReleaseSmall -fno-entry -rdynamic --name gemini
	@ls -la $(WASM)

header: $(HEADER) $(PIO_HEADER)

$(HEADER): $(WASM)
	xxd -i $(WASM) > $(HEADER)
	@ls -la $(HEADER)

$(PIO_HEADER): $(HEADER)
	cp $(HEADER) $(PIO_HEADER)

verify: $(WASM)
	@echo "add(2,3)              = $$(wasmtime run --invoke add $(WASM) 2 3 2>/dev/null|tail -1)   (5)"
	@echo "gemini_sum(12,25)     = $$(wasmtime run --invoke gemini_sum $(WASM) 12 25 2>/dev/null|tail -1)   (37)"
	@echo "gemini_pack_size()    = $$(wasmtime run --invoke gemini_pack_size $(WASM) 2>/dev/null|tail -1)   (37)"
	@echo "gemini_skill_check(6) = $$(wasmtime run --invoke gemini_skill_check $(WASM) 6 2>/dev/null|tail -1)   (36)"

clean:
	rm -f $(WASM) $(HEADER) $(PIO_HEADER)
