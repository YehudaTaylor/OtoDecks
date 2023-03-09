/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "DJAudioPlayer.h"
#include "DeckGUI.h"
#include "PlaylistComponent.h"

//==============================================================================
/*
    This component lives inside our window, and this is where you should put
   all your controls and content.
*/
class MainComponent : public AudioAppComponent
{
  public:
    MainComponent();
    ~MainComponent();

    /** called before playback starts, to let the processor prepare itself*/
    void prepareToPlay(int samplesPerBlockExpected,
                       double sampleRate) override;

    /** called repeatedly to fetch subsequent blocks of audio data*/
    void getNextAudioBlock(
        const AudioSourceChannelInfo& bufferToFill) override;

    /** called after playback has stopped, to let the object free up any
     * resources it no longer needs*/
    void releaseResources() override;

    /** component overrides this, for drawing it's content*/
    void paint(Graphics& g) override;

    /** component overrides this, to place child components in the correct
     * place when the width or height changes*/
    void resized() override;

  private:
    AudioFormatManager formatManager;

    AudioThumbnailCache thumbnailCache{20};

    PlaylistComponent playlistComponent{formatManager};

    DJAudioPlayer player1{formatManager};
    DeckGUI deck1{&player1, formatManager, thumbnailCache, &playlistComponent};

    DJAudioPlayer player2{formatManager};
    DeckGUI deck2{&player2, formatManager, thumbnailCache, &playlistComponent};

    MixerAudioSource mixerSource;

    /** todo check if these are being used. remove if not*/
    bool playing;
    double gain;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MainComponent)
};
