/*
  ==============================================================================

    LibraryComponent.cpp
    Created: 1 Mar 2023 10:18:09am
    Author:  yehuda

  ==============================================================================
*/

#include "LibraryComponent.h"
#include <JuceHeader.h>
#include <fstream>
#include <iostream>
#include <string>


//==============================================================================
LibraryComponent::LibraryComponent()
{
    addAndMakeVisible(loadButton);
    loadButton.addListener(this);

    loadLibraryFromDisk();
}

LibraryComponent::~LibraryComponent()
{
}

void LibraryComponent::paint(juce::Graphics& g)
{
    g.fillAll(getLookAndFeel().findColour(
        juce::ResizableWindow::backgroundColourId));

    g.setColour(juce::Colours::grey);
    g.drawRect(getLocalBounds(), 1);
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
                                 addTrackURL(URL{chosenFile});
                                 sendChangeMessage();
                                 saveLibraryToDisk(getTrackURLs());
                             });
        std::cout
            << "LibraryComponent::buttonClicked. Number of tracks loaded: "
            << trackTitles.size() << std::endl;
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
        addTrackURL(fileURL);
        sendChangeMessage();
        saveLibraryToDisk(getTrackURLs());

        return;
    }
}

std::vector<URL> LibraryComponent::getTrackURLs()
{
    return trackTitles;
}

void LibraryComponent::setTrackURLS(std::vector<URL> _trackTitles)
{
    trackTitles = _trackTitles;
}

void LibraryComponent::addTrackURL(URL trackURL)
{
    trackTitles.push_back(trackURL);
}

void LibraryComponent::saveLibraryToDisk(std::vector<URL> _trackTitles)
{
    std::ofstream MusicLibrary;
    MusicLibrary.open("Library.csv");

    if (MusicLibrary.is_open())
    {
        for (URL track : _trackTitles)
        {
            MusicLibrary << track.toString(false) + "\n";
        }

        MusicLibrary.close();
        std::cout << "LibraryComponent::saveLibraryToDisk: saved library and "
                     "closed file"
                  << std::endl;
    }
    else
    {
        std::cout << "LibraryComponent::saveLibraryToDisk. FAILED to open file"
                  << std::endl;
    }
}
void LibraryComponent::loadLibraryFromDisk()
{
    std::ifstream MusicLibrary;
    MusicLibrary.open("Library.csv", std::ios::out | std::ios::in);

    if (MusicLibrary.is_open())
    {
        std::vector<URL> titlesFromDisk;
        std::string line;
        while (getline(MusicLibrary, line))
        {
            titlesFromDisk.push_back(URL{line});
        }

        setTrackURLS(titlesFromDisk);

        MusicLibrary.close();
        std::cout << "LibraryComponent::loadLibraryFromDisk: loaded library "
                     "and closed file"
                  << std::endl;
    }
    else
    {
        std::cout
            << "LibraryComponent::loadLibraryFromDisk. FAILED to open file"
            << std::endl;
    }
}