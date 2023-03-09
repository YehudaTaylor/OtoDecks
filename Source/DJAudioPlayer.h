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

    /** called before playback starts, to let the processor prepare itself*/
    void prepareToPlay(int samplesPerBlockExpected,
                       double sampleRate) override;

    /** called repeatedly to fetch subsequent blocks of audio data*/
    void getNextAudioBlock(
        const AudioSourceChannelInfo& bufferToFill) override;
        
    /** called after playback has stopped, to let the object free up any
     * resources it no longer needs*/
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

    /** set the speed of the song multiplied by the ratio that is passed in*/
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