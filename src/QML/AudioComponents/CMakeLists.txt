qt_add_library(AudioComponentsLib STATIC)

set_target_properties(AudioComponentsLib PROPERTIES AUTOMOC ON)
target_link_libraries(AudioComponentsLib PRIVATE Qt6::Quick)

list(APPEND MODULE_QML_FILES Knob.qml)

qt_add_qml_module(AudioComponentsLib
        URI AudioComponents
        VERSION 1.0
        RESOURCE_PREFIX /sercan.com/imports
        QML_FILES ${MODULE_QML_FILES}
        RESOURCES Images/button.png
)


