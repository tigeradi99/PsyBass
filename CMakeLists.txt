CMAKE_MINIMUM_REQUIRED(VERSION 3.15.0)

project(PsyBass
        VERSION 1.0.0
        DESCRIPTION "Darkpsy/Forest bass plugin")

set(vst3SDK_SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/external/vst3sdk" )

add_subdirectory(${vst3SDK_SRC_DIR} ${PROJECT_BINARY_DIR}/vst3sdk)
smtg_enable_vst3_sdk()
