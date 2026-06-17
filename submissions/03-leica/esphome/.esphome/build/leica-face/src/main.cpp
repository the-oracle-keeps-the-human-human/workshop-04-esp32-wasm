// Auto generated code by esphome
// ========== AUTO GENERATED INCLUDE BLOCK BEGIN ===========
#include "esphome.h"
using namespace esphome;
alignas(logger::Logger) static unsigned char logger__logger_logger_id__pstorage[sizeof(logger::Logger)];
static logger::Logger *const logger_logger_id = reinterpret_cast<logger::Logger *>(logger__logger_logger_id__pstorage);
#ifndef __PICOLIBC__
using std::isnan;
#endif
using std::min;
using std::max;
#include <new>
using namespace light;
using namespace display;
alignas(wifi::WiFiComponent) static unsigned char wifi__wifi_wificomponent_id__pstorage[sizeof(wifi::WiFiComponent)];
static wifi::WiFiComponent *const wifi_wificomponent_id = reinterpret_cast<wifi::WiFiComponent *>(wifi__wifi_wificomponent_id__pstorage);
alignas(mdns::MDNSComponent) static unsigned char mdns__mdns_mdnscomponent_id__pstorage[sizeof(mdns::MDNSComponent)];
static mdns::MDNSComponent *const mdns_mdnscomponent_id = reinterpret_cast<mdns::MDNSComponent *>(mdns__mdns_mdnscomponent_id__pstorage);
alignas(preferences::IntervalSyncer) static unsigned char preferences__preferences_intervalsyncer_id__pstorage[sizeof(preferences::IntervalSyncer)];
static preferences::IntervalSyncer *const preferences_intervalsyncer_id = reinterpret_cast<preferences::IntervalSyncer *>(preferences__preferences_intervalsyncer_id__pstorage);
using namespace spi;
alignas(spi::QuadSPIComponent) static unsigned char spi__lcd_spi__pstorage[sizeof(spi::QuadSPIComponent)];
static spi::QuadSPIComponent *const lcd_spi = reinterpret_cast<spi::QuadSPIComponent *>(spi__lcd_spi__pstorage);
alignas(esp32::ESP32InternalGPIOPin) static unsigned char esp32__esp32_esp32internalgpiopin_id__pstorage[sizeof(esp32::ESP32InternalGPIOPin)];
static esp32::ESP32InternalGPIOPin *const esp32_esp32internalgpiopin_id = reinterpret_cast<esp32::ESP32InternalGPIOPin *>(esp32__esp32_esp32internalgpiopin_id__pstorage);
alignas(psram::PsramComponent) static unsigned char psram__psram_psramcomponent_id__pstorage[sizeof(psram::PsramComponent)];
static psram::PsramComponent *const psram_psramcomponent_id = reinterpret_cast<psram::PsramComponent *>(psram__psram_psramcomponent_id__pstorage);
using namespace output;
alignas(esp32::ESP32InternalGPIOPin) static unsigned char esp32__esp32_esp32internalgpiopin_id_2__pstorage[sizeof(esp32::ESP32InternalGPIOPin)];
static esp32::ESP32InternalGPIOPin *const esp32_esp32internalgpiopin_id_2 = reinterpret_cast<esp32::ESP32InternalGPIOPin *>(esp32__esp32_esp32internalgpiopin_id_2__pstorage);
alignas(ledc::LEDCOutput) static unsigned char ledc__backlight_pwm__pstorage[sizeof(ledc::LEDCOutput)];
static ledc::LEDCOutput *const backlight_pwm = reinterpret_cast<ledc::LEDCOutput *>(ledc__backlight_pwm__pstorage);
alignas(monochromatic::MonochromaticLightOutput) static unsigned char monochromatic__monochromatic_monochromaticlightoutput_id__pstorage[sizeof(monochromatic::MonochromaticLightOutput)];
static monochromatic::MonochromaticLightOutput *const monochromatic_monochromaticlightoutput_id = reinterpret_cast<monochromatic::MonochromaticLightOutput *>(monochromatic__monochromatic_monochromaticlightoutput_id__pstorage);
alignas(light::LightState) static unsigned char light__backlight__pstorage[sizeof(light::LightState)];
static light::LightState *const backlight = reinterpret_cast<light::LightState *>(light__backlight__pstorage);
alignas(mipi_spi::MipiSpi<uint16_t, mipi_spi::PIXEL_MODE_16, true, mipi_spi::PIXEL_MODE_16, mipi_spi::BUS_TYPE_QUAD, 320, 480, 0, 0, 0, false>) static unsigned char mipi_spi__lcd__pstorage[sizeof(mipi_spi::MipiSpi<uint16_t, mipi_spi::PIXEL_MODE_16, true, mipi_spi::PIXEL_MODE_16, mipi_spi::BUS_TYPE_QUAD, 320, 480, 0, 0, 0, false>)];
static mipi_spi::MipiSpi<uint16_t, mipi_spi::PIXEL_MODE_16, true, mipi_spi::PIXEL_MODE_16, mipi_spi::BUS_TYPE_QUAD, 320, 480, 0, 0, 0, false> *const lcd = reinterpret_cast<mipi_spi::MipiSpi<uint16_t, mipi_spi::PIXEL_MODE_16, true, mipi_spi::PIXEL_MODE_16, mipi_spi::BUS_TYPE_QUAD, 320, 480, 0, 0, 0, false> *>(mipi_spi__lcd__pstorage);
alignas(esp32::ESP32InternalGPIOPin) static unsigned char esp32__esp32_esp32internalgpiopin_id_3__pstorage[sizeof(esp32::ESP32InternalGPIOPin)];
static esp32::ESP32InternalGPIOPin *const esp32_esp32internalgpiopin_id_3 = reinterpret_cast<esp32::ESP32InternalGPIOPin *>(esp32__esp32_esp32internalgpiopin_id_3__pstorage);
using namespace lvgl;
static lv_group_t *lv_group_t_id;
alignas(lvgl::LvglComponent) static unsigned char lvgl__lvgl_lvglcomponent_id__pstorage[sizeof(lvgl::LvglComponent)];
static lvgl::LvglComponent *const lvgl_lvglcomponent_id = reinterpret_cast<lvgl::LvglComponent *>(lvgl__lvgl_lvglcomponent_id__pstorage);
alignas(LvPageType) static unsigned char esphome__main_page__pstorage[sizeof(LvPageType)];
static LvPageType *const main_page = reinterpret_cast<LvPageType *>(esphome__main_page__pstorage);
static lv_obj_t *lv_label_t_id;
static lv_obj_t *lv_label_t_id_2;
static lv_obj_t *lv_label_t_id_3;
static lv_obj_t *lv_label_t_id_4;
static lv_obj_t *lv_label_t_id_5;
static lv_obj_t *lv_label_t_id_6;
static lv_obj_t *lv_label_t_id_7;
static constexpr size_t ESPHOME_LOOPING_COMPONENT_COUNT = \
  (1 * HasLoopOverride<logger::Logger>::value) + \
  (1 * HasLoopOverride<wifi::WiFiComponent>::value) + \
  (1 * HasLoopOverride<mdns::MDNSComponent>::value) + \
  (1 * HasLoopOverride<preferences::IntervalSyncer>::value) + \
  (1 * HasLoopOverride<spi::QuadSPIComponent>::value) + \
  (1 * HasLoopOverride<psram::PsramComponent>::value) + \
  (1 * HasLoopOverride<ledc::LEDCOutput>::value) + \
  (1 * HasLoopOverride<light::LightState>::value) + \
  (1 * HasLoopOverride<mipi_spi::MipiSpi<uint16_t, mipi_spi::PIXEL_MODE_16, true, mipi_spi::PIXEL_MODE_16, mipi_spi::BUS_TYPE_QUAD, 320, 480, 0, 0, 0, false>>::value) + \
  (1 * HasLoopOverride<lvgl::LvglComponent>::value);
namespace esphome {
static const char COMP_SRC_TABLE_STR_0[] PROGMEM = "logger";
static const char COMP_SRC_TABLE_STR_1[] PROGMEM = "wifi";
static const char COMP_SRC_TABLE_STR_2[] PROGMEM = "mdns";
static const char COMP_SRC_TABLE_STR_3[] PROGMEM = "preferences";
static const char COMP_SRC_TABLE_STR_4[] PROGMEM = "spi";
static const char COMP_SRC_TABLE_STR_5[] PROGMEM = "psram";
static const char COMP_SRC_TABLE_STR_6[] PROGMEM = "ledc.output";
static const char COMP_SRC_TABLE_STR_7[] PROGMEM = "light";
static const char COMP_SRC_TABLE_STR_8[] PROGMEM = "display";
static const char COMP_SRC_TABLE_STR_9[] PROGMEM = "lvgl";
static const char *const COMP_SRC_TABLE[] PROGMEM = {COMP_SRC_TABLE_STR_0, COMP_SRC_TABLE_STR_1, COMP_SRC_TABLE_STR_2, COMP_SRC_TABLE_STR_3, COMP_SRC_TABLE_STR_4, COMP_SRC_TABLE_STR_5, COMP_SRC_TABLE_STR_6, COMP_SRC_TABLE_STR_7, COMP_SRC_TABLE_STR_8, COMP_SRC_TABLE_STR_9};
const LogString *component_source_lookup(uint8_t index) {
  if (index == 0 || index > 10) return LOG_STR("<unknown>");
  return reinterpret_cast<const LogString *>(
    progmem_read_ptr(&COMP_SRC_TABLE[index - 1]));
}
}  // namespace esphome
// ========== AUTO GENERATED INCLUDE BLOCK END ==========="

void setup() {
  // ========== AUTO GENERATED CODE BEGIN ===========
  // logger:
  //   level: INFO
  //   hardware_uart: USB_SERIAL_JTAG
  //   id: logger_logger_id
  //   baud_rate: 115200
  //   tx_buffer_size: 512
  //   deassert_rts_dtr: false
  //   task_log_buffer_size: 768
  //   logs: {}
  //   runtime_tag_levels: false
  new(logger_logger_id) logger::Logger(115200);
  logger_logger_id->create_pthread_key();
  logger_logger_id->set_uart_selection(logger::UART_SELECTION_USB_SERIAL_JTAG);
  logger_logger_id->pre_setup();
  logger_logger_id->set_log_level(ESPHOME_LOG_LEVEL_INFO);
  // network:
  //   enable_ipv6: false
  //   min_ipv6_addr_count: 0
  // esphome:
  //   name: leica-face
  //   friendly_name: Leica Oracle Face
  //   comment: 320x480 QSPI — Leica Oracle WASM status display
  //   min_version: 2026.5.3
  //   build_path: build/leica-face
  //   platformio_options: {}
  //   environment_variables: {}
  //   includes: []
  //   includes_c: []
  //   libraries: []
  //   name_add_mac_suffix: false
  //   debug_scheduler: false
  //   areas: []
  //   devices: []
  new (&App) Application();
  App.pre_setup("leica-face", 10, "Leica Oracle Face", 17);
  App.looping_components_.init(ESPHOME_LOOPING_COMPONENT_COUNT);
  // light:
  // display:
  App.register_component_(logger_logger_id, 1);
  // wifi:
  //   id: wifi_wificomponent_id
  //   domain: .local
  //   reboot_timeout: 15min
  //   power_save_mode: LIGHT
  //   fast_connect: false
  //   enable_btm: false
  //   enable_rrm: false
  //   passive_scan: false
  //   enable_on_boot: true
  //   post_connect_roaming: true
  //   min_auth_mode: WPA2
  //   networks:
  //     - ssid: !secret 'wifi_ssid'
  //       password: !secret 'wifi_password'
  //       id: wifi_wifiap_id
  //       priority: 0
  //   use_address: leica-face.local
  new(wifi_wificomponent_id) wifi::WiFiComponent();
  wifi_wificomponent_id->set_use_address("leica-face.local");
  wifi_wificomponent_id->init_sta(1);
  {
  wifi::WiFiAP wifi_wifiap_id = wifi::WiFiAP();
  wifi_wifiap_id.set_ssid("your-wifi-ssid");
  wifi_wifiap_id.set_password("your-wifi-password");
  wifi_wifiap_id.set_priority(0);
  wifi_wificomponent_id->add_sta(wifi_wifiap_id);
  }
  wifi_wificomponent_id->set_reboot_timeout(900000);
  wifi_wificomponent_id->set_power_save_mode(wifi::WIFI_POWER_SAVE_LIGHT);
  wifi_wificomponent_id->set_min_auth_mode(wifi::WIFI_MIN_AUTH_MODE_WPA2);
  App.register_component_(wifi_wificomponent_id, 2);
  // mdns:
  //   id: mdns_mdnscomponent_id
  //   disabled: false
  //   services: []
  new(mdns_mdnscomponent_id) mdns::MDNSComponent();
  App.register_component_(mdns_mdnscomponent_id, 3);
  // preferences:
  //   id: preferences_intervalsyncer_id
  //   flash_write_interval: 60s
  new(preferences_intervalsyncer_id) preferences::IntervalSyncer();
  preferences_intervalsyncer_id->set_write_interval(60000);
  App.register_component_(preferences_intervalsyncer_id, 4);
  // spi:
  //   - id: lcd_spi
  //     clk_pin:
  //       number: 47
  //       mode:
  //         output: true
  //         input: false
  //         open_drain: false
  //         pullup: false
  //         pulldown: false
  //       id: esp32_esp32internalgpiopin_id
  //       inverted: false
  //       ignore_pin_validation_error: false
  //       ignore_strapping_warning: false
  //       drive_strength: 20.0
  //     data_pins:
  //       - 21
  //       - 48
  //       - 40
  //       - 39
  //     interface: hardware
  //     type: quad
  //     interface_index: 0
  new(lcd_spi) spi::QuadSPIComponent();
  App.register_component_(lcd_spi, 5);
  new(esp32_esp32internalgpiopin_id) esp32::ESP32InternalGPIOPin();
  esp32_esp32internalgpiopin_id->set_pin(::GPIO_NUM_47);
  esp32_esp32internalgpiopin_id->set_drive_strength(::GPIO_DRIVE_CAP_2);
  esp32_esp32internalgpiopin_id->set_flags(gpio::Flags::FLAG_OUTPUT);
  lcd_spi->set_clk(esp32_esp32internalgpiopin_id);
  lcd_spi->set_data_pins({21, 48, 40, 39});
  lcd_spi->set_interface(SPI2_HOST);
  lcd_spi->set_interface_name("SPI2_HOST");
  // esp32:
  //   board: esp32-s3-devkitc-1
  //   variant: ESP32S3
  //   flash_size: 16MB
  //   framework:
  //     type: esp-idf
  //     version: 5.5.4
  //     sdkconfig_options: {}
  //     log_level: ERROR
  //     advanced:
  //       compiler_optimization: SIZE
  //       enable_idf_experimental_features: false
  //       enable_lwip_assert: true
  //       ignore_efuse_custom_mac: false
  //       ignore_efuse_mac_crc: false
  //       sram1_as_iram: false
  //       enable_lwip_mdns_queries: true
  //       enable_lwip_bridge_interface: false
  //       enable_lwip_tcpip_core_locking: true
  //       enable_lwip_check_thread_safety: true
  //       disable_libc_locks_in_iram: true
  //       disable_vfs_support_termios: true
  //       disable_vfs_support_select: true
  //       disable_vfs_support_dir: true
  //       freertos_in_iram: false
  //       ringbuf_in_iram: false
  //       heap_in_iram: false
  //       execute_from_psram: false
  //       loop_task_stack_size: 8192
  //       enable_ota_rollback: false
  //       use_full_certificate_bundle: false
  //       include_builtin_idf_components: []
  //       enable_full_printf: false
  //       disable_debug_stubs: true
  //       disable_ocd_aware: true
  //       disable_usb_serial_jtag_secondary: true
  //       disable_dev_null_vfs: true
  //       disable_mbedtls_peer_cert: true
  //       disable_mbedtls_pkcs7: true
  //       disable_regi2c_in_iram: true
  //       adc_oneshot_in_iram: false
  //       disable_fatfs: true
  //     components: []
  //     platform_version: https:github.com/pioarduino/platform-espressif32/releases/download/55.03.38-1/platform-espressif32.zip
  //     source: pioarduino/framework-espidf@https:github.com/pioarduino/esp-idf/releases/download/v5.5.4/esp-idf-v5.5.4.tar.xz
  //   watchdog_timeout: 5s
  //   cpu_frequency: 240MHZ
  // psram:
  //   mode: octal
  //   speed: 80MHZ
  //   id: psram_psramcomponent_id
  //   enable_ecc: false
  //   disabled: false
  //   ignore_not_found: true
  new(psram_psramcomponent_id) psram::PsramComponent();
  App.register_component_(psram_psramcomponent_id, 6);
  // output:
  // output.ledc:
  //   platform: ledc
  //   pin:
  //     number: 1
  //     mode:
  //       output: true
  //       input: false
  //       open_drain: false
  //       pullup: false
  //       pulldown: false
  //     id: esp32_esp32internalgpiopin_id_2
  //     inverted: false
  //     ignore_pin_validation_error: false
  //     ignore_strapping_warning: false
  //     drive_strength: 20.0
  //   id: backlight_pwm
  //   frequency: 5000.0
  //   zero_means_zero: false
  new(esp32_esp32internalgpiopin_id_2) esp32::ESP32InternalGPIOPin();
  esp32_esp32internalgpiopin_id_2->set_pin(::GPIO_NUM_1);
  esp32_esp32internalgpiopin_id_2->set_drive_strength(::GPIO_DRIVE_CAP_2);
  esp32_esp32internalgpiopin_id_2->set_flags(gpio::Flags::FLAG_OUTPUT);
  new(backlight_pwm) ledc::LEDCOutput(esp32_esp32internalgpiopin_id_2);
  App.register_component_(backlight_pwm, 7);
  backlight_pwm->set_frequency(5000.0f);
  // light.monochromatic:
  //   platform: monochromatic
  //   id: backlight
  //   name: Backlight
  //   output: backlight_pwm
  //   restore_mode: ALWAYS_ON
  //   default_transition_length: 200ms
  //   disabled_by_default: false
  //   gamma_correct: 2.8
  //   flash_transition_length: 0s
  //   output_id: monochromatic_monochromaticlightoutput_id
  new(monochromatic_monochromaticlightoutput_id) monochromatic::MonochromaticLightOutput();
  new(backlight) light::LightState(monochromatic_monochromaticlightoutput_id);
  App.register_component_(backlight, 8);
  backlight->set_restore_mode(light::LIGHT_ALWAYS_ON);
  backlight->set_default_transition_length(200);
  backlight->set_flash_transition_length(0);
  backlight->set_gamma_correct(2.8f);
  static constexpr uint16_t gamma_2_8_fwd[] PROGMEM = {0x00, 0x01, 0x01, 0x01, 0x01, 0x01, 0x02, 0x03, 0x04, 0x06, 0x08, 0x0A, 0x0D, 0x10, 0x13, 0x18, 0x1C, 0x21, 0x27, 0x2E, 0x35, 0x3C, 0x45, 0x4E, 0x58, 0x62, 0x6E, 0x7A, 0x87, 0x95, 0xA4, 0xB3, 0xC4, 0xD6, 0xE8, 0xFC, 0x111, 0x127, 0x13D, 0x155, 0x16E, 0x189, 0x1A4, 0x1C1, 0x1DE, 0x1FE, 0x21E, 0x23F, 0x262, 0x287, 0x2AC, 0x2D3, 0x2FC, 0x326, 0x351, 0x37E, 0x3AC, 0x3DC, 0x40D, 0x440, 0x474, 0x4AA, 0x4E2, 0x51B, 0x556, 0x593, 0x5D1, 0x611, 0x653, 0x696, 0x6DC, 0x723, 0x76C, 0x7B7, 0x803, 0x852, 0x8A2, 0x8F5, 0x949, 0x99F, 0x9F8, 0xA52, 0xAAE, 0xB0D, 0xB6D, 0xBD0, 0xC34, 0xC9B, 0xD04, 0xD6F, 0xDDC, 0xE4C, 0xEBE, 0xF32, 0xFA8, 0x1020, 0x109B, 0x1118, 0x1198, 0x121A, 0x129E, 0x1325, 0x13AE, 0x1439, 0x14C7, 0x1558, 0x15EB, 0x1680, 0x1718, 0x17B3, 0x1850, 0x18F0, 0x1992, 0x1A37, 0x1ADF, 0x1B89, 0x1C36, 0x1CE5, 0x1D98, 0x1E4D, 0x1F05, 0x1FC0, 0x207D, 0x213D, 0x2200, 0x22C6, 0x238F, 0x245B, 0x252A, 0x25FB, 0x26D0, 0x27A7, 0x2882, 0x295F, 0x2A40, 0x2B23, 0x2C0A, 0x2CF3, 0x2DE0, 0x2ED0, 0x2FC3, 0x30B9, 0x31B2, 0x32AF, 0x33AE, 0x34B1, 0x35B7, 0x36C1, 0x37CD, 0x38DD, 0x39F1, 0x3B07, 0x3C21, 0x3D3E, 0x3E5F, 0x3F83, 0x40AA, 0x41D5, 0x4303, 0x4435, 0x456A, 0x46A3, 0x47DF, 0x491F, 0x4A62, 0x4BA9, 0x4CF4, 0x4E42, 0x4F94, 0x50E9, 0x5242, 0x539F, 0x54FF, 0x5663, 0x57CB, 0x5936, 0x5AA6, 0x5C19, 0x5D90, 0x5F0A, 0x6089, 0x620B, 0x6391, 0x651C, 0x66AA, 0x683B, 0x69D1, 0x6B6B, 0x6D09, 0x6EAA, 0x7050, 0x71FA, 0x73A8, 0x7559, 0x770F, 0x78C9, 0x7A87, 0x7C4A, 0x7E10, 0x7FDA, 0x81A9, 0x837C, 0x8553, 0x872E, 0x890D, 0x8AF1, 0x8CD9, 0x8EC5, 0x90B6, 0x92AB, 0x94A4, 0x96A1, 0x98A3, 0x9AA9, 0x9CB4, 0x9EC3, 0xA0D7, 0xA2EF, 0xA50B, 0xA72C, 0xA952, 0xAB7B, 0xADAA, 0xAFDD, 0xB214, 0xB451, 0xB691, 0xB8D7, 0xBB21, 0xBD6F, 0xBFC3, 0xC21B, 0xC477, 0xC6D9, 0xC93F, 0xCBAA, 0xCE19, 0xD08E, 0xD307, 0xD585, 0xD807, 0xDA8F, 0xDD1C, 0xDFAD, 0xE243, 0xE4DE, 0xE77E, 0xEA23, 0xECCD, 0xEF7C, 0xF230, 0xF4E9, 0xF7A7, 0xFA6A, 0xFD32, 0xFFFF};
  backlight->set_gamma_table(gamma_2_8_fwd);
  backlight->add_effects({});
  App.register_light(backlight, "Backlight", 878769956, 0);
  monochromatic_monochromaticlightoutput_id->set_output(backlight_pwm);
  // display.mipi_spi:
  //   platform: mipi_spi
  //   model: AXS15231
  //   id: lcd
  //   spi_id: lcd_spi
  //   cs_pin:
  //     number: 45
  //     mode:
  //       output: true
  //       input: false
  //       open_drain: false
  //       pullup: false
  //       pulldown: false
  //     id: esp32_esp32internalgpiopin_id_3
  //     inverted: false
  //     ignore_pin_validation_error: false
  //     ignore_strapping_warning: false
  //     drive_strength: 20.0
  //   dimensions:
  //     width: 320
  //     height: 480
  //     offset_height: 0
  //     offset_width: 0
  //   color_order: RGB
  //   invert_colors: false
  //   data_rate: 40000000.0
  //   update_interval: 4294967295ms
  //   auto_clear_enabled: false
  //   bus_mode: quad
  //   spi_mode: MODE0
  //   byte_order: big_endian
  //   color_depth: '16'
  //   draw_rounding: 8
  //   pixel_mode: 16bit
  //   use_axis_flips: false
  new(lcd) mipi_spi::MipiSpi<uint16_t, mipi_spi::PIXEL_MODE_16, true, mipi_spi::PIXEL_MODE_16, mipi_spi::BUS_TYPE_QUAD, 320, 480, 0, 0, 0, false>();
  lcd->set_init_sequence({187, 8, 0, 0, 0, 0, 0, 0, 90, 165, 193, 1, 51, 187, 8, 0, 0, 0, 0, 0, 0, 0, 0, 58, 1, 85, 32, 0, 17, 0, 41, 0});
  lcd->set_model("AXS15231");
  lcd->set_update_interval(4294967295UL);
  App.register_component_(lcd, 9);
  lcd->set_auto_clear(false);
  lcd->set_spi_parent(lcd_spi);
  lcd->set_write_only(true);
  new(esp32_esp32internalgpiopin_id_3) esp32::ESP32InternalGPIOPin();
  esp32_esp32internalgpiopin_id_3->set_pin(::GPIO_NUM_45);
  esp32_esp32internalgpiopin_id_3->set_drive_strength(::GPIO_DRIVE_CAP_2);
  esp32_esp32internalgpiopin_id_3->set_flags(gpio::Flags::FLAG_OUTPUT);
  lcd->set_cs_pin(esp32_esp32internalgpiopin_id_3);
  lcd->set_data_rate(40000000.0f);
  lcd->set_mode(spi::MODE0);
  // lvgl:
  //   - displays:
  //       - lcd
  //     bg_color: 0
  //     pages:
  //       - id: main_page
  //         bg_color: 0
  //         bg_opa: 1.0
  //         pad_all: 8
  //         widgets:
  //           - label:
  //               align: LV_ALIGN_TOP_MID
  //               y: 20
  //               text_font: montserrat_28
  //               text_color: 518143
  //               text: Leica Oracle
  //               id: lv_label_t_id
  //           - label:
  //               align: LV_ALIGN_TOP_MID
  //               y: 60
  //               text_font: montserrat_16
  //               text_color: 8947848
  //               text: Father Oracle — Precision Optics
  //               id: lv_label_t_id_2
  //           - label:
  //               align: LV_ALIGN_CENTER
  //               y: -40
  //               text_font: montserrat_28
  //               text_color: 16755200
  //               text: WASM OK
  //               id: lv_label_t_id_3
  //           - label:
  //               align: LV_ALIGN_CENTER
  //               y: 10
  //               text_font: montserrat_16
  //               text_color: 3789651
  //               text: add(2,3) = 5
  //               id: lv_label_t_id_4
  //           - label:
  //               align: LV_ALIGN_CENTER
  //               y: 40
  //               text_font: montserrat_16
  //               text_color: 3789651
  //               text: mul(7,6) = 42
  //               id: lv_label_t_id_5
  //           - label:
  //               align: LV_ALIGN_CENTER
  //               y: 70
  //               text_font: montserrat_16
  //               text_color: 3789651
  //               text: fib(10) = 55
  //               id: lv_label_t_id_6
  //           - label:
  //               align: LV_ALIGN_BOTTOM_MID
  //               y: -20
  //               text_font: montserrat_14
  //               text_color: 4473924
  //               text: the lens that sees clearly
  //               id: lv_label_t_id_7
  //         skip: false
  //     update_interval: 1s
  //     id: lvgl_lvglcomponent_id
  //     align_to_lambda_id: lvgl_lvlambdacomponent_id
  //     color_depth: 16
  //     default_font: montserrat_14
  //     full_refresh: false
  //     update_when_display_idle: false
  //     draw_rounding: 8
  //     buffer_size: 0.0
  //     log_level: WARN
  //     byte_order: big_endian
  //     page_wrap: true
  //     transparency_key: 1024
  //     touchscreens: []
  //     encoders: []
  //     keypads: []
  //     default_group: lv_group_t_id
  //     resume_on_input: true
  LvglComponent::esphome_lvgl_init();
  lv_group_t_id = lv_group_create();
  lv_group_set_default(lv_group_t_id);
  new(lvgl_lvglcomponent_id) lvgl::LvglComponent({lcd}, 0.0f, false, 8, true, false, lvgl::ROTATION_UNUSED);
  lvgl_lvglcomponent_id->set_update_interval(1000);
  App.register_component_(lvgl_lvglcomponent_id, 10);
  lvgl_lvglcomponent_id->set_big_endian(true);
  lv_obj_set_style_bg_color(lvgl_lvglcomponent_id->get_screen_active(), lv_color_make(0, 0, 0), LV_PART_MAIN);
  lvgl_lvglcomponent_id->set_page_wrap(true);
  new(main_page) LvPageType(false);
  lvgl_lvglcomponent_id->add_page(main_page);
  lv_obj_set_style_bg_color(main_page->obj, lv_color_make(0, 0, 0), LV_PART_MAIN);
  lv_obj_set_style_bg_color(main_page->obj, lv_color_make(0, 0, 0), LV_PART_MAIN);
  lv_obj_set_style_bg_opa(main_page->obj, static_cast<uint8_t>(255.0f), LV_PART_MAIN);
  lv_obj_set_style_pad_all(main_page->obj, 8, LV_PART_MAIN);
  #line 70 "/Users/switchaphon/ghq/github.com/switchaphon/workshop-04-esp32-wasm/submissions/03-leica/esphome/leica-face.yaml"
   lv_label_t_id = lv_label_create(main_page->obj);
  lv_obj_set_style_align(lv_label_t_id, LV_ALIGN_TOP_MID, LV_PART_MAIN);
  lv_obj_set_style_text_color(lv_label_t_id, lv_color_make(7, 231, 255), LV_PART_MAIN);
  lv_obj_set_style_text_font(lv_label_t_id, &lv_font_montserrat_28, LV_PART_MAIN);
  lv_obj_set_style_y(lv_label_t_id, 20, LV_PART_MAIN);
  lv_label_set_text(lv_label_t_id, "Leica Oracle");
  #line 76 "/Users/switchaphon/ghq/github.com/switchaphon/workshop-04-esp32-wasm/submissions/03-leica/esphome/leica-face.yaml"
   lv_label_t_id_2 = lv_label_create(main_page->obj);
  lv_obj_set_style_align(lv_label_t_id_2, LV_ALIGN_TOP_MID, LV_PART_MAIN);
  lv_obj_set_style_text_color(lv_label_t_id_2, lv_color_make(136, 136, 136), LV_PART_MAIN);
  lv_obj_set_style_text_font(lv_label_t_id_2, &lv_font_montserrat_16, LV_PART_MAIN);
  lv_obj_set_style_y(lv_label_t_id_2, 60, LV_PART_MAIN);
  lv_label_set_text(lv_label_t_id_2, "Father Oracle \342\200\224 Precision Optics");
  #line 82 "/Users/switchaphon/ghq/github.com/switchaphon/workshop-04-esp32-wasm/submissions/03-leica/esphome/leica-face.yaml"
   lv_label_t_id_3 = lv_label_create(main_page->obj);
  lv_obj_set_style_align(lv_label_t_id_3, LV_ALIGN_CENTER, LV_PART_MAIN);
  lv_obj_set_style_text_color(lv_label_t_id_3, lv_color_make(255, 170, 0), LV_PART_MAIN);
  lv_obj_set_style_text_font(lv_label_t_id_3, &lv_font_montserrat_28, LV_PART_MAIN);
  lv_obj_set_style_y(lv_label_t_id_3, -40, LV_PART_MAIN);
  lv_label_set_text(lv_label_t_id_3, "WASM OK");
  #line 88 "/Users/switchaphon/ghq/github.com/switchaphon/workshop-04-esp32-wasm/submissions/03-leica/esphome/leica-face.yaml"
   lv_label_t_id_4 = lv_label_create(main_page->obj);
  lv_obj_set_style_align(lv_label_t_id_4, LV_ALIGN_CENTER, LV_PART_MAIN);
  lv_obj_set_style_text_color(lv_label_t_id_4, lv_color_make(57, 211, 83), LV_PART_MAIN);
  lv_obj_set_style_text_font(lv_label_t_id_4, &lv_font_montserrat_16, LV_PART_MAIN);
  lv_obj_set_style_y(lv_label_t_id_4, 10, LV_PART_MAIN);
  lv_label_set_text(lv_label_t_id_4, "add(2,3) = 5");
  #line 94 "/Users/switchaphon/ghq/github.com/switchaphon/workshop-04-esp32-wasm/submissions/03-leica/esphome/leica-face.yaml"
   lv_label_t_id_5 = lv_label_create(main_page->obj);
  lv_obj_set_style_align(lv_label_t_id_5, LV_ALIGN_CENTER, LV_PART_MAIN);
  lv_obj_set_style_text_color(lv_label_t_id_5, lv_color_make(57, 211, 83), LV_PART_MAIN);
  lv_obj_set_style_text_font(lv_label_t_id_5, &lv_font_montserrat_16, LV_PART_MAIN);
  lv_obj_set_style_y(lv_label_t_id_5, 40, LV_PART_MAIN);
  lv_label_set_text(lv_label_t_id_5, "mul(7,6) = 42");
  #line 100 "/Users/switchaphon/ghq/github.com/switchaphon/workshop-04-esp32-wasm/submissions/03-leica/esphome/leica-face.yaml"
   lv_label_t_id_6 = lv_label_create(main_page->obj);
  lv_obj_set_style_align(lv_label_t_id_6, LV_ALIGN_CENTER, LV_PART_MAIN);
  lv_obj_set_style_text_color(lv_label_t_id_6, lv_color_make(57, 211, 83), LV_PART_MAIN);
  lv_obj_set_style_text_font(lv_label_t_id_6, &lv_font_montserrat_16, LV_PART_MAIN);
  lv_obj_set_style_y(lv_label_t_id_6, 70, LV_PART_MAIN);
  lv_label_set_text(lv_label_t_id_6, "fib(10) = 55");
  #line 106 "/Users/switchaphon/ghq/github.com/switchaphon/workshop-04-esp32-wasm/submissions/03-leica/esphome/leica-face.yaml"
   lv_label_t_id_7 = lv_label_create(main_page->obj);
  lv_obj_set_style_align(lv_label_t_id_7, LV_ALIGN_BOTTOM_MID, LV_PART_MAIN);
  lv_obj_set_style_text_color(lv_label_t_id_7, lv_color_make(68, 68, 68), LV_PART_MAIN);
  lv_obj_set_style_text_font(lv_label_t_id_7, &lv_font_montserrat_14, LV_PART_MAIN);
  lv_obj_set_style_y(lv_label_t_id_7, -20, LV_PART_MAIN);
  lv_label_set_text(lv_label_t_id_7, "the lens that sees clearly");
  // =========== AUTO GENERATED CODE END ============
  App.setup();
}

void loop() {
  App.loop();
}
