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
                 AudioThumbnailCache& cacheToUse,
                 PlaylistComponent* _playlistComponent)
    : djAudioPlayer{_djAudioPlayer},
      waveformDisplay(formatManagerToUse, cacheToUse),
      playlistComponent(_playlistComponent)
{
    addAndMakeVisible(playButton);
    addAndMakeVisible(stopButton);
    addAndMakeVisible(loadButton);
    addAndMakeVisible(volumeSlider);
    addAndMakeVisible(positionSlider);
    addAndMakeVisible(speedSlider);
    addAndMakeVisible(waveformDisplay);
    addAndMakeVisible(playbackControls);
    addAndMakeVisible(volumeLabel);
    addAndMakeVisible(positionLabel);
    addAndMakeVisible(speedLabel);

    volumeSlider.setRange(0.0, 1.0);
    positionSlider.setRange(0.0, 1.0);
    speedSlider.setRange(0.1, 10.0);

    volumeSlider.setTextValueSuffix("%");
    positionSlider.setTextValueSuffix("%");
    speedSlider.setTextValueSuffix("%");

    volumeLabel.setText("Volume", juce::dontSendNotification);
    positionLabel.setText("Postion", juce::dontSendNotification);
    speedLabel.setText("Speed", juce::dontSendNotification);

    volumeLabel.attachToComponent(&volumeSlider, true);
    positionLabel.attachToComponent(&positionSlider, true);
    speedLabel.attachToComponent(&speedSlider, true);

    playButton.addListener(this);
    stopButton.addListener(this);
    volumeSlider.addListener(this);
    positionSlider.addListener(this);
    speedSlider.addListener(this);
    loadButton.addListener(this);

    playlistComponent->addActionListener(this);

    startTimer(200);
}

DeckGUI::~DeckGUI()
{
    stopTimer();
}

void DeckGUI::paint(juce::Graphics& g)
{
    g.fillAll(
        getLookAndFeel().findColour(ResizableWindow::backgroundColourId));
}

void DeckGUI::resized()
{
    auto padding = 1;
    auto sliderLeft = 60;
    float rowH = getHeight() / 10;
    playButton.setBounds(0, 0, getWidth(), rowH * 2);
    stopButton.setBounds(0, rowH * 2, getWidth(), rowH);
    volumeSlider.setBounds(sliderLeft + padding, rowH * 3,
                           getWidth() - sliderLeft - padding, rowH);
    positionSlider.setBounds(sliderLeft + padding, rowH * 4,
                             getWidth() - sliderLeft - padding, rowH);
    speedSlider.setBounds(sliderLeft + padding, rowH * 5,
                          getWidth() - sliderLeft - padding, rowH);
    waveformDisplay.setBounds(0, rowH * 6, getWidth(), rowH * 2);
    playbackControls.setBounds(0, rowH * 8, getWidth(), rowH);
    loadButton.setBounds(0, rowH * 9, getWidth(), rowH);
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
        fChooser.launchAsync(
            fileChooserFlags, [this](const FileChooser& chooser) {
                auto chosenFile = chooser.getResult();
                djAudioPlayer->loadURL(URL{chosenFile});
                waveformDisplay.loadURL(URL{chooser.getResult()});
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
        waveformDisplay.loadURL(fileURL);
        return;
    }
}

void DeckGUI::timerCallback()
{
    waveformDisplay.setPositionRelative(djAudioPlayer->getPositionRelative());
}

void DeckGUI::actionListenerCallback(const String& message)
{
    std::cout << "DeckGUI::actionListenerCallback, message: " << message
              << std::endl;
    URL fileURL = URL{message};
    djAudioPlayer->loadURL(fileURL);
    waveformDisplay.loadURL(fileURL);
    return;
}