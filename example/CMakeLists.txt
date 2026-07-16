add_executable(plugin-ocr-example main.cpp)

target_link_libraries(plugin-ocr-example PUBLIC Qt${QT_MAJOR_VERSION}::Widgets)
