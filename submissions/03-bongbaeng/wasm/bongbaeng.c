// บ๊องแบ๊ง wasm — zero-import, pure functions (โหลดได้ใต้ wasm3/WAMR บน ESP32) 🐆
// build: clang --target=wasm32 -nostdlib -O2 -Wl,--no-entry -Wl,--export-all
//        (หรือ zig build-exe -target wasm32-freestanding)

// baseline ที่ reviewer เช็ค: add(2,3)=5
__attribute__((export_name("add")))
int add(int a, int b) { return a + b; }

// cheetah_spots(n): ผลรวมจุดลายสะสม deterministic + pure (บ๊อง flavor)
// สูตร: ผลรวม (i*7 mod 13) สำหรับ i=1..n  → cheetah_spots(10)=60
__attribute__((export_name("cheetah_spots")))
int cheetah_spots(int n) {
  int s = 0;
  for (int i = 1; i <= n; i++) s += (i * 7) % 13;
  return s;
}
