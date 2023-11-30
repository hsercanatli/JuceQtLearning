#pragma once

#include <QQuickView>
#include <juce_gui_basics/juce_gui_basics.h>

class QWindow;

class JuceQComponent : public juce::Component {
public:
    JuceQComponent();
    ~JuceQComponent() override;

    void setWindow(std::shared_ptr<QQuickView> window);

private:
    class Pimpl;
    std::unique_ptr<Pimpl> pimpl;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(JuceQComponent)
};
