
add_library(plugin-ocr SHARED PluginOcr.cpp)
target_link_libraries(plugin-ocr PRIVATE Qt5::Widgets)
target_compile_options(plugin-ocr PRIVATE ${COMPILE_OPTIONS})
