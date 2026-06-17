(module
  (func $atom_score (export "atom_score") (param $protons i32) (param $electrons i32) (result i32)
    (i32.add
      (i32.add
        (i32.mul (local.get $protons) (i32.const 31))
        (i32.mul (local.get $electrons) (i32.const 17)))
      (i32.mul
        (i32.sub (local.get $protons) (local.get $electrons))
        (i32.sub (local.get $protons) (local.get $electrons)))))

  (func $pulse (export "pulse") (param $n i32) (result i32)
    (i32.div_s
      (i32.mul
        (local.get $n)
        (i32.add (local.get $n) (i32.const 1)))
      (i32.const 2))))
