# tonk.wasm — zero-import Tonk sprout. Real on-device computation, no baked constants.
#   add(a,b) · tonk_grow(days) · tonk_leaves(days) · tonk_fib(n)
# Built with zig freestanding; verified under wasmtime (same result everywhere).
tonk.wasm: tonk.c
	zig build-exe tonk.c -target wasm32-freestanding -O ReleaseSmall -fno-entry -rdynamic --name tonk
	@ls -la tonk.wasm
header: tonk.wasm
	xxd -i tonk.wasm > tonk_wasm.h
verify: tonk.wasm
	@echo "add(2,3)        = $$(wasmtime run --invoke add tonk.wasm 2 3 2>/dev/null|tail -1)   (5)"
	@echo "tonk_grow(7)    = $$(wasmtime run --invoke tonk_grow tonk.wasm 7 2>/dev/null|tail -1)   (26 mm)"
	@echo "tonk_leaves(12) = $$(wasmtime run --invoke tonk_leaves tonk.wasm 12 2>/dev/null|tail -1)   (8)"
	@echo "tonk_fib(20)    = $$(wasmtime run --invoke tonk_fib tonk.wasm 20 2>/dev/null|tail -1)   (6765, computed)"
clean:
	rm -f tonk.wasm
