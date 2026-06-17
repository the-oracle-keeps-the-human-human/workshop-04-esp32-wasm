#pragma once
#include "esphome/core/component.h"

namespace esphome {
namespace gif_wamr {

// Runs our gifapp.wasm (an import-free WASM reactor that decodes an embedded GIF
// with the AnimatedGIF core) on the ESP32-S3 under the WebAssembly Micro Runtime,
// then reads the decoded RGBA framebuffer back into native memory. Same host
// sequence as the PlatformIO/ESP-IDF version, wrapped as an ESPHome Component.
class GifWamr : public Component {
 public:
  void setup() override;
  void dump_config() override;
  // run after PSRAM + core are up; the wasm linear memory lives in PSRAM.
  float get_setup_priority() const override { return setup_priority::LATE; }
};

}  // namespace gif_wamr
}  // namespace esphome
