;; ViaLumen — a tiny, zero-import WebAssembly module.
;; No imports → loads cleanly under wasm3 / WAMR on an ESP32, and identically
;; in a browser. Two pure functions so the result is the same everywhere.
;;
;;   build:  wat2wasm vialumen.wat -o vialumen.wasm
;;   theme:  "ทุกก้าวที่เรียนรู้คือแสง" — each step adds light.
(module
  ;; add(a, b) — sanity check. add(2, 3) = 5
  (func $add (export "add") (param i32 i32) (result i32)
    (i32.add (local.get 0) (local.get 1)))

  ;; lumen(steps) — total light after N steps: the triangular number
  ;; 1 + 2 + ... + N = N*(N+1)/2. Pure, no imports. lumen(8) = 36
  (func $lumen (export "lumen") (param $n i32) (result i32)
    (i32.div_u
      (i32.mul (local.get $n) (i32.add (local.get $n) (i32.const 1)))
      (i32.const 2))))
