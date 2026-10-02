/*
==============================================================================

DJAudioPlayer.cpp
Created: 13 Mar 2020 4:22:22pm
Author:  matthew

==============================================================================
*/

#include "DJAudioPlayer.h"
#include <iostream>

DJAudioPlayer::DJAudioPlayer(juce::AudioFormatManager& _formatManager)
: formatManager(_formatManager), resampleSource(&transportSource, false, 2) {
}

DJAudioPlayer::~DJAudioPlayer() {
}

void DJAudioPlayer::prepareToPlay(int samplesPerBlockExpected, double sampleRate) {
    transportSource.prepareToPlay(samplesPerBlockExpected, sampleRate);
    resampleSource.prepareToPlay(samplesPerBlockExpected, sampleRate);
}

void DJAudioPlayer::releaseResources() {
    transportSource.releaseResources();
    resampleSource.releaseResources();
}

//>>>>>>>>>>>>>>>>>>>>>>>>MY CODE<<<<<<<<<<<<<<<<<<<<<<<<<<
void DJAudioPlayer::loadURL(juce::URL audioURL) {
    //creates audio reader from URL
    auto* reader = formatManager.createReaderFor(audioURL.createInputStream(false));
    if (reader != nullptr) {
        //setting up audio source from reader
        auto newSource = std::make_unique<juce::AudioFormatReaderSource>(reader, true);
        transportSource.setSource(newSource.get(), 0, nullptr, reader->sampleRate);
        //stores the source
        readerSource.reset(newSource.release());
    }
}
//>>>>>>>>>>>>>>>>>>>>>>>>MY CODE<<<<<<<<<<<<<<<<<<<<<<<<<<

void DJAudioPlayer::setGain(double gain) {
    if (gain >= 0.0 && gain <= 1.0) {
        transportSource.setGain(gain);
    }
}

void DJAudioPlayer::setSpeed(double ratio) {
    if (ratio >= 0.0 && ratio <= 100.0) {
        resampleSource.setResamplingRatio(ratio);
    }
}

void DJAudioPlayer::setPosition(double posInSecs) {
    transportSource.setPosition(posInSecs);
}

void DJAudioPlayer::setPositionRelative(double pos) {
    if (pos >= 0.0 && pos <= 1.0) {
        double posInSecs = transportSource.getLengthInSeconds() * pos;
        setPosition(posInSecs);
    }
}

void DJAudioPlayer::start() {
    transportSource.start();
}

void DJAudioPlayer::stop() {
    transportSource.stop();
}

double DJAudioPlayer::getPositionRelative() {
    return transportSource.getCurrentPosition() / transportSource.getLengthInSeconds();
}

//>>>>>>>>>>>>>>>>>>>>>>>>MY CODE<<<<<<<<<<<<<<<<<<<<<<<<<<
void DJAudioPlayer::setPan(float panValue) {
    //seting the stereo pan level
    pan = panValue;
}

void DJAudioPlayer::getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill) {
    //clears the buffer region
    bufferToFill.clearActiveBufferRegion();
    //gets next block of audio data
    resampleSource.getNextAudioBlock(bufferToFill);

    //computes stereo balance based on pan
    float leftGain = (pan <= 0.0f ? 1.0f : 1.0f - pan);
    float rightGain = (pan >= 0.0f ? 1.0f : 1.0f + pan);

    // Applying the volume adjustment to each sample
    for (int sample = 0; sample < bufferToFill.numSamples; ++sample) {
        bufferToFill.buffer->getWritePointer(0)[sample] *= leftGain;
        bufferToFill.buffer->getWritePointer(1)[sample] *= rightGain;
    }
}
//>>>>>>>>>>>>>>>>>>>>>>>>MY CODE<<<<<<<<<<<<<<<<<<<<<<<<<<
