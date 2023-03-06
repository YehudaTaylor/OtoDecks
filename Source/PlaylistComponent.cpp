/*
  ==============================================================================

    PlaylistComponent.cpp
    Created: 27 Feb 2023 3:48:17pm
    Author:  yehuda

  ==============================================================================
*/

#include "PlaylistComponent.h"
#include <JuceHeader.h>


//==============================================================================
PlaylistComponent::PlaylistComponent(AudioFormatManager& _formatManager) : formatManager(_formatManager)
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.
    addAndMakeVisible(tableComponent);
    addAndMakeVisible(libraryComponent);
    addAndMakeVisible(textEditor);

    libraryComponent.addChangeListener(this);
    textEditor.addListener(this);

    trackURLs = libraryComponent.getTrackURLs();

    tableComponent.getHeader().addColumn("Track title", 1, 300);
    tableComponent.getHeader().addColumn("Action", 2, 100);
    tableComponent.getHeader().addColumn("File type", 3, 100);
    tableComponent.getHeader().addColumn("Track length", 4, 100);

    tableComponent.setModel(this);
}

PlaylistComponent::~PlaylistComponent()
{
}

void PlaylistComponent::paint(juce::Graphics& g)
{
    g.fillAll(getLookAndFeel().findColour(
        juce::ResizableWindow::backgroundColourId)); // clear the background

    g.setColour(juce::Colours::grey);
    g.drawRect(getLocalBounds(), 1); // draw an outline around the component
}

void PlaylistComponent::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..
    float rowH = getHeight() / 3;
    tableComponent.setBounds(0, 0, getWidth(), rowH);
    libraryComponent.setBounds(0, rowH, getWidth(), rowH);
    textEditor.setBounds(0, rowH * 2, getWidth(), rowH);
}

int PlaylistComponent::getNumRows()
{
    return trackURLs.size();
}
void PlaylistComponent::paintRowBackground(Graphics& g, int rowNumber,
                                           int width, int height,
                                           bool rowIsSelected)
{
    // just highlight selected rows
    if (rowIsSelected)
    {
        g.fillAll(Colours::orange);
    }
    else
    {
        g.fillAll(Colours::darkgrey);
    }
}

void PlaylistComponent::paintCell(Graphics& g, int rowNumber, int columnId,
                                  int width, int height, bool rowIsSelected)
{
    String text = getCellMetaData(rowNumber, columnId);

    g.drawText(text, // the important bit
               2, 0, width - 4, height, Justification::centredLeft, true);
}

void PlaylistComponent::cellClicked(int rowNumber, int columnId,
                                    const MouseEvent&)
{
    std::cout << "Row number: " << rowNumber << " coloumn id: " << columnId
              << std::endl;
}

Component* PlaylistComponent::refreshComponentForCell(
    int rowNumber, int columnId, bool isRowSelected,
    Component* existingComponentToUpdate)
{
    if (columnId == 2)
    {
        if (existingComponentToUpdate == nullptr)
        {
            TextButton* btn = new TextButton("Load to deck");
            String id{std::to_string(rowNumber)};
            btn->setComponentID(id);
            btn->addListener(this);
            existingComponentToUpdate = btn;
        }
    }
    return existingComponentToUpdate;
}

void PlaylistComponent::buttonClicked(Button* button)
{
    int id = std::stoi(button->getComponentID().toStdString());
    DBG("PlaylistComponent::buttonClicked " << trackURLs[id].getFileName());
    sendActionMessage(trackURLs[id].toString(false));
}

// void PlaylistComponent::tableColumnsChanged (TableHeaderComponent *)
// {

// }

void PlaylistComponent::changeListenerCallback(ChangeBroadcaster* source)
{
    std::cout << "PlaylistComponent::changeListenerCallback: change received! "
              << std::endl;

    trackURLs = libraryComponent.getTrackURLs();
    std::cout
        << "PlaylistComponent::changeListenerCallback. Number of tracks: "
        << trackURLs.size() << std::endl;
    tableComponent.updateContent();

    // getTrackMetaData();
}


void PlaylistComponent::textEditorTextChanged(TextEditor&)
{
    std::cout << "PlaylistComponent::textEditorTextChanged, current text: "
              << textEditor.getText() << std::endl;

    trackURLs = libraryComponent.getTrackURLs();
    std::vector<URL> matchingURLs;

    for (URL fileURL : trackURLs)
    {
        if (fileURL.toString(false).toStdString().find(
                textEditor.getText().toStdString()) != std::string::npos)
        {
            matchingURLs.push_back(fileURL);
            std::cout << "PlaylistComponent::textEditorTextChanged match found"
                      << std::endl;
            std::cout << "PlC::teChanged filename: " << fileURL.getFileName()
                      << std::endl;
        }
    }

    trackURLs = matchingURLs;
    tableComponent.updateContent();
}
void PlaylistComponent::textEditorReturnKeyPressed(TextEditor&)
{
    std::cout << "PlaylistComponent::textEditorReturnKeyPressed" << std::endl;
}

// void PlaylistComponent::getTrackMetaData()
// {
//     for (URL fileURL : trackURLs)
//     {
//         juce::File audioFile{fileURL.toString(false)};

//         std::cout << "PlaylistComponent::getTrackMetaData file extension: "
//                   << audioFile.getFileExtension() << std::endl;
//         audioFile.getSize();
//         audioFile.getFileName();
//     }
// }

String PlaylistComponent::getCellMetaData(int rowNumber, int columnId)
{
    juce::File audioFile{trackURLs[rowNumber].toString(false)};

    String text = "Default text";
    
    if (columnId == 1)
    {
        text = audioFile.getFileNameWithoutExtension();
    }
    if (columnId == 3)
    {
        text = audioFile.getFileExtension();
    }
    if (columnId == 4)
    {
        ScopedPointer<AudioFormatReader> reader =
        // auto* reader =
            formatManager.createReaderFor(
                trackURLs[rowNumber].createInputStream(false));
        if (reader != nullptr)
        {
            double seconds = reader->lengthInSamples/ reader->sampleRate;
            RelativeTime relativeTime{seconds};
            String trackLength = relativeTime.getDescription();
            text = trackLength;
            std::cout
                << "PlaylistComponent::getCellMetaData track length: "
                << trackLength << std::endl;
        }
    }

    return text;
}