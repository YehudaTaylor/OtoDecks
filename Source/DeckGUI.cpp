/*
  ==============================================================================

    DeckGUI.cpp
    Created: 15 Feb 2023 2:37:48pm
    Author:  yehuda

  ==============================================================================
*/

#include "DeckGUI.h"
#include "../JuceLibraryCode/JuceHeader.h"


//==============================================================================
DeckGUI::DeckGUI()
{
    addAndMakeVisible(playButton);
    addAndMakeVisible(stopButton);
    addAndMakeVisible(loadButton);
    addAndMakeVisible(volumeSlider);
    addAndMakeVisible(positionSlider);
    addAndMakeVisible(speedSlider);
}

DeckGUI::~DeckGUI()
{
}

void DeckGUI::paint(juce::Graphics& g)
{
    g.fillAll(
        getLookAndFeel().findColour(ResizableWindow::backgroundColourId));
}

void DeckGUI::resized()
{
    float rowH = getHeight() / 6;
    playButton.setBounds(0, 0, getWidth(), rowH);
    stopButton.setBounds(0, rowH, getWidth(), rowH);
    volumeSlider.setBounds(0, rowH * 2, getWidth(), rowH);
    positionSlider.setBounds(0, rowH * 3, getWidth(), rowH);
    speedSlider.setBounds(0, rowH * 4, getWidth(), rowH);
    loadButton.setBounds(0, rowH * 5, getWidth(), rowH);
