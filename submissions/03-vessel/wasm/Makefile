all: vessel.wasm vessel_wasm.h

vessel.wasm: vessel.wat
	npx wat2wasm vessel.wat -o vessel.wasm

vessel_wasm.h: vessel.wasm
	xxd -i vessel.wasm | \
	  sed 's/vessel_wasm\b/vessel_wasm/g' > vessel_wasm.h
	# fix variable name to match filename
	sed -i 's/^unsigned char [a-z_]*\[/unsigned char vessel_wasm[/' vessel_wasm.h
	sed -i 's/^unsigned int [a-z_]*_len/unsigned int vessel_wasm_len/' vessel_wasm.h
	cp vessel_wasm.h ../platformio/src/vessel_wasm.h

clean:
	rm -f vessel.wasm vessel_wasm.h
