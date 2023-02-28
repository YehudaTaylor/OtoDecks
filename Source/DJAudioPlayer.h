/*
  ==============================================================================

    DJAudioPlayer.h
    Created: 14 Feb 2023 1:39:12pm
    Author:  yehuda

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

class DJAudioPlayer : public AudioSource
{
  public:
    DJAudioPlayer(AudioFormatManager& formatManager);
    ~DJAudioPlayer();

    void prepareToPlay(int samplesPerBlockExpected,
                       double sampleRate) override;
    void getNextAudioBlock(
        const AudioSourceChannelInfo& bufferToFill) override;
    void releaseResources() override;


    /** load a ULR (a file in this case) from the file system*/
    void loadURL(URL file);
    /** start playing the file*/
    void play();
    /** stop playing the file*/
    void stop();
    /** set the currently playing position in the sound file*/
    void setPosition(double posInSecs);
    /** set the gain of the current song*/
    void setGain(double gain);
    void setSpeed(double ratio);
    /** set position in song relative to the position in the slider*/
    void setPositionRelative(double pos);

    /** get the relative position of the play head */
    double getPositionRelative();
    /** skip forward in the track by amount of seconds*/
    void skipForward(double amount);
    /** skip backward in the track by amount of seconds*/
    void skipBackward(double amount);

  private:
    AudioFormatManager& formatManager;
    std::unique_ptr<AudioFormatReaderSource> readerSource;
    AudioTransportSource transportSource;
    ResamplingAudioSource resampleSource{&transportSource, false, 2};
};