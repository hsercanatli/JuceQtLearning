#include "PluginEditor.h"

#include <QGuiApplication>
#include <QLoggingCategory>
#include <QQuickStyle>

Q_LOGGING_CATEGORY(qtEditor, "juce.qt.editor")

using namespace juce;

namespace {
    int argc = 2;
    // You can attach the running app to the qml profiler of Qt Creator
    char* argv[2] = { "_", "-qmljsdebugger=port:53944" };
}// namespace

PluginEditor::PluginEditor(AudioPluginAudioProcessor &p)
    : AudioProcessorEditor(p),
      processorRef(p) {
    qCDebug(qtEditor) << "Creating editor" << this;

    setResizable(false, false);
    setWantsKeyboardFocus(true);

    QCoreApplication::setAttribute(Qt::AA_PluginApplication);
    // to get rid of QML style warnings
    QQuickStyle::setStyle("Basic");

    mQtApp = std::make_unique<QGuiApplication>(argc, argv);
    mQmlApplication = std::make_unique<QMLApplication>(processorRef.apvts);

    mJuceQComponent.setWindow(mQmlApplication->getQMLView());
    addAndMakeVisible(mJuceQComponent);
    childBoundsChanged(&mJuceQComponent);
}

PluginEditor::~PluginEditor() {
    qCDebug(qtEditor) << "Deleting editor" << this;
}

void PluginEditor::resized() {
    qCDebug(qtEditor) << "Editor" << this << "resized";
    mJuceQComponent.setBounds(getLocalBounds());
}

void PluginEditor::childBoundsChanged(Component *) {
    qCDebug(qtEditor) << "Editor" << this << "child bounds changed";
    setSize(mJuceQComponent.getWidth(), mJuceQComponent.getHeight());
}

void PluginEditor::paint(juce::Graphics &) {
    // FIXME: We're still being asked to paint by JUCE. Ideally
    // there would be a way to tell JUCE to skip this component.
    qCDebug(qtEditor) << "Editor" << this << "asked to paint";
}
