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
    }
}
void DJAudioPlayer::play()
{
}
void DJAudioPlayer::stop()
{
}
void DJAudioPlayer::setPosition(double posInSecs)
{
}
void DJAudioPlayer::setGain(double gain)
{
}