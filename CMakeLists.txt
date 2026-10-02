# Builds OtoDecks with CMake as an alternative to the Projucer (.jucer) project.
# JUCE is downloaded automatically, so no separate JUCE install is needed.
cmake_minimum_required(VERSION 3.22)
project(OtoDecks VERSION 1.0.0)

include(FetchContent)
FetchContent_Declare(JUCE
    GIT_REPOSITORY https://github.com/juce-framework/JUCE.git
    GIT_TAG 8.0.6
    GIT_SHALLOW TRUE)
FetchContent_MakeAvailable(JUCE)

juce_add_gui_app(OtoDecks
    PRODUCT_NAME "OtoDecks"
    COMPANY_NAME "Alizea2")

juce_generate_juce_header(OtoDecks)

target_sources(OtoDecks PRIVATE
    Source/Main.cpp
    Source/MainComponent.cpp
    Source/DeckGUI.cpp
    Source/DJAudioPlayer.cpp
    Source/WaveformDisplay.cpp
    Source/PanControl.cpp)

# DeckGUI includes "../JuceLibraryCode/JuceHeader.h" (the Projucer location),
# so provide a small forwarding header that points at the CMake-generated one.
set(SHIM_DIR "${CMAKE_CURRENT_BINARY_DIR}/projucer_shim")
file(MAKE_DIRECTORY "${SHIM_DIR}/include")
file(WRITE "${SHIM_DIR}/JuceLibraryCode/JuceHeader.h" "#pragma once\n#include <JuceHeader.h>\n")
target_include_directories(OtoDecks PRIVATE "${SHIM_DIR}/include")

target_compile_definitions(OtoDecks PRIVATE
    JUCE_WEB_BROWSER=0
    JUCE_USE_CURL=0
    JUCE_APPLICATION_NAME_STRING="$<TARGET_PROPERTY:OtoDecks,JUCE_PRODUCT_NAME>"
    JUCE_APPLICATION_VERSION_STRING="$<TARGET_PROPERTY:OtoDecks,JUCE_VERSION>")

target_link_libraries(OtoDecks
    PRIVATE
        juce::juce_audio_utils
        juce::juce_audio_processors
        juce::juce_gui_extra
    PUBLIC
        juce::juce_recommended_config_flags
        juce::juce_recommended_lto_flags
        juce::juce_recommended_warning_flags)
