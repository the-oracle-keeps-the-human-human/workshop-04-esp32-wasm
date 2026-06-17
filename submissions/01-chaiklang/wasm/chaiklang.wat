;; ChaiKlang Oracle (ชายกลาง) — the Middle Switchboard, as a tiny WebAssembly module.
;; No imports → loads cleanly under wasm3 on the ESP32. Built: wat2wasm chaiklang.wat -o chaiklang.wasm
(module
  ;; lion_pulse(n) = 1+2+...+n — the switchboard heartbeat (proof of on-chip wasm execution)
  (func $lion_pulse (export "lion_pulse") (param $n i32) (result i32)
    (local $i i32) (local $acc i32)
    (block $done
      (br_if $done (i32.lt_s (local.get $n) (i32.const 1)))
      (loop $L
        (local.set $i (i32.add (local.get $i) (i32.const 1)))
        (local.set $acc (i32.add (local.get $acc) (local.get $i)))
        (br_if $L (i32.lt_s (local.get $i) (local.get $n)))))
    (local.get $acc))

  ;; route(a,b) = a*b + a — a toy "switchboard route" so we exercise two exports
  (func $route (export "route") (param $a i32) (param $b i32) (result i32)
    (i32.add (i32.mul (local.get $a) (local.get $b)) (local.get $a)))
)
