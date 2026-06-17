import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import esp32
from esphome.const import CONF_ID

CODEOWNERS = ["@MEYD-605"]
DEPENDENCIES = ["esp32"]

gif_wamr_ns = cg.esphome_ns.namespace("gif_wamr")
GifWamr = gif_wamr_ns.class_("GifWamr", cg.Component)

CONFIG_SCHEMA = cv.Schema(
    {
        cv.GenerateID(): cv.declare_id(GifWamr),
    }
).extend(cv.COMPONENT_SCHEMA)


async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    await cg.register_component(var, config)

    # WebAssembly Micro Runtime (Espressif managed component, IDF registry).
    esp32.add_idf_component(name="espressif/wasm-micro-runtime", ref="2.4.0")

    # The hard-won WAMR knobs (same as the PlatformIO sdkconfig.defaults):
    #  - zero-imports module → no WASI (also avoids WAMR's espidf_file.c)
    #  - zig/LLVM emits reference-types encoding → REF_TYPES on
    #  - big decoder functions overflow the fast interp → classic interp
    esp32.add_idf_sdkconfig_option("CONFIG_WAMR_ENABLE_LIBC_WASI", False)
    esp32.add_idf_sdkconfig_option("CONFIG_WAMR_ENABLE_REF_TYPES", True)
    esp32.add_idf_sdkconfig_option("CONFIG_WAMR_INTERP_CLASSIC", True)

    # wasm linear memory (512 KB→2 MB) lives in PSRAM; WAMR's small runtime
    # structs stay in internal RAM (cache-safe). The `psram:` YAML block enables
    # SPIRAM + USE_MALLOC; we only need the always-internal threshold here.
    esp32.add_idf_sdkconfig_option("CONFIG_SPIRAM_MALLOC_ALWAYSINTERNAL", 8192)
    esp32.add_idf_sdkconfig_option("CONFIG_SPIRAM_TRY_ALLOCATE_WHEN_FAILS", True)
