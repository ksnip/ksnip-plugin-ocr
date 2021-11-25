
add_library(plugin-ocr SHARED PluginOcr.cpp OcrWrapper.cpp)
target_link_libraries(plugin-ocr PRIVATE Qt5::Widgets tesseract)
target_compile_options(plugin-ocr PRIVATE ${COMPILE_OPTIONS})
