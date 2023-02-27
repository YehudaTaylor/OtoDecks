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
DeckGUI::DeckGUI(DJAudioPlayer* _djAudioPlayer,
                 AudioFormatManager& formatManagerToUse,
                 AudioThumbnailCache& cacheToUse)
    : djAudioPlayer{_djAudioPlayer},
      waveformDisplay(formatManagerToUse, cacheToUse)
{
    addAndMakeVisible(playButton);
    addAndMakeVisible(stopButton);
    addAndMakeVisible(loadButton);
    addAndMakeVisible(volumeSlider);
    addAndMakeVisible(positionSlider);
    addAndMakeVisible(speedSlider);
    addAndMakeVisible(waveformDisplay);


    volumeSlider.setRange(0.0, 1.0);
    positionSlider.setRange(0.0, 1.0);
    speedSlider.setRange(0.0, 100.0);

    playButton.addListener(this);
    stopButton.addListener(this);
    volumeSlider.addListener(this);
    positionSlider.addListener(this);
    speedSlider.addListener(this);
    loadButton.addListener(this);
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
    float rowH = getHeight() / 8;
    playButton.setBounds(0, 0, getWidth(), rowH);
    stopButton.setBounds(0, rowH, getWidth(), rowH);
    volumeSlider.setBounds(0, rowH * 2, getWidth(), rowH);
    positionSlider.setBounds(0, rowH * 3, getWidth(), rowH);
    speedSlider.setBounds(0, rowH * 4, getWidth(), rowH);
    waveformDisplay.setBounds(0, rowH * 5, getWidth(), rowH * 2);
    loadButton.setBounds(0, rowH * 7, getWidth(), rowH);
}

void DeckGUI::buttonClicked(Button* button)
{
    if (button == &playButton)
    {
        djAudioPlayer->setPosition(0);
        djAudioPlayer->play();
    }
    if (button == &stopButton)
    {
        djAudioPlayer->stop();
    }
    if (button == &loadButton)
    {
        auto fileChooserFlags = FileBrowserComponent::canSelectFiles;
        fChooser.launchAsync(fileChooserFlags,
                             [this](const FileChooser& chooser) {
                                 auto chosenFile = chooser.getResult();
                                 djAudioPlayer->loadURL(URL{chosenFile});
                             });
    }
}
void DeckGUI::sliderValueChanged(Slider* slider)
{
    if (slider == &volumeSlider)
    {
        djAudioPlayer->setGain(slider->getValue());
    }
    if (slider == &positionSlider)
    {
        djAudioPlayer->setPositionRelative(slider->getValue());
    }
    if (slider == &speedSlider)
    {
        djAudioPlayer->setSpeed(slider->getValue());
    }
}

bool DeckGUI::isInterestedInFileDrag(const StringArray& files)
{
    std::cout << "DeckGUI::isInterestedInFileDrag" << std::endl;
    return true;
}
void DeckGUI::filesDropped(const StringArray& files, int x, int y)
{
    for (String filename : files)
    {
        std::cout << "DeckGUI::filesDropped " << filename << std::endl;
        URL fileURL = URL{File{filename}};
        djAudioPlayer->loadURL(fileURL);
        return;
    }
}