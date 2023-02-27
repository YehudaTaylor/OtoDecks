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

    addAndMakeVisible(deck1);
    addAndMakeVisible(deck2);
    addAndMakeVisible(playlistComponent);

    // list of supported audio formats
    // for (int i = 0; i < formatManager.getNumKnownFormats(); i++)
    // {
    //     std::string s =
    //         formatManager.getKnownFormat(i)->getFormatName().toStdString();
    //     std::cout << i << " " << s << std::endl;
    // }

    formatManager.registerBasicFormats();
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
    mixerSource.addInputSource(&player1, false);
    mixerSource.addInputSource(&player2, false);
    // note that this will call prepareToPlay
    // automatically on the two players
    mixerSource.prepareToPlay(samplesPerBlockExpected, sampleRate);
    // so this is not needed:
    // player1.prepareToPlay(samplesPerBlockExpected, sampleRate);
    // player2.prepareToPlay(samplesPerBlockExpected, sampleRate);
}

void MainComponent::getNextAudioBlock(
    const AudioSourceChannelInfo& bufferToFill)
{
    mixerSource.getNextAudioBlock(bufferToFill);
}

void MainComponent::releaseResources()
{
    // This will be called when the audio device stops, or when it is being
    // restarted due to a setting change.

    // For more details, see the help for AudioProcessor::releaseResources()
    // transportSource.releaseResources();
    mixerSource.removeAllInputs();
    mixerSource.releaseResources();
    player1.releaseResources();
    player2.releaseResources();
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

    deck1.setBounds(0, 0, getWidth() / 2, getHeight() / 2);
    deck2.setBounds(getWidth() / 2, 0, getWidth() / 2, getHeight() / 2);
    playlistComponent.setBounds(0, getHeight()/2, getWidth(), getHeight()/2);
}
