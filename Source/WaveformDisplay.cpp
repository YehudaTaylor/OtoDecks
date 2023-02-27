/*
  ==============================================================================

    WaveformDisplay.cpp
    Created: 27 Feb 2023 10:40:21am
    Author:  yehuda

  ==============================================================================
*/

#include "WaveformDisplay.h"
#include "../JuceLibraryCode/JuceHeader.h"


//==============================================================================
WaveformDisplay::WaveformDisplay(AudioFormatManager& formatManagerToUse,
                                 AudioThumbnailCache& cacheToUse)
    : audioThumbnail(1000, formatManagerToUse, cacheToUse), fileLoaded(false)
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.
}

WaveformDisplay::~WaveformDisplay()
{
}

void WaveformDisplay::paint(juce::Graphics& g)
{
    /* This demo code just fills the component's background and
       draws some placeholder text to get you started.

       You should replace everything in this method with your own
       drawing code..
    */

    g.fillAll(getLookAndFeel().findColour(
        juce::ResizableWindow::backgroundColourId)); // clear the background

    g.setColour(juce::Colours::black);
    g.drawRect(getLocalBounds(), 1); // draw an outline around the component

    g.setColour(juce::Colours::green);
    g.setFont(24.0f);
    g.drawText("Waveform here!", getLocalBounds(),
               juce::Justification::centred,
               true); // draw some placeholder text
}

void WaveformDisplay::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..
}

void WaveformDisplay::loadURL(URL audioURL)
{
    audioThumbnail.clear();
    fileLoaded = audioThumbnail.setSource(new URLInputSource(audioURL));
}
