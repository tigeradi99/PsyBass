CMAKE_MINIMUM_REQUIRED(VERSION 3.15.0)

project(PsyBass
        VERSION 1.0.0
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
