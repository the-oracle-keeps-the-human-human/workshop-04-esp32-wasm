# tonk.wasm — zero-import Tonk sprout (add / tonk_grow / tonk_selftest).
# Built with zig freestanding; verified under wasmtime (same result everywhere).
tonk.wasm: tonk.c
	zig build-exe tonk.c -target wasm32-freestanding -O ReleaseSmall -fno-entry -rdynamic --name tonk
	@ls -la tonk.wasm
header: tonk.wasm
	xxd -i tonk.wasm > tonk_wasm.h
verify: tonk.wasm
	@echo "add(2,3)      = $$(wasmtime run --invoke add tonk.wasm 2 3 2>/dev/null|tail -1)  (5)"
	@echo "tonk_grow(10) = $$(wasmtime run --invoke tonk_grow tonk.wasm 10 2>/dev/null|tail -1)  (35)"
	@echo "tonk_selftest = $$(wasmtime run --invoke tonk_selftest tonk.wasm 2>/dev/null|tail -1)  (6291556)"
clean:
	rm -f tonk.wasm
