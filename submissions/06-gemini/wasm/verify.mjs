import { readFile } from "node:fs/promises";

const wasmPath = process.argv[2] ?? "gemini.wasm";
const bytes = await readFile(wasmPath);
const { instance } = await WebAssembly.instantiate(bytes, {});

const checks = [
  ["add(2,3)", instance.exports.add(2, 3), 5],
  ["gemini_sum(12,25)", instance.exports.gemini_sum(12, 25), 37],
  ["gemini_pack_size()", instance.exports.gemini_pack_size(), 37],
  ["gemini_skill_check(6)", instance.exports.gemini_skill_check(6), 36],
  ["gemini_gif_size()", instance.exports.gemini_gif_size(), 17822],
];

for (const [label, got, want] of checks) {
  if (got !== want) {
    throw new Error(`${label}: got ${got}, want ${want}`);
  }
  console.log(`${label} = ${got} PASS`);
}

const gifPtr = instance.exports.gemini_gif_ptr();
console.log(`gemini_gif_ptr() = ${gifPtr} (WASM offset) PASS`);

console.log(`${wasmPath}: ${bytes.length} bytes, zero-import module verified`);
