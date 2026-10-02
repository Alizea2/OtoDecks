/*
  =============================================================================

    PanControl.cp
    Created: 2 Mar 2025 12:48:26a
    Author:  Alizea Ari

  =============================================================================
*/
//>>>>>>>>>>>>>>>>>>>>>>>>MY CODE<<<<<<<<<<<<<<<<<<<<<<<<<<
#include "PanControl.h"

PanControl::PanControl(DJAudioPlayer& player)
    : audioProcessor(player),
      //initialize the pan left button
      panLeftButton("Pan Left"),
      //initialize the pan right button
      panRightButton("Pan Right"),
      //initialize the pan center button
      panCenterButton("Pan Off")
{
    //adding and making pan buttons
    addAndMakeVisible(panLeftButton);
    addAndMakeVisible(panRightButton);
    addAndMakeVisible(panCenterButton);

    //attaching callback functions to the buttons
    panLeftButton.onClick = [this] { setPanLeft(); };
    panRightButton.onClick = [this] { setPanRight(); };
    panCenterButton.onClick = [this] { setPanCenter(); };

    //button color and style
    panLeftButton.setColour(juce::TextButton::buttonColourId, juce::Colours::darkgrey);
    panRightButton.setColour(juce::TextButton::buttonColourId, juce::Colours::darkgrey);
    panCenterButton.setColour(juce::TextButton::buttonColourId, juce::Colours::darkgrey);
}

PanControl::~PanControl()
{
}

void PanControl::paint(juce::Graphics& g)
{
    //background color
    g.fillAll(juce::Colours::transparentBlack);
}

void PanControl::resized()
{
    //defines the layout of the buttons
    auto area = getLocalBounds();
    int buttonWidth = area.getWidth() / 3;
    panLeftButton.setBounds(area.removeFromLeft(buttonWidth));
    panCenterButton.setBounds(area.removeFromLeft(buttonWidth));
    panRightButton.setBounds(area);
}

//callback functions to set audio pan
void PanControl::setPanLeft()
{
    //full left
    audioProcessor.setPan(-1.0);
}
void PanControl::setPanCenter()
{
    //center
    audioProcessor.setPan(0.0);
}
void PanControl::setPanRight()
{
    //full right
    audioProcessor.setPan(1.0);
}
//>>>>>>>>>>>>>>>>>>>>>>>>MY CODE<<<<<<<<<<<<<<<<<<<<<<<<<<
