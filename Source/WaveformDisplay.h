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

    /** component overrides this, for drawing it's content*/
    void paint(juce::Graphics&) override;

    /** component overrides this, to place child components in the correct
     * place when the width or height changes*/
    void resized() override;

    /** generate the waveform for the file with the given URL*/
    void loadURL(URL audioURL);

    /** callback that updates the waveform display by repainting it*/
    void changeListenerCallback(ChangeBroadcaster* source) override;

    /** set the relative position of the play head*/
    void setPositionRelative(double pos);

  private:
    AudioThumbnail audioThumbnail;

    bool fileLoaded;

    double position;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(WaveformDisplay)
};
