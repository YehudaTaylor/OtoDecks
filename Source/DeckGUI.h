/*
  ==============================================================================

    DeckGUI.h
    Created: 15 Feb 2023 2:37:48pm
    Author:  yehuda

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "DJAudioPlayer.h"
#include "WaveformDisplay.h"

//==============================================================================
/*
 */
class DeckGUI : public Component,
                public Button::Listener,
                public Slider::Listener,
                public FileDragAndDropTarget
{
  public:
    DeckGUI(DJAudioPlayer* _djAudioPlayer,
            AudioFormatManager& formatManagerToUse,
            AudioThumbnailCache& cacheToUse);
    ~DeckGUI() override;

    void paint(juce::Graphics&) override;
    void resized() override;

    void buttonClicked(Button* button) override;
    void sliderValueChanged(Slider* slider) override;

    bool isInterestedInFileDrag(const StringArray& files) override;
    void filesDropped(const StringArray& files, int x, int y) override;

  private:
    TextButton playButton{"PLAY"};
    TextButton stopButton{"STOP"};
    TextButton loadButton{"LOAD"};
    Slider volumeSlider;
    Slider positionSlider;
    Slider speedSlider;
    FileChooser fChooser{"Select a file..."};

    DJAudioPlayer* djAudioPlayer;

    WaveformDisplay waveformDisplay;


    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(DeckGUI)
};
