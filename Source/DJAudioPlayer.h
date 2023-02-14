/*
  ==============================================================================

    DJAudioPlayer.h
    Created: 14 Feb 2023 1:39:12pm
    Author:  yehuda

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

class DJAudioPlayer
{
  public:
    DJAudioPlayer();
    ~DJAudioPlayer();
    void loadURL(URL file);
    void play();
    void stop();
    void setPosition(double posInSecs);
    void setGain(double gain);
};