/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#include "MainComponent.h"

//==============================================================================
MainComponent::MainComponent()
{
    // Make sure you set the size of the component after
    // you add any child components.
    setSize(800, 600);

    // Some platforms require permissions to open input channels so request
    // that here
    if (RuntimePermissions::isRequired(RuntimePermissions::recordAudio) &&
        !RuntimePermissions::isGranted(RuntimePermissions::recordAudio))
    {
        RuntimePermissions::request(RuntimePermissions::recordAudio,
                                    [&](bool granted) {
                                        if (granted)
                                            setAudioChannels(2, 2);
                                    });
    }
    else
    {
        // Specify the number of input and output channels that we want to open
        setAudioChannels(0, 2);
    }

    addAndMakeVisible(playButton);
    addAndMakeVisible(stopButton);
    addAndMakeVisible(volSlider);
    addAndMakeVisible(gainSlider);

    playButton.addListener(this);
    stopButton.addListener(this);
    gainSlider.addListener(this);
    gainSlider.setRange(0, 1);

    playButton.setButtonText("PLAY BUTTON");
    stopButton.setButtonText("STOP BUTTON");
}

MainComponent::~MainComponent()
{
    // This shuts down the audio device and clears the audio source.
    shutdownAudio();
}

//==============================================================================
void MainComponent::prepareToPlay(int samplesPerBlockExpected,
                                  double sampleRate)
{
    playing = false;
    gain = 0.5;
    phase = 0;
}

void MainComponent::getNextAudioBlock(
    const AudioSourceChannelInfo& bufferToFill)
{
    if (!playing)
    {
        bufferToFill.clearActiveBufferRegion();
        return;
    }

    auto* leftChannel =
        bufferToFill.buffer->getWritePointer(0, bufferToFill.startSample);
    auto* rightChannel =
        bufferToFill.buffer->getWritePointer(1, bufferToFill.startSample);
    for (auto i = 0; i < bufferToFill.numSamples; ++i)
    {
        auto sample = fmod(phase, 1.0f);
        phase += 0.005;
        leftChannel[i] = sample * 0.125 * gain;
        rightChannel[i] = sample * 0.125 * gain;
    }
}

void MainComponent::releaseResources()
{
    // This will be called when the audio device stops, or when it is being
    // restarted due to a setting change.

    // For more details, see the help for AudioProcessor::releaseResources()
}

//==============================================================================
void MainComponent::paint(Graphics& g)
{
    // std::cout << "MainComponent::paint was called " << std::endl;

    // (Our component is opaque, so we must completely fill the background with
    // a solid colour) g.fillAll (getLookAndFeel().findColour
    // (ResizableWindow::backgroundColourId));

    g.fillAll(Colour{255, 0, 0});

    // You can add your drawing code here!
}

void MainComponent::resized()
{
    // This is called when the MainContentComponent is resized.
    // If you add any child components, this is where you should
    // update their positions.
    double rowH = getHeight() / 5;
    playButton.setBounds(0, 0, getWidth(), rowH);
    stopButton.setBounds(0, rowH, getWidth(), rowH);
    gainSlider.setBounds(0, rowH * 4, getWidth(), rowH);
    volSlider.setBounds(0, rowH * 3, getWidth(), rowH);
}

void MainComponent::buttonClicked(Button* button)
{
    if (button == &playButton)
    {
        playing = true;
    }
    if (button == &stopButton)
    {
        playing = false;
    }
}

void MainComponent::sliderValueChanged(Slider* slider)
{
    if (slider == &gainSlider)
    {
        DBG("MainComponent::sliderValueChanged: gainSlider "
            << gainSlider.getValue());
        gain = gainSlider.getValue();
    }
}