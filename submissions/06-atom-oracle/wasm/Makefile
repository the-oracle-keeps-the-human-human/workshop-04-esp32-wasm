WASM = atom-orbit.wasm
WAT = atom-orbit.wat
HEADER = atom_orbit_wasm.h
PIO_HEADER = ../platformio/src/atom_orbit_wasm.h

.PHONY: all wasm header verify clean
all: wasm header

wasm: $(WASM)

$(WASM): $(WAT)
	wasm-tools parse $(WAT) -o $(WASM)
	wasm-tools validate $(WASM)
	@ls -l $(WASM)

header: $(HEADER) $(PIO_HEADER)

$(HEADER): $(WASM)
	xxd -i $(WASM) > $(HEADER)
	@ls -l $(HEADER)

$(PIO_HEADER): $(HEADER)
	cp $(HEADER) $(PIO_HEADER)

verify: $(WASM)
	node verify.mjs $(WASM)

clean:
	rm -f $(WASM) $(HEADER) $(PIO_HEADER)
