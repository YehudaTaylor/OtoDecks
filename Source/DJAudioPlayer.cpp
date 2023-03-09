/*
  ==============================================================================

    DJAudioPlayer.cpp
    Created: 14 Feb 2023 1:39:12pm
    Author:  yehuda

  ==============================================================================
*/

#include "DJAudioPlayer.h"

DJAudioPlayer::DJAudioPlayer(AudioFormatManager& _formatManager)
    : formatManager(_formatManager)
{
}

DJAudioPlayer::~DJAudioPlayer()
{
}

void DJAudioPlayer::prepareToPlay(int samplesPerBlockExpected,
                                  double sampleRate)
{
    transportSource.prepareToPlay(samplesPerBlockExpected, sampleRate);
    resampleSource.prepareToPlay(samplesPerBlockExpected, sampleRate);
}

void DJAudioPlayer::getNextAudioBlock(
    const AudioSourceChannelInfo& bufferToFill)
{
    resampleSource.getNextAudioBlock(bufferToFill);
}

void DJAudioPlayer::releaseResources()
{
    transportSource.releaseResources();
    resampleSource.releaseResources();
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

void DJAudioPlayer::setSpeed(double ratio)
{
    if (ratio < 0 || ratio > 10.0)
    {
        std::cout << "DJAudioPlayer::setSpeed ratio should be between 0 and 10"
                  << std::endl;
    }
    else
    {
        resampleSource.setResamplingRatio(ratio);
    }
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

void DJAudioPlayer::setPositionRelative(double pos)
{
    if (pos < 0 || pos > 1.0)
    {
        std::cout << "DJAudioPlayer::setPositionRelative pos should be "
                     "between 0 and 1"
                  << std::endl;
    }
    else
    {
        double posInSecs = transportSource.getLengthInSeconds() * pos;
        setPosition(posInSecs);
    }
}

void DJAudioPlayer::setGain(double gain)
{
    if (gain < 0 || gain > 1.0)
    {
        std::cout << "DJAudioPlayer::setGain gain should be between 0 and 1"
                  << std::endl;
    }
    else
    {
        transportSource.setGain(gain);
    }
}

double DJAudioPlayer::getPositionRelative()
{
    return transportSource.getCurrentPosition() /
           transportSource.getLengthInSeconds();
}

void DJAudioPlayer::skipForward(double amount)
{
    if (amount < 0 || amount > transportSource.getLengthInSeconds())
    {
        std::cout << "DJAudioPlayer::skipForward: warning set position "
                  << amount << " greater than length "
                  << transportSource.getLengthInSeconds() << std::endl;
        return;
    }
    double currentPos = transportSource.getCurrentPosition();
    double newPos = currentPos + amount;
    transportSource.setPosition(newPos);
}

void DJAudioPlayer::skipBackward(double amount)
{
    if (amount < 0 || amount > transportSource.getLengthInSeconds())
    {
        std::cout << "DJAudioPlayer::skipForward: warning set position "
                  << amount << " greater than length "
                  << transportSource.getLengthInSeconds() << std::endl;
        return;
    }
    double currentPos = transportSource.getCurrentPosition();
    double newPos = currentPos - amount;
    transportSource.setPosition(newPos);
}