///*
//  ==============================================================================
//
//    DeckGUI.h
//    Created: 13 Mar 2020 6:44:48pm
//    Author:  matthew
//
//  ==============================================================================
//*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "DJAudioPlayer.h"
#include "WaveformDisplay.h"
#include <map>

using namespace juce;

//>>>>>>>>>>>>>>>>>>>>>>>>MY CODE<<<<<<<<<<<<<<<<<<<<<<<<<<
//custom LookAndFeel class for creating oval shaped buttons
class OvalButtonLookAndFeel : public LookAndFeel_V4
{
public:
    //override to draw an oval button background
    void drawButtonBackground(Graphics& g, Button& button, const Colour& backgroundColour,
                              bool isMouseOverButton, bool isButtonDown) override
    {
        auto bounds = button.getLocalBounds().toFloat();
        g.setColour(backgroundColour);
        //draws the button as an oval
        g.fillEllipse(bounds);

        g.setColour(Colours::black);
        //adding an outline for better visibility
        g.drawEllipse(bounds, 2.0f);
    }
};
//>>>>>>>>>>>>>>>>>>>>>>>>MY CODE<<<<<<<<<<<<<<<<<<<<<<<<<<

class DeckGUI : public Component,
                public Button::Listener,
                public Slider::Listener,
                public FileDragAndDropTarget,
                public Timer
{
public:
    DeckGUI(DJAudioPlayer* player,
            AudioFormatManager &formatManagerToUse,
            AudioThumbnailCache &cacheToUse);
    ~DeckGUI();

    void paint(Graphics&) override;
    void resized() override;

    /* implement Button::Listener */
    void buttonClicked(Button*) override;
    
    /*implement Slider::Listener */
    void sliderValueChanged(Slider* slider) override;

    bool isInterestedInFileDrag(const StringArray &files) override;
    void filesDropped(const StringArray &files, int x, int y) override;

    void timerCallback() override;

private:
    juce::FileChooser fChooser{"Select an MP3 file..."};

    TextButton playButton{"PLAY"};
    TextButton stopButton{"STOP"};

    Slider volSlider;
    Slider speedSlider;
    Slider posSlider;
    
    //>>>>>>>>>>>>>>>>>>>>>>>>MY CODE<<<<<<<<<<<<<<<<<<<<<<<<<<
    //initializes slider properties
    void initialiseSliders();
    //track button setup
    void initialiseTrackButton(TextButton& button, const String& name);
    

    //title for the playlist
    Label playlistLabel;

    //track buttons
    TextButton trackButton1{"Track 1"};
    TextButton trackButton2{"Track 2"};
    TextButton trackButton3{"Track 3"};
    TextButton trackButton4{"Track 4"};

    //map to store track file paths
    std::map<TextButton*, String> trackPaths;
    TextButton* currentTrackButton = nullptr;

    // Custom LookAndFeel for oval buttons
    OvalButtonLookAndFeel customLookAndFeel;
    //>>>>>>>>>>>>>>>>>>>>>>>>MY CODE<<<<<<<<<<<<<<<<<<<<<<<<<<
    
    WaveformDisplay waveformDisplay;
    
    DJAudioPlayer* player;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(DeckGUI)
};
