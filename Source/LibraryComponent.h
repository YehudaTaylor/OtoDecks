/*
  ==============================================================================

    LibraryComponent.h
    Created: 1 Mar 2023 10:18:09am
    Author:  yehuda

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include <string>
#include <vector>


//==============================================================================
/*
 */
class LibraryComponent : public juce::Component,
                         public Button::Listener,
                         public FileDragAndDropTarget,
                         public ChangeBroadcaster
{
  public:
    LibraryComponent();
    ~LibraryComponent() override;

    void paint(juce::Graphics&) override;
    void resized() override;

    void buttonClicked(Button* button) override;

    bool isInterestedInFileDrag(const StringArray& files) override;
    void filesDropped(const StringArray& files, int x, int y) override;
    /** get the URLs of tracks in the library*/
    std::vector<URL> getTrackURLs();
    /** set the list of track URLs*/
    void setTrackURLS(std::vector<URL> _trackTitles);
    /** add a track URL to the list of tracks in the library*/
    void addTrackURL(URL trackURL);

    /** save the library of tracks, to disk*/
    void saveLibraryToDisk(std::vector<URL> _trackTitles);
    /** load all the library tracks from disk storage*/
    void loadLibraryFromDisk();


  private:
    std::vector<URL> trackTitles;
    TextButton loadButton{"LOAD"};
    TextButton saveButton{"Save library to disk"};
    FileChooser fChooser{"Select a file..."};

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(LibraryComponent)
};
