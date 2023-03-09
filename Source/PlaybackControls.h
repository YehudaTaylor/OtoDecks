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

    /** component overrides this, for drawing it's content*/
    void paint(juce::Graphics&) override;

    /** component overrides this, to place child components in the correct
     * place when the width or height changes*/
    void resized() override;

    /** receives callbacks when buttons in the component are clicked. this is
     * used by the skipForward and skipBackward buttons*/
    void buttonClicked(Button* button) override;

    /** this is called when the slider's value is changed in some way. this is
     * used to update the amount of time used in the skip forward and backward
     * buttons*/
    void sliderValueChanged(Slider* slider) override;

  private:
    DJAudioPlayer* djAudioPlayer;

    Slider skipSlider;

    TextButton skipForwardButton{"Skip Forward"};

    TextButton skipBackwardButton{"Skip Backwards"};

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PlaybackControls)
};
