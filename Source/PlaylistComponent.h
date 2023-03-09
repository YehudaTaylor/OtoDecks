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

    /** component overrides this, for drawing it's content*/
    void paint(juce::Graphics&) override;

    /** component overrides this, to place child components in the correct
     * place when the width or height changes*/
    void resized() override;

    /**this returns the number of items in the list, to be used in the table
     * (which is the number of tracks in the library)*/
    int getNumRows() override;

    /** draws the background for each of the rows in the table*/
    void paintRowBackground(Graphics&, int rowNumber, int width, int height,
                            bool rowIsSelected) override;

    /** draws an individual cell in the table*/
    void paintCell(Graphics&, int rowNumber, int columnId, int width,
                   int height, bool rowIsSelected) override;

    /** callback for when a cell is clicked*/
    void cellClicked(int rowNumber, int columnId, const MouseEvent&) override;

    /**this is used to create or update a custom component to go in a cell.
     * here it is used to create the 'load to deck' buttons, each with a
     * specific ID, which is then used to load the specified track onto the
     * deck*/
    Component* refreshComponentForCell(
        int rowNumber, int columnId, bool isRowSelected,
        Component* existingComponentToUpdate) override;

    /** receives callbacks when buttons in the component are clicked. this is
     * used by the load to deck button, to load the given song onto the deck*/
    void buttonClicked(Button* button) override;

    /** listens for the change broadcast that the LibraryComponent broadcasts
     * when a new song is added to the library. this is used to update the
     * library list in playlist, as well as update the table component to show
     * the new track*/
    void changeListenerCallback(ChangeBroadcaster* source) override;

    /** called when the text in the text editor is changed in some way. when
     * the text editor changes, it's text input is collected and is used to
     * search through the list of tracks, in order to find tracks that match
     * the users search input.*/
    void textEditorTextChanged(TextEditor&) override;

    /** todo check if this is used at all. remove if it isn't*/
    void textEditorReturnKeyPressed(TextEditor&) override;

    /** returns the track meta-data for each cell as a String. this is called
     * by the paintCell function. it returns the respective data for each cell
     * based on it's rowNumber and columnId.
     * The meta-data includes the track's name, file type and duration */
    String getCellMetaData(int rowNumber, int columnId);

    /** update the list of songs in the playlist's library. this is called when
     * the playlist is first loaded as well as when any other changes occur,
     * such as when a new track is added. it is also called when the user is
     * searching for a song, the table is updated to only show songs which are
     * relavent to the users search input*/
    /** todo: this should be named better, such as something to do with
     * updatePlaylistTableDataSource*/
    void updateLibraryList(std::vector<URL> _trackURLs);

  private:
    AudioFormatManager& formatManager;

    LibraryComponent libraryComponent;

    TableListBox tableComponent;

    std::vector<URL> trackURLs;

    TextEditor textEditor{"Search for a track"};

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PlaylistComponent)
};
