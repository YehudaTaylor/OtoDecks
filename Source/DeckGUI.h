/*
  ==============================================================================

    DeckGUI.h
    Created: 15 Feb 2023 2:37:48pm
    Author:  yehuda

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
 */
class DeckGUI : public juce::Component
{
  public:
    DeckGUI();
    ~DeckGUI() override;

    void paint(juce::Graphics&) override;
    void resized() override;

  private:
    TextButton playButton;
    TextButton stopButton;
    TextButton loadButton;
    Slider volumeSlider;
    Slider positionSlider;
    Slider speedSlider;
    FileChooser fChooser{"Select a file..."};


    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(DeckGUI)
};
