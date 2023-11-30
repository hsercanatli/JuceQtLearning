#pragma once

#include <juce_audio_processors/juce_audio_processors.h>

class AudioPluginAudioProcessor : public juce::AudioProcessor, public juce::ValueTree::Listener {
public:
    AudioPluginAudioProcessor();
    ~AudioPluginAudioProcessor() override = default;

    const juce::String getName() const override { return JucePlugin_Name; }

    bool hasEditor() const override { return true; }
    juce::AudioProcessorEditor *createEditor() override;

    void prepareToPlay(double, int) override;
    void processBlock(juce::AudioBuffer<float> &, juce::MidiBuffer &) override;
    void releaseResources() override;

    bool acceptsMidi() const override { return false; }
    bool producesMidi() const override { return false; }
    double getTailLengthSeconds() const override { return 0.0; }
    int getNumPrograms() override { return 1; }
    int getCurrentProgram() override { return 0; }
    void setCurrentProgram(int) override {}
    const juce::String getProgramName(int) override { return {}; }
    void changeProgramName(int, const juce::String &) override {}
    void getStateInformation(juce::MemoryBlock &) override {}
    void setStateInformation(const void *, int) override {}

    std::shared_ptr<juce::AudioProcessorValueTreeState> apvts;

private:
    float previousGain{0.f};
    juce::AudioProcessorValueTreeState::ParameterLayout createParameters();

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(AudioPluginAudioProcessor)
};
