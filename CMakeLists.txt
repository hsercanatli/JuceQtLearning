cmake_minimum_required(VERSION 3.15)
project(JuceQtLearning VERSION 0.0.1)

option(BUILD_STANDALONE_QT_APP False)
set(CMAKE_AUTOMOC ON)

# packages
find_package(JUCE CONFIG REQUIRED)
find_package(Qt6 REQUIRED COMPONENTS Core Gui Quick QuickControls2 Core5Compat)

# Qt standalone app
if (${BUILD_STANDALONE_QT_APP})
    qt_add_executable(JuceQtLearning src/main.cpp)
else()
    qt_standard_project_setup()
    # Stop warning about a changed import prefix.
    qt6_policy(SET QTP0001 NEW)
    # juce plugin
    juce_add_plugin(JuceQtLearning
           COMPANY_NAME "JuceQtLearning Company"
           PRODUCT_NAME "JuceQtLearning"
           BUNDLE_ID "io.JuceQtLearning"
           FORMATS AU VST3 Standalone
           COPY_PLUGIN_AFTER_BUILD TRUE
    )
endif()
qt_import_qml_plugins(JuceQtLearning)

# qml plugins
add_subdirectory(src/QML/AudioComponents)
add_subdirectory(src/QML/Utilities)
# Make Qt Creator aware of where the QML modules live
set (_QML_IMPORT_PATHS "")
## Add new module paths here.
list (APPEND _QML_IMPORT_PATHS ${CMAKE_BINARY_DIR}/src/QML)

qt_add_qml_module(JuceQtLearning
    URI Sercan
    VERSION 1.0
    RESOURCE_PREFIX /sercan.com/imports
    QML_FILES src/QML/main.qml
    SOURCES src/Controllers/GainController.h src/Models/GainModel.h src/Models/GainModel.cpp
    IMPORT_PATH ${_QML_IMPORT_PATHS}
)
set (QML_IMPORT_PATH ${_QML_IMPORT_PATHS} CACHE STRING "Path used to locate CMake modules by Qt Creator" FORCE)


file(GLOB_RECURSE _headers src/*.h)
file(GLOB_RECURSE _sources src/*.cpp)

target_sources(JuceQtLearning PRIVATE ${_headers} ${_sources})

if(NOT ${BUILD_STANDALONE_QT_APP})
    target_compile_definitions(JuceQtLearning
           PUBLIC
           JUCE_WEB_BROWSER=0
           JUCE_USE_CURL=0
           JUCE_VST3_CAN_REPLACE_VST2=0
    )
endif()

target_link_libraries(JuceQtLearning
        PRIVATE
        juce::juce_audio_utils
        Qt6::Core
        Qt6::Gui
        Qt6::Quick
        Qt6::QuickControls2
        Qt6::Core5Compat
        UtilitiesLibplugin
        AudioComponentsLibplugin

        PUBLIC
        juce::juce_recommended_config_flags
        juce::juce_recommended_lto_flags
        juce::juce_recommended_warning_flags
)

# Ease up on juce_recommended_warning_flags a bit
target_compile_options(juce_recommended_warning_flags INTERFACE
        -Wno-gnu-zero-variadic-macro-arguments
        -Wno-switch-enum
        -Wno-missing-prototypes
)
