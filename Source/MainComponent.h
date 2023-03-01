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

  private:
    //==============================================================================
    // Your private member variables go here...
    AudioFormatManager formatManager;
    // note we need to tell it how large the cache is. 20 files are ok for now.
    AudioThumbnailCache thumbnailCache{20};

    PlaylistComponent playlistComponent;

    DJAudioPlayer player1{formatManager};
    DeckGUI deck1{&player1, formatManager, thumbnailCache, &playlistComponent};

    DJAudioPlayer player2{formatManager};
    DeckGUI deck2{&player2, formatManager, thumbnailCache, &playlistComponent};

    MixerAudioSource mixerSource;

    bool playing;
    double gain;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MainComponent)
};
