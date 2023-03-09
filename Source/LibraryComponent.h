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

    /** component overrides this, for drawing it's content*/
    void paint(juce::Graphics&) override;

    /** component overrides this, to place child components in the correct
     * place when the width or height changes*/
    void resized() override;

    /** receives callbacks when buttons in the component are clicked. this is
     * used by the load button to load a track*/
    void buttonClicked(Button* button) override;

    /** Callback to check whether this target is interested in the set of files
     * being offered*/
    bool isInterestedInFileDrag(const StringArray& files) override;

    /** callback that is called when a file is dropped onto the component. the
     * URL for the file is passed in through the StringArray& files, which is
     * then used to add the track to the library*/
    void filesDropped(const StringArray& files, int x, int y) override;

    /** get the vector of all the track URLs in the library*/
    std::vector<URL> getTrackURLs();

    /** set the library's list of track URLs*/
    void setTrackURLS(std::vector<URL> _trackTitles);

    /** add a track's URL to the list of tracks in the library*/
    void addTrackURL(URL trackURL);

    /** save the library of tracks to persistent storage on disk*/
    void saveLibraryToDisk(std::vector<URL> _trackTitles);

    /** load all the library tracks from persistent storage on the disk*/
    void loadLibraryFromDisk();

  private:
    std::vector<URL> trackTitles;
    
    TextButton loadButton{"CLICK TO LOAD | OR DRAG AND DROP HERE"};
    
    FileChooser fChooser{"Select a file..."};

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(LibraryComponent)
};
