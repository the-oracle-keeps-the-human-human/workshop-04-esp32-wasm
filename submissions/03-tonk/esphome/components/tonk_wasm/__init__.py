"""ESPHome external component: tonk_wasm.

Runs the zero-import tonk.wasm under wasm3 ON the ESP32 and exposes the LIVE
results (computed on-device, not hard-coded) so an LVGL label can show them.
"""
import esphome.codegen as cg
import esphome.config_validation as cv

CODEOWNERS = ["@tonk"]

tonk_wasm_ns = cg.esphome_ns.namespace("tonk_wasm")
TonkWasm = tonk_wasm_ns.class_("TonkWasm", cg.Component)

CONFIG_SCHEMA = cv.Schema(
    {cv.GenerateID(): cv.declare_id(TonkWasm)}
).extend(cv.COMPONENT_SCHEMA)


async def to_code(config):
    var = cg.new_Pvariable(config[cv.CONF_ID])
    await cg.register_component(var, config)
    # wasm3 — the on-chip interpreter that runs our wasm (Arduino framework).
    cg.add_library("wasm3/Wasm3", "^0.5.0")
