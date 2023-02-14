/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "DJAudioPlayer.h"

//==============================================================================
/*
    This component lives inside our window, and this is where you should put
   all your controls and content.
*/
class MainComponent : public AudioAppComponent,
                      public Button::Listener,
                      public Slider::Listener
{
  public:
    //==============================================================================
    MainComponent();
    ~MainComponent();

    //==============================================================================
    void prepareToPlay(int samplesPerBlockExpected,
                       double sampleRate) override;
    void getNextAudioBlock(
        const AudioSourceChannelInfo& bufferToFill) override;
    void releaseResources() override;

    //==============================================================================
    void paint(Graphics& g) override;
    void resized() override;

    void buttonClicked(Button* button) override;

    void sliderValueChanged(Slider* slider) override;

  private:
    //==============================================================================
    // Your private member variables go here...

    TextButton playButton{"PLAY"};
    TextButton stopButton{"STOP"};

    DJAudioPlayer player1;

    Slider posSlider;
    juce::Slider gainSlider;

    juce::TextButton loadButton;
    juce::FileChooser fChooser{"Select a file..."};

    bool playing;
    double gain;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MainComponent)
};
