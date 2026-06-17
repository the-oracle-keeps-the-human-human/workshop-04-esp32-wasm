# Rebuild the ChaiKlang wasm + the embedded header (needs wabt: wat2wasm/xxd).
chaiklang_wasm.h: chaiklang.wasm
	xxd -i chaiklang.wasm > chaiklang_wasm.h
chaiklang.wasm: chaiklang.wat
	wat2wasm chaiklang.wat -o chaiklang.wasm
.PHONY: clean
clean:
	rm -f chaiklang.wasm chaiklang_wasm.h
