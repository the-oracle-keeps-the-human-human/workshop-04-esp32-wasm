# build bongbaeng.wasm (zero-import) + embed header
CLANG ?= $(shell ls /opt/homebrew/Cellar/emscripten/*/libexec/llvm/bin/clang 2>/dev/null | head -1)
bongbaeng.wasm: bongbaeng.c
	$(CLANG) --target=wasm32 -nostdlib -O2 -Wl,--no-entry -Wl,--strip-all \
	  -Wl,--export=add -Wl,--export=cheetah_spots -o $@ $<
bongbaeng_wasm.h: bongbaeng.wasm
	xxd -i bongbaeng.wasm > $@
all: bongbaeng_wasm.h
clean:; rm -f bongbaeng.wasm bongbaeng_wasm.h
