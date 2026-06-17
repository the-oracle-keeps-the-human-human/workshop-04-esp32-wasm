idf_component_register(SRCS "chaiklang_wamr_main.c"
                       PRIV_REQUIRES esp_psram pthread
                       EMBED_FILES "chaiklang.wasm")
