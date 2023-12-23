//
// Created by Sercan Atlı on 23/12/2023.
//

#include <QGuiApplication>
#include <QQuickStyle>

#include "QMLApplication.h"
#include "PluginProcessor.h"

int main(int argc, char* argv[]) {
    juce::ScopedJuceInitialiser_GUI initializer;
    AudioPluginAudioProcessor pluginProcessor;

//    QCoreApplication::setAttribute(Qt::AA_PluginApplication);
    // to get rid of QML style warnings
    QQuickStyle::setStyle("Basic");

    QGuiApplication qtApp = QGuiApplication(argc, argv);
    QMLApplication qmlApp = QMLApplication(pluginProcessor.apvts);
    qmlApp.getQMLView()->show();
    return qtApp.exec();
}
