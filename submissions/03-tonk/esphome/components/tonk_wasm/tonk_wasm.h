#pragma once
#include "esphome/core/component.h"
#include <string>

namespace esphome {
namespace tonk_wasm {

// Loads tonk.wasm under wasm3 at boot, calls its pure exports on the chip, and
// stores the LIVE results as a formatted line. An LVGL label reads `line` so the
// screen shows numbers the wasm actually computed on-device (not hard-coded).
class TonkWasm : public Component {
 public:
  void setup() override;
  void dump_config() override;
  float get_setup_priority() const override { return setup_priority::DATA; }

  // The live one-line result, e.g. "grow(7)=26mm  leaves(12)=8  fib(20)=6765".
  // Exposed as a static so an LVGL text lambda can read it without an id() dance.
  static std::string line;
  static bool ran;
};

}  // namespace tonk_wasm
}  // namespace esphome
