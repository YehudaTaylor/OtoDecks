/*
  ==============================================================================

    PlaylistComponent.h
    Created: 27 Feb 2023 3:48:17pm
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
class PlaylistComponent : public juce::Component, public TableListBoxModel, public Button::Listener
{
  public:
    PlaylistComponent();
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

  private:
    TableListBox tableComponent;
    std::vector<std::string> trackTitles;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PlaylistComponent)
};
