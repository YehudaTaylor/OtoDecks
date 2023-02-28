/*
  ==============================================================================

    PlaybackControls.h
    Created: 28 Feb 2023 3:25:38pm
    Author:  yehuda

  ==============================================================================
*/

#pragma once

#include "DJAudioPlayer.h"
#include <JuceHeader.h>


//==============================================================================
/*
 */
class PlaybackControls : public juce::Component,
                         public Button::Listener,
                         public Slider::Listener,
                         public ChangeBroadcaster
{
  public:
    PlaybackControls(DJAudioPlayer* _djAudioPlayer);
    ~PlaybackControls() override;

    void paint(juce::Graphics&) override;
    void resized() override;

    void buttonClicked(Button* button) override;
    void sliderValueChanged(Slider* slider) override;

  private:
    DJAudioPlayer* djAudioPlayer;

    Slider skipSlider;
    TextButton skipForwardButton{"Skip Forward"};
    TextButton skipBackwardButton{"Skip Backwards"};

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PlaybackControls)
};
