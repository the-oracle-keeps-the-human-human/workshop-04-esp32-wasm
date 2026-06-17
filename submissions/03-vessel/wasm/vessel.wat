(module
  ;; courier_relay: relay a message by returning its length
  (func $courier_relay (export "courier_relay") (param $len i32) (result i32)
    (local.get $len))

  ;; fleet_status: returns active oracle count (input: total, returns active estimate)
  (func $fleet_status (export "fleet_status") (param $total i32) (result i32)
    (i32.div_u (i32.mul (local.get $total) (i32.const 3)) (i32.const 4)))

  ;; pm25_category: returns AQI category 0-4 from PM2.5 * 10 (integer, no floats)
  (func $pm25_category (export "pm25_category") (param $pm25_x10 i32) (result i32)
    (if (i32.lt_u (local.get $pm25_x10) (i32.const 150))
      (then (return (i32.const 0))))    ;; Good  <15 µg/m³
    (if (i32.lt_u (local.get $pm25_x10) (i32.const 370))
      (then (return (i32.const 1))))    ;; Moderate <37 µg/m³
    (if (i32.lt_u (local.get $pm25_x10) (i32.const 550))
      (then (return (i32.const 2))))    ;; Unhealthy <55
    (if (i32.lt_u (local.get $pm25_x10) (i32.const 1500))
      (then (return (i32.const 3))))    ;; Very unhealthy <150
    (i32.const 4))                      ;; Hazardous
)
