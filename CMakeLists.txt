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

set(QT_MIN_VERSION 5.9.4)
find_package(Qt5 ${QT_MIN_VERSION} REQUIRED Widgets)

include(FeatureSummary)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

add_subdirectory(src)

if (BUILD_EXAMPLE)
	add_subdirectory(example)
endif (BUILD_EXAMPLE)

if (BUILD_TESTS)
	find_package(Qt5 ${QT_MIN_VERSION} REQUIRED Test)
	enable_testing()
	add_subdirectory(tests)
endif (BUILD_TESTS)

