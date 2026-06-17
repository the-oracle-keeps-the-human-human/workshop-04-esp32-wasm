#!/usr/bin/env python3
"""Verify the Sentinel wasm exports with wasmtime."""

from __future__ import annotations

import sys
from pathlib import Path

from wasmtime import Instance, Module, Store


def main() -> int:
    wasm_path = Path(sys.argv[1]) if len(sys.argv) > 1 else Path("sentinel.wasm")
    wasm = wasm_path.read_bytes()

    store = Store()
    module = Module(store.engine, wasm)
    instance = Instance(store, module, [])
    exports = instance.exports(store)

    flame = exports["flame"]
    sense = exports["sense"]

    checks = [
        ("flame(10)", flame(store, 10), 385),
        ("sense(3,4)", sense(store, 3, 4), 25),
    ]

    for label, got, want in checks:
        if got != want:
            raise SystemExit(f"{label}: got {got}, want {want}")
        print(f"{label} = {got} PASS")

    print(f"{wasm_path.name}: {len(wasm)} bytes, exports verified")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
