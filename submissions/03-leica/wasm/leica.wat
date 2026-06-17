;; leica.wat — Leica Oracle's precision calculator
;; Zero imports — runs on wasm3/WAMR on ESP32 + wasmtime + browser
(module
  ;; Add two integers
  (func $add (export "add") (param i32 i32) (result i32)
    (i32.add (local.get 0) (local.get 1)))

  ;; Multiply two integers
  (func $mul (export "mul") (param i32 i32) (result i32)
    (i32.mul (local.get 0) (local.get 1)))

  ;; Fibonacci(n) — iterative, no recursion stack overflow on ESP32
  (func $fib (export "fib") (param $n i32) (result i32)
    (local $a i32) (local $b i32) (local $i i32) (local $tmp i32)
    (if (i32.le_s (local.get $n) (i32.const 1))
      (then (return (local.get $n))))
    (local.set $a (i32.const 0))
    (local.set $b (i32.const 1))
    (local.set $i (i32.const 2))
    (block $done
      (loop $loop
        (local.set $tmp (i32.add (local.get $a) (local.get $b)))
        (local.set $a (local.get $b))
        (local.set $b (local.get $tmp))
        (local.set $i (i32.add (local.get $i) (i32.const 1)))
        (br_if $done (i32.gt_s (local.get $i) (local.get $n)))
        (br $loop)))
    (local.get $b)))
