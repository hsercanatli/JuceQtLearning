#pragma once

#include <QObject>
#include <QQuickView>

#include "Controllers/GainController.h"
#include "Models/GainModel.h"

#include <juce_audio_processors/juce_audio_processors.h>


class QMLApplication : public QObject {
    Q_OBJECT

public:
    QMLApplication(std::shared_ptr<juce::AudioProcessorValueTreeState>);

    std::shared_ptr<QQuickView> getQMLView() { return qmlView; }

private:
    void initializeModels();
    void initializeControllers();
    void registerContent();

    std::shared_ptr<juce::AudioProcessorValueTreeState> mApvts;

    // QML
    std::shared_ptr<QQuickView> qmlView;

    // Models
    std::shared_ptr<GainModel> mGainModel;

    // Controllers
    std::unique_ptr<GainController> mGainController;

    Q_DISABLE_COPY_MOVE(QMLApplication)
};
