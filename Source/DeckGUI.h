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
#include "PlaybackControls.h"
#include "PlaylistComponent.h"

//==============================================================================
/*
 */
class DeckGUI : public Component,
                public Button::Listener,
                public Slider::Listener,
                public FileDragAndDropTarget,
                public Timer, public ChangeListener, public ActionListener
{
  public:
    DeckGUI(DJAudioPlayer* _djAudioPlayer,
            AudioFormatManager& formatManagerToUse,
            AudioThumbnailCache& cacheToUse, PlaylistComponent* _playlistComponent);
    ~DeckGUI() override;

    void paint(juce::Graphics&) override;
    void resized() override;

    void buttonClicked(Button* button) override;
    void sliderValueChanged(Slider* slider) override;

    bool isInterestedInFileDrag(const StringArray& files) override;
    void filesDropped(const StringArray& files, int x, int y) override;

    void timerCallback() override;

    void changeListenerCallback(ChangeBroadcaster* source) override;
    void actionListenerCallback(const String &message) override;

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

    PlaybackControls playbackControls{djAudioPlayer};

    PlaylistComponent* playlistComponent;


    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(DeckGUI)
};
