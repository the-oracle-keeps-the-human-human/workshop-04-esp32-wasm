import { readFile } from "node:fs/promises";

const wasmPath = process.argv[2] ?? "atom-orbit.wasm";
const bytes = await readFile(wasmPath);
const { instance } = await WebAssembly.instantiate(bytes, {});

const checks = [
  ["atom_score(6,6)", instance.exports.atom_score(6, 6), 288],
  ["pulse(12)", instance.exports.pulse(12), 78],
];

for (const [label, got, want] of checks) {
  if (got !== want) {
    throw new Error(`${label}: got ${got}, want ${want}`);
  }
  console.log(`${label} = ${got} PASS`);
}

console.log(`${wasmPath}: ${bytes.length} bytes, zero-import module verified`);
