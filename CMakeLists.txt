CMAKE_MINIMUM_REQUIRED(VERSION 3.15.0)

project(PsyBass
        VERSION 0.1.0
        DESCRIPTION "Darkpsy/Forest bass plugin")

if(APPLE)
# M-series CPUs M1/M2/M3 etc
set(CMAKE_OSX_ARCHITECTURES "arm64" CACHE STRING "")

# Choose how old a macOS version you want to support.
set(CMAKE_OSX_DEPLOYMENT_TARGET "13.0" CACHE STRING "")
endif()

# Steinberg SDK settings
set(SMTG_ENABLE_VST3_PLUGIN_EXAMPLES OFF CACHE BOOL "" FORCE)
set(SMTG_ENABLE_VST3_HOSTING_EXAMPLES OFF CACHE BOOL "" FORCE)
# No Steinberg VSTGUI for now
set(SMTG_ENABLE_VSTGUI_SUPPORT OFF CACHE BOOL "" FORCE)
set(SMTG_ENABLE_WAYLAND_SUPPORT OFF CACHE BOOL "" FORCE)

set(vst3SDK_SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/external/vst3sdk" )

add_subdirectory(${vst3SDK_SRC_DIR} ${PROJECT_BINARY_DIR}/vst3sdk)
smtg_enable_vst3_sdk()

smtg_add_vst3plugin(PsyBass
        source/plugin/controller.h
        source/plugin/controller.cpp
        source/plugin/processor.h
        source/plugin/processor.cpp
        source/plugin/psybass_cids.h
        source/plugin/params.h
        source/plugin/version.h
        source/plugin/psybass_entry.cpp
        source/dsp/oscillator.cpp
        source/dsp/oscillator.hpp
)

target_include_directories(PsyBass
        PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/source
)

target_link_libraries(PsyBass PRIVATE sdk)

smtg_target_configure_version_file(PsyBass)