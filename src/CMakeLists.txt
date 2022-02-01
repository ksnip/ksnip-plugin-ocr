set(KSNIP_PLUGIN_OCR_SRCS
        ${CMAKE_SOURCE_DIR}/src/PluginOcr.cpp
        ${CMAKE_SOURCE_DIR}/src/OcrWrapper.cpp
        )


add_library(ksnip-plugin-ocr SHARED ${KSNIP_PLUGIN_OCR_SRCS})
target_link_libraries(ksnip-plugin-ocr PRIVATE Qt5::Widgets tesseract leptonica)
target_compile_options(ksnip-plugin-ocr PRIVATE ${COMPILE_OPTIONS})

if (UNIX AND NOT APPLE)
    install(TARGETS ksnip-plugin-ocr)
else ()
    message("DEBUG: NOT UNIX")
endif ()

# uninstall target
if (UNIX AND NOT APPLE)
    if(NOT TARGET uninstall)
        configure_file(
                "${CMAKE_CURRENT_SOURCE_DIR}/../cmake/cmake_uninstall.cmake.in"
                "${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake"
                IMMEDIATE @ONLY)

        add_custom_target(uninstall COMMAND ${CMAKE_COMMAND} -P ${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake)
    endif ()
endif ()