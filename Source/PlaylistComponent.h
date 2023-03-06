/*
  ==============================================================================

    PlaylistComponent.h
    Created: 27 Feb 2023 3:48:17pm
    Author:  yehuda

  ==============================================================================
*/

#pragma once

#include "LibraryComponent.h"
#include <JuceHeader.h>
#include <string>
#include <vector>


//==============================================================================
/*
 */
class PlaylistComponent : public juce::Component,
                          public TableListBoxModel,
                          public Button::Listener,
                          public ChangeListener,
                          public TextEditor::Listener,
                          public ActionBroadcaster
{
  public:
    PlaylistComponent(AudioFormatManager& formatManager);
    ~PlaylistComponent() override;

    void paint(juce::Graphics&) override;
    void resized() override;

    int getNumRows() override;
    void paintRowBackground(Graphics&, int rowNumber, int width, int height,
                            bool rowIsSelected) override;
    void paintCell(Graphics&, int rowNumber, int columnId, int width,
                   int height, bool rowIsSelected) override;

    void cellClicked(int rowNumber, int columnId, const MouseEvent&) override;

    Component* refreshComponentForCell(
        int rowNumber, int columnId, bool isRowSelected,
        Component* existingComponentToUpdate) override;

    void buttonClicked(Button* button) override;

    // void tableColumnsChanged(TableHeaderComponent*) override;
    void changeListenerCallback(ChangeBroadcaster* source) override;

    void textEditorTextChanged(TextEditor &) override;
    void textEditorReturnKeyPressed(TextEditor &) override;

    // void getTrackMetaData();

    String getCellMetaData(int rowNumber, int columnId);

  private:
    AudioFormatManager& formatManager;
    LibraryComponent libraryComponent;
    TableListBox tableComponent;
    std::vector<URL> trackURLs;

    TextEditor textEditor{"Search for a track"};

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PlaylistComponent)
};
