/*
  ==============================================================================

    DJAudioPlayer.cpp
    Created: 14 Feb 2023 1:39:12pm
    Author:  yehuda

  ==============================================================================
*/

#include "DJAudioPlayer.h"

DJAudioPlayer::DJAudioPlayer()
{
    formatManager.registerBasicFormats();
}
DJAudioPlayer::~DJAudioPlayer()
{
}

void DJAudioPlayer::prepareToPlay(int samplesPerBlockExpected,
                                  double sampleRate)
{
    transportSource.prepareToPlay(samplesPerBlockExpected, sampleRate);
}
void DJAudioPlayer::getNextAudioBlock(
    const AudioSourceChannelInfo& bufferToFill)
{
    if (readerSource.get() == nullptr)
    {
        bufferToFill.clearActiveBufferRegion();
        return;
    }
    transportSource.getNextAudioBlock(bufferToFill);
}
void DJAudioPlayer::releaseResources()
{
    transportSource.releaseResources();
}

void DJAudioPlayer::loadURL(URL audioURL)
{
    auto* reader =
        formatManager.createReaderFor(audioURL.createInputStream(false));
    if (reader != nullptr) // good file!
    {
        std::unique_ptr<AudioFormatReaderSource> newSource(
            new AudioFormatReaderSource(reader, true));
        transportSource.setSource(newSource.get(), 0, nullptr,
                                  reader->sampleRate);
        readerSource.reset(newSource.release());

        std::cout << "DJAudioPlayer::loadURL: file loaded" << std::endl;
    }
}
void DJAudioPlayer::play()
{
    transportSource.setPosition(0);
    transportSource.start();
}
void DJAudioPlayer::stop()
{
    transportSource.stop();
}
void DJAudioPlayer::setPosition(double posInSecs)
{
    if (posInSecs < 0 || posInSecs > transportSource.getLengthInSeconds())
    {
        std::cout << "DJAudioPlayer::setPosition: warning set position "
                  << posInSecs << " greater than length "
                  << transportSource.getLengthInSeconds() << std::endl;
        return;
    }
    transportSource.setPosition(posInSecs);
}
void DJAudioPlayer::setGain(double gain)
{
    transportSource.setGain(gain);
}