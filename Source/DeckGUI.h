/*
  ==============================================================================

    DeckGUI.h
    Created: 15 Feb 2023 2:37:48pm
    Author:  yehuda

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

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
    TextButton playButton{"PLAY"};
    TextButton stopButton{"STOP"};
    TextButton loadButton{"LOAD"};
    Slider volumeSlider;
    Slider positionSlider;
    Slider speedSlider;
    FileChooser fChooser{"Select a file..."};


    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(DeckGUI)
};
