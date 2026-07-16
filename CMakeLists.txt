cmake_minimum_required(VERSION 3.5)
project(ksnip-plugin-ocr LANGUAGES CXX VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_CXX_VISIBILITY_PRESET hidden)
set(CMAKE_VISIBILITY_INLINES_HIDDEN 1)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

option(BUILD_TESTS "Build Unit Tests" OFF)
option(BUILD_EXAMPLE "Build Example Application" ON)

include(GNUInstallDirs)

configure_file(src/BuildConfig.h.in ${CMAKE_CURRENT_BINARY_DIR}/src/BuildConfig.h)

# A Qt plugin must be built against the SAME Qt major version as the host that
# loads it (ksnip). ksnip defaults to Qt5, so default to Qt5 here too, but allow
# overriding with -DQT_MAJOR_VERSION=6 to match a Qt6 ksnip build. A mismatch
# makes QPluginLoader silently reject the plugin ("Failed to extract plugin meta
# data"), so it never appears in ksnip.
set(QT_MIN_VERSION 5.9.4)
if (NOT DEFINED QT_MAJOR_VERSION)
	set(QT_MAJOR_VERSION 5)
endif ()
find_package(Qt${QT_MAJOR_VERSION} REQUIRED Widgets)

# The OCR engine is provided by libtesseract, which in turn depends on
# leptonica. Locate them via pkg-config so we fail configuration early with a
# clear message instead of failing at link time.
find_package(PkgConfig REQUIRED)
pkg_check_modules(Tesseract REQUIRED IMPORTED_TARGET tesseract)
pkg_check_modules(Leptonica REQUIRED IMPORTED_TARGET lept)

include(FeatureSummary)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

add_subdirectory(src)

if (BUILD_EXAMPLE)
	add_subdirectory(example)
endif (BUILD_EXAMPLE)

if (BUILD_TESTS)
	find_package(Qt${QT_MAJOR_VERSION} REQUIRED Test)
	enable_testing()
	add_subdirectory(tests)
endif (BUILD_TESTS)

