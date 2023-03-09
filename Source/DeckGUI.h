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
#include "PlaybackControls.h"
#include "PlaylistComponent.h"
#include "WaveformDisplay.h"


//==============================================================================
/*
 */
class DeckGUI : public Component,
                public Button::Listener,
                public Slider::Listener,
                public FileDragAndDropTarget,
                public Timer,
                public ActionListener
{
  public:
    DeckGUI(DJAudioPlayer* _djAudioPlayer,
            AudioFormatManager& formatManagerToUse,
            AudioThumbnailCache& cacheToUse,
            PlaylistComponent* _playlistComponent);
    ~DeckGUI() override;

    /** component overrides this, for drawing it's content*/
    void paint(juce::Graphics&) override;

    /** component overrides this, to place child components in the correct
     * place when the width or height changes*/
    void resized() override;

    /** receives callbacks when buttons in the component are clicked. this is
     * used by the play, stop and load buttons*/
    void buttonClicked(Button* button) override;

    /** this is called when the slider's value is changed in some way. this is
     * used to update the track's gain, postion and speed*/
    void sliderValueChanged(Slider* slider) override;

    /** Callback to check whether this target is interested in the set of files
     * being offered*/
    bool isInterestedInFileDrag(const StringArray& files) override;

    /** callback that is called when a file is dropped onto the component. the
     * URL for the file is passed in through the StringArray& files, which is
     * then used to load the track into the player and waveform display*/
    void filesDropped(const StringArray& files, int x, int y) override;

    /** callback routine that actually gets called periodically. this is used
     * to update the position rectangle in the waveform display*/
    void timerCallback() override;

    /** callback listener that recieve messages broadcasted from the playlist
     * component. the playlist component sends out an action message when a
     * button for a specific track is clicked, the message is the URL of the
     * track to be loaded into the deck. this listner receives this message and
     * loads the track into the deck, as well as the waveform display*/
    void actionListenerCallback(const String& message) override;

  private:
    TextButton playButton{"PLAY"};
    TextButton stopButton{"STOP"};
    TextButton loadButton{"LOAD"};

    Slider volumeSlider;
    Slider positionSlider;
    Slider speedSlider;

    Label volumeLabel;
    Label positionLabel;
    Label speedLabel;

    FileChooser fChooser{"Select a file..."};

    DJAudioPlayer* djAudioPlayer;

    WaveformDisplay waveformDisplay;

    PlaybackControls playbackControls{djAudioPlayer};

    PlaylistComponent* playlistComponent;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(DeckGUI)
};
