;; Singhasingha Oracle — zero-import wasm core  🦁
;; "ฟ้าร้องก่อนฝน — สิงห์เฝ้าโค้ดก่อน production"
;;
;; Two pure integer functions, identical on every runtime (browser/zig/wasm3/WAMR):
;;   roar(n)    = 1 + 2 + ... + n          (the pride's strength accumulates)
;;   guard(a,b) = a*a + b*b                (the sentinel's watch: sum of squares)
;; Zero imports → loads cleanly under wasm3 and WAMR on the chip.
(module
  (func $roar (export "roar") (param $n i32) (result i32)
    (local $sum i32)
    (local $i i32)
    (local.set $sum (i32.const 0))
    (local.set $i (i32.const 1))
    (block $done
      (loop $loop
        (br_if $done (i32.gt_s (local.get $i) (local.get $n)))
        (local.set $sum (i32.add (local.get $sum) (local.get $i)))
        (local.set $i (i32.add (local.get $i) (i32.const 1)))
        (br $loop)))
    (local.get $sum))

  (func $guard (export "guard") (param $a i32) (param $b i32) (result i32)
    (i32.add
      (i32.mul (local.get $a) (local.get $a))
      (i32.mul (local.get $b) (local.get $b)))))
