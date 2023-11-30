#include "GainModel.h"


GainModel::GainModel(std::shared_ptr<juce::AudioProcessorValueTreeState> apvts)
    : mApvts(apvts) {
    updateGain(mApvts->getParameter("GAIN")->getValue());
}

void GainModel::updateGain(qreal gain) {
    mApvts->getParameter("GAIN")->setValue(static_cast<float>(gain));

    emit gainChanged();
}

void GainModel::updateBypass(bool bypass) {
    mApvts->getParameter("BYPASS")->setValue(bypass);

    emit bypassChanged();
}
