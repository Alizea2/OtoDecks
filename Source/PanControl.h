/*
  =============================================================================

    PanControl.
    Created: 2 Mar 2025 12:48:26a
    Author:  Alizea Ari

  =============================================================================
*/

//>>>>>>>>>>>>>>>>>>>>>>>>MY CODE<<<<<<<<<<<<<<<<<<<<<<<<<<
#pragma once

#include <JuceHeader.h>
#include "DJAudioPlayer.h"  

class PanControl : public juce::Component
{
public:
    PanControl(DJAudioPlayer& player);
    virtual ~PanControl();

    //override to handle painting
    void paint (juce::Graphics&) override;
    //override to handle resizinng
    void resized() override;

private:
    DJAudioPlayer& audioProcessor;

    //panning buttons
    juce::TextButton panLeftButton;
    juce::TextButton panRightButton;
    juce::TextButton panCenterButton;

    //callback methods for button clicks
    void setPanLeft();
    void setPanRight();
    void setPanCenter();

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PanControl)
};
//>>>>>>>>>>>>>>>>>>>>>>>>MY CODE<<<<<<<<<<<<<<<<<<<<<<<<<<
