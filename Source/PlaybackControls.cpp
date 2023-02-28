/*
  ==============================================================================

    PlaybackControls.cpp
    Created: 28 Feb 2023 3:25:38pm
    Author:  yehuda

  ==============================================================================
*/

#include "PlaybackControls.h"
#include <JuceHeader.h>


//==============================================================================
PlaybackControls::PlaybackControls(DJAudioPlayer* _djAudioPlayer)
    : djAudioPlayer{_djAudioPlayer}
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.
    addAndMakeVisible(skipSlider);
    addAndMakeVisible(skipForwardButton);
    addAndMakeVisible(skipBackwardButton);

    skipSlider.setRange(0.1, 10.0);

    skipSlider.addListener(this);
    skipForwardButton.addListener(this);
    skipBackwardButton.addListener(this);

    skipSlider.setSliderStyle(Slider::IncDecButtons);
    skipSlider.setTextBoxStyle(Slider::TextBoxLeft, false, 50, 20);
    skipSlider.setIncDecButtonsMode(Slider::incDecButtonsDraggable_Vertical);
}

PlaybackControls::~PlaybackControls()
{
}

void PlaybackControls::paint(juce::Graphics& g)
{
    g.fillAll(juce::Colours::green); // clear the background

    g.setColour(juce::Colours::blue);
    g.drawRect(getLocalBounds(), 2); // draw an outline around the component
}

void PlaybackControls::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..
    float rowH = getHeight();
    skipSlider.setBounds(getWidth() / 3, 0, getWidth() / 3, rowH);
    skipForwardButton.setBounds((getWidth() / 3) * 2, 0, getWidth() / 3, rowH);
    skipBackwardButton.setBounds(0, 0, getWidth() / 3, rowH);
}

void PlaybackControls::buttonClicked(Button* button)
{
    if (button == &skipForwardButton)
    {
        djAudioPlayer->skipForward(skipSlider.getValue());
    }
    if (button == &skipBackwardButton)
    {
        djAudioPlayer->skipBackward(skipSlider.getValue());
    }
}
void PlaybackControls::sliderValueChanged(Slider* slider)
{
    if (slider == &skipSlider)
    {
        std::cout
            << "PlaybackControls::sliderValueChanged, skip slider value: "
            << slider->getValue() << std::endl;
    }
}