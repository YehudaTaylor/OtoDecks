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
    : audioThumbnail(1000, formatManagerToUse, cacheToUse), fileLoaded(false),
      position(0)
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.
    audioThumbnail.addChangeListener(this);
}

WaveformDisplay::~WaveformDisplay()
{
}

void WaveformDisplay::paint(juce::Graphics& g)
{
    g.fillAll(getLookAndFeel().findColour(
        juce::ResizableWindow::backgroundColourId));

    g.setColour(juce::Colours::black);
    g.drawRect(getLocalBounds(), 1);

    g.setColour(juce::Colours::green);
    if (fileLoaded)
    {
        g.setColour(Colours::lightgreen);
        audioThumbnail.drawChannel(g, getLocalBounds(), 0,
                                   audioThumbnail.getTotalLength(), 0, 1);
        g.drawRect(position * getWidth(), 0, getWidth() / 20, getHeight());
    }
    else
    {
        g.setFont(24.0f);
        g.drawText("File not loaded...", getLocalBounds(),
                   juce::Justification::centred,
                   true);
    }
}

void WaveformDisplay::resized()
{
}

void WaveformDisplay::loadURL(URL audioURL)
{
    audioThumbnail.clear();
    fileLoaded = audioThumbnail.setSource(new URLInputSource(audioURL));
}

void WaveformDisplay::changeListenerCallback(ChangeBroadcaster* source)
{
    std::cout << "wfd: change received! " << std::endl;
    repaint();
}

void WaveformDisplay::setPositionRelative(double pos)
{
    if (pos != position)
    {
        position = pos;
        repaint();
    }
}