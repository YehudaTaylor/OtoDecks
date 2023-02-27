/*
  ==============================================================================

    WaveformDisplay.h
    Created: 27 Feb 2023 10:40:21am
    Author:  yehuda

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

//==============================================================================
/*
 */
class WaveformDisplay : public juce::Component, public ChangeListener
{
  public:
    WaveformDisplay(AudioFormatManager& formatManagerToUse,
                    AudioThumbnailCache& cacheToUse);
    ~WaveformDisplay() override;

    void paint(juce::Graphics&) override;
    void resized() override;

    void loadURL(URL audioURL);
    void changeListenerCallback(ChangeBroadcaster* source) override;

    /** set the relative position of the play head*/
    void setPositionRelative(double pos);

  private:
    AudioThumbnail audioThumbnail;
    bool fileLoaded;
    double position;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(WaveformDisplay)
};
