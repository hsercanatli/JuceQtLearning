#pragma once

#include <QObject>
#include <juce_audio_processors/juce_audio_processors.h>

// TODO as value tree listener
class GainModel : public QObject {
    Q_OBJECT

    // Gain
    Q_PROPERTY(qreal gain READ getGainValue NOTIFY gainChanged)
    Q_PROPERTY(qreal minGain READ getMinGainValue CONSTANT)
    Q_PROPERTY(qreal maxGain READ getMaxGainValue CONSTANT)

    // Bypass
    Q_PROPERTY(bool bypass READ getBypassValue NOTIFY bypassChanged)

public:
    GainModel(std::shared_ptr<juce::AudioProcessorValueTreeState> mApvts);

    void updateGain(qreal gain);
    void updateBypass(bool bypass);

    inline qreal getMinGainValue() { return mApvts->getParameterRange("GAIN").getRange().getStart(); }
    inline qreal getMaxGainValue() { return mApvts->getParameterRange("GAIN").getRange().getEnd(); }
    inline qreal getGainValue() { return mApvts->getParameter("GAIN")->getValue(); }

    inline bool getBypassValue() { return static_cast<bool>(mApvts->getParameter("BYPASS")->getValue()); }

signals:
    void gainChanged();
    void bypassChanged();

private:
    std::shared_ptr<juce::AudioProcessorValueTreeState> mApvts;

    Q_DISABLE_COPY_MOVE(GainModel)
};