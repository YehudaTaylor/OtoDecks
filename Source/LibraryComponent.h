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

    std::vector<URL> getTrackURLs();


  private:
    std::vector<URL> trackTitles;
    TextButton loadButton{"LOAD"};
    FileChooser fChooser{"Select a file..."};

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(LibraryComponent)
};
