cmake_minimum_required(VERSION 3.16)

project(CHORDARPER VERSION 0.0.1)

set(CMAKE_CXX_STANDARD 17)

if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC" )
endif()

add_subdirectory(Vendor/JUCE-LV2)

# juce_add_binary_data(ChordArperBinaries
#         HEADER_NAME ChordArperBinaryData.h
#         NAMESPACE ChordArperBin
#         SOURCES Fonts/overpass-regular.otf)

juce_add_plugin(ChordArper
        COMPANY_NAME "The ChordArper contributors"
        IS_SYNTH TRUE
        NEEDS_MIDI_INPUT TRUE
        NEEDS_MIDI_OUTPUT TRUE
        IS_MIDI_EFFECT TRUE
        VST_NUM_MIDI_INS 1
        VST_NUM_MIDI_OUTS 1
        VST3_CATEGORIES "Fx Instrument Tools"
        AU_MAIN_TYPE "kAudioUnitType_MIDIProcessor"
        EDITOR_WANTS_KEYBOARD_FOCUS TRUE
        COPY_PLUGIN_AFTER_BUILD TRUE
        PLUGIN_MANUFACTURER_CODE Larx
        PLUGIN_CODE Larx
        FORMATS AU VST3 LV2 Standalone
        LV2_URI https://github.com/baboulaz/chordarper
        NEEDS_CURL FALSE
        PRODUCT_NAME "ChordArper")

if(MINGW)
    target_compile_options(ChordArper PRIVATE "-Wa,-mbig-obj")
endif()

target_sources(ChordArper
        PRIVATE

        Source/music-utils/Chord.cpp Source/music-utils/Chord.h
        Source/music-utils/Scale.cpp Source/music-utils/Scale.h

        Source/ArpeggiatorPanel.cpp Source/ArpeggiatorPanel.h
        Source/ChordPanel.cpp Source/ChordPanel.h
        Source/GridItemPanel.cpp Source/GridItemPanel.h
        Source/PluginEditor.cpp Source/PluginEditor.h
        Source/PluginProcessor.cpp Source/PluginProcessor.h
        Source/ScalePanel.cpp Source/ScalePanel.h
        )

target_compile_definitions(ChordArper
        PUBLIC
        JUCE_WEB_BROWSER=0
        JUCE_USE_CURL=1
        JUCE_USE_FLAC=0
        JUCE_USE_OGGVORBIS=0
        JUCE_USE_WINDOWS_MEDIA_FORMAT=0
        JUCE_VST3_CAN_REPLACE_VST2=0
        JUCE_DISPLAY_SPLASH_SCREEN=0 # we are GPL so we are allowed
        )

target_link_libraries(ChordArper
        PRIVATE
        # ChordArperBinaries
        juce::juce_audio_utils
        juce::juce_audio_plugin_client
        PUBLIC
        juce::juce_recommended_config_flags
        juce::juce_recommended_lto_flags
        juce::juce_recommended_warning_flags)

