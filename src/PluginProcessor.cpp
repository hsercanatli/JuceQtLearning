#include "PluginProcessor.h"
#include "PluginEditor.h"


AudioPluginAudioProcessor::AudioPluginAudioProcessor()
    : apvts(std::make_shared<juce::AudioProcessorValueTreeState>(*this, nullptr, "params", createParameters())) {
}

juce::AudioProcessorEditor *AudioPluginAudioProcessor::createEditor() {
    return new PluginEditor(*this);
}

void AudioPluginAudioProcessor::prepareToPlay(double, int) {
    previousGain = apvts->getParameter("GAIN")->getValue();
}

void AudioPluginAudioProcessor::processBlock(juce::AudioBuffer<float> &buffer,
                                             juce::MidiBuffer &) {
    if (static_cast<bool>(apvts->getParameter("BYPASS")->getValue()))
        return;

    buffer.applyGain(apvts->getParameter("GAIN")->getValue());


    auto gain = apvts->getParameter("GAIN")->getValue();
    if (juce::approximatelyEqual(gain, previousGain)) {
        buffer.applyGain(gain);
    } else {
        buffer.applyGainRamp(0, buffer.getNumSamples(), previousGain, gain);
        previousGain = gain;
    }
}

void AudioPluginAudioProcessor::releaseResources() {}

juce::AudioProcessor *JUCE_CALLTYPE createPluginFilter() {
    return new AudioPluginAudioProcessor;
}

juce::AudioProcessorValueTreeState::ParameterLayout AudioPluginAudioProcessor::createParameters() {
    juce::AudioProcessorValueTreeState::ParameterLayout params;

    params.add(std::make_unique<juce::AudioParameterFloat>(juce::ParameterID("GAIN", 1), "Gain", 0.0f, 1.f, 0.f));
    params.add(std::make_unique<juce::AudioParameterBool>(juce::ParameterID("BYPASS", 1), "Bypass", false));
    return params;
}