/*
  ==============================================================================

    LibraryComponent.cpp
    Created: 1 Mar 2023 10:18:09am
    Author:  yehuda

  ==============================================================================
*/

#include "LibraryComponent.h"
#include <JuceHeader.h>


//==============================================================================
LibraryComponent::LibraryComponent()
{
    addAndMakeVisible(loadButton);
    loadButton.addListener(this);
}

LibraryComponent::~LibraryComponent()
{
}

void LibraryComponent::paint(juce::Graphics& g)
{
    g.fillAll(getLookAndFeel().findColour(
        juce::ResizableWindow::backgroundColourId)); // clear the background

    g.setColour(juce::Colours::grey);
    g.drawRect(getLocalBounds(), 1); // draw an outline around the component
}

void LibraryComponent::resized()
{
    float rowH = getHeight();
    loadButton.setBounds(0, 0, getWidth(), rowH);
}

void LibraryComponent::buttonClicked(Button* button)
{
    if (button == &loadButton)
    {
        auto fileChooserFlags = FileBrowserComponent::canSelectFiles;
        fChooser.launchAsync(fileChooserFlags,
                             [this](const FileChooser& chooser) {
                                 auto chosenFile = chooser.getResult();
                                 // djAudioPlayer->loadURL(URL{chosenFile});
                                 // and now the waveformDisplay as well
                                 // waveformDisplay.loadURL(URL{chooser.getResult()});
                                 trackTitles.push_back(URL{chosenFile});
                                 sendChangeMessage();
                             });
      
      std::cout << "LibraryComponent::buttonClicked. Number of tracks loaded: " << trackTitles.size() << std::endl;
    }
}

bool LibraryComponent::isInterestedInFileDrag(const StringArray& files)
{
    std::cout << "LibraryComponent::isInterestedInFileDrag" << std::endl;
    return true;
}
void LibraryComponent::filesDropped(const StringArray& files, int x, int y)
{
    for (String filename : files)
    {
        std::cout << "LibraryComponent::filesDropped " << filename
                  << std::endl;
        URL fileURL = URL{File{filename}};
        // djAudioPlayer->loadURL(fileURL);

        // trackTitles.push_back(filename.toStdString());
        trackTitles.push_back(fileURL);

        std::cout << "LibraryComponent::filesDropped. Number of tracks loaded: " << trackTitles.size() << std::endl;
        std::cout << "LibraryComponent::filesDropped. Track URL as string: " << fileURL.toString(true) << std::endl;

        sendChangeMessage();

        return;
    }
}

std::vector<URL> LibraryComponent::getTrackURLs()
{
  return trackTitles;
}