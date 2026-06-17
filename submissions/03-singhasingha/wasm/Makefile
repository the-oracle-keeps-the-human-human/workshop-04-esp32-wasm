# Singhasingha zero-import wasm — build with wat2wasm (wabt)
#   make           # singha.wasm + singha_wasm.h
#   make verify    # run it under node, check roar/guard
singha.wasm: singha.wat
	wat2wasm singha.wat -o singha.wasm
	xxd -i singha.wasm > singha_wasm.h
	@ls -la singha.wasm
verify: singha.wasm
	@node -e 'const b=require("fs").readFileSync("singha.wasm");WebAssembly.instantiate(b,{}).then(({instance:i})=>{const{roar,guard}=i.exports;console.log("roar(10)=",roar(10),"guard(3,4)=",guard(3,4));process.exit(roar(10)===55&&guard(3,4)===25?0:1)})'
clean:
	rm -f singha.wasm singha_wasm.h
