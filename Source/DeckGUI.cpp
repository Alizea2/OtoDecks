/*
  ==============================================================================

    DeckGUI.cpp
    Created: 13 Mar 2020 6:44:48pm
    Author:  matthew

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "DeckGUI.h"

DeckGUI::DeckGUI(DJAudioPlayer* player, AudioFormatManager &formatManagerToUse, AudioThumbnailCache &cacheToUse)
    : player(player), waveformDisplay(formatManagerToUse, cacheToUse)
{
    //>>>>>>>>>>>>>>>>>>>>>>>>MY CODE<<<<<<<<<<<<<<<<<<<<<<<<<<
    //setting up the play button
    addAndMakeVisible(playButton);
    playButton.addListener(this);
    playButton.setColour(TextButton::textColourOffId, Colours::black);

    //setting up the stop button
    addAndMakeVisible(stopButton);
    stopButton.addListener(this);
    stopButton.setColour(TextButton::textColourOffId, Colours::black);

    //adding the sliders for volume, speed, and position
    initialiseSliders();
    
    addAndMakeVisible(volSlider);
    volSlider.addListener(this);

    addAndMakeVisible(speedSlider);
    speedSlider.addListener(this);

    addAndMakeVisible(posSlider);
    posSlider.addListener(this);

    //title for the track buttons
    addAndMakeVisible(playlistLabel);
    playlistLabel.setText("Load Your Playlist", dontSendNotification);
    playlistLabel.setFont(Font(16.0f, Font::bold));
    playlistLabel.setJustificationType(Justification::centred);

    //adding track buttons
    initialiseTrackButton(trackButton1, "Track 1");
    initialiseTrackButton(trackButton2, "Track 2");
    initialiseTrackButton(trackButton3, "Track 3");
    initialiseTrackButton(trackButton4, "Track 4");

    //adding the waveform display
    addAndMakeVisible(waveformDisplay);

    startTimer(40);
    //>>>>>>>>>>>>>>>>>>>>>>>>MY CODE<<<<<<<<<<<<<<<<<<<<<<<<<<
}

DeckGUI::~DeckGUI()
{
}

//>>>>>>>>>>>>>>>>>>>>>>>>MY CODE<<<<<<<<<<<<<<<<<<<<<<<<<<
void DeckGUI::initialiseTrackButton(TextButton& button, const String& name) {
    //setups individual track buttons
    button.setButtonText(name);
    button.setColour(TextButton::buttonColourId, Colours::darkgrey);
    button.setColour(TextButton::textColourOffId, Colours::black);
    button.addListener(this);
    addAndMakeVisible(button);
}

void DeckGUI::initialiseSliders()
{
    //volume slider customization
    volSlider.setSliderStyle(Slider::RotaryVerticalDrag);
    volSlider.setColour(Slider::thumbColourId, Colours::maroon);
    volSlider.setTextBoxStyle(Slider::TextBoxLeft, false, 120, 20);
    volSlider.setTextValueSuffix(" Volume");
    volSlider.setRange(0.1, 1.0, 0.00);
    addAndMakeVisible(volSlider);

    //speed slider customization
    speedSlider.setSliderStyle(Slider::RotaryVerticalDrag);
    speedSlider.setColour(Slider::thumbColourId, Colours::green);
    speedSlider.setTextBoxStyle(Slider::TextBoxLeft, false, 120, 20);
    speedSlider.setTextValueSuffix(" Speed");
    speedSlider.setRange(0.1, 1.0, 0.01);
    addAndMakeVisible(speedSlider);

    //position slider customization
    posSlider.setSliderStyle(Slider::RotaryVerticalDrag);
    posSlider.setColour(Slider::thumbColourId, Colours::blue);
    posSlider.setTextBoxStyle(Slider::TextBoxLeft, false, 120, 20);
    posSlider.setTextValueSuffix(" Position");
    posSlider.setRange(0.1, 1.0, 0.00);
    addAndMakeVisible(posSlider);
}

void DeckGUI::paint(Graphics& g)
{
    g.fillAll(getLookAndFeel().findColour(ResizableWindow::backgroundColourId));
}

void DeckGUI::resized()
{
    //calculates row height
    auto rowH = getHeight() / 12;

    //setting up smaller oval buttons
    int buttonWidth = getWidth() / 4;
    int buttonHeight = rowH * 0.8;
    int buttonXOffset = (getWidth() / 2 - buttonWidth) / 2;

    //play and stop buttons with oval shape
    playButton.setBounds(buttonXOffset, rowH * 0.2, buttonWidth, buttonHeight);
    stopButton.setBounds(getWidth() / 2 + buttonXOffset, rowH * 0.2, buttonWidth, buttonHeight);
    
    playButton.setColour(TextButton::buttonColourId, Colours::lightgrey);
    stopButton.setColour(TextButton::buttonColourId, Colours::lightgrey);

    //round corners for oval shape
    playButton.setLookAndFeel(&customLookAndFeel);
    stopButton.setLookAndFeel(&customLookAndFeel);

    //setting up layout for sliders,labels and track buttons
    auto sliderHeight = rowH * 1.5;
    volSlider.setBounds(10, rowH, getWidth() - 20, sliderHeight);
    speedSlider.setBounds(10, rowH * 2.5, getWidth() - 20, sliderHeight);
    posSlider.setBounds(10, rowH * 4, getWidth() - 20, sliderHeight);

    playlistLabel.setBounds(0, rowH * 5, getWidth(), rowH);

    trackButton1.setBounds(0, rowH * 6, getWidth(), rowH);
    trackButton2.setBounds(0, rowH * 6.8, getWidth(), rowH);
    trackButton3.setBounds(0, rowH * 7.6, getWidth(), rowH);
    trackButton4.setBounds(0, rowH * 8.4, getWidth(), rowH);

    //set waveform display bounds
    waveformDisplay.setBounds(0, rowH * 9.2, getWidth(), rowH * 3);
}

void DeckGUI::buttonClicked(Button* button)
{
    //handlling play and stop button clicks
    if (button == &playButton)
    {
        player->start();
        playButton.setColour(TextButton::buttonColourId, Colours::green);
        Timer::callAfterDelay(1000, [this]() {
            playButton.setColour(TextButton::buttonColourId, Colours::lightgrey);
        });
        return;
    }

    if (button == &stopButton)
    {
        player->stop();
        stopButton.setColour(TextButton::buttonColourId, Colours::maroon);
        Timer::callAfterDelay(1000, [this]() {
            stopButton.setColour(TextButton::buttonColourId, Colours::lightgrey);
        });
        return;
    }

    //handlling track selection for existing loaded tracks
    if (trackPaths.find(static_cast<TextButton*>(button)) != trackPaths.end())
    {
        String filePath = trackPaths[static_cast<TextButton*>(button)];
        File chosenFile(filePath);
        if (chosenFile.existsAsFile())
        {
            if (currentTrackButton != button)
            {
                player->stop();
            }

            player->loadURL(URL{chosenFile});
            waveformDisplay.loadURL(URL{chosenFile});
            player->start();
            currentTrackButton = static_cast<TextButton*>(button);
        }
        return;
    }

    //handles new track loading
    if (button == &trackButton1 || button == &trackButton2 || button == &trackButton3 || button == &trackButton4)
    {
        fChooser.launchAsync(FileBrowserComponent::canSelectFiles, [this, button](const FileChooser& chooser)
        {
            File chosenFile = chooser.getResult();
            if (chosenFile.exists())
            {
                trackPaths[static_cast<TextButton*>(button)] = chosenFile.getFullPathName();
                button->setButtonText("Track Loaded: " + chosenFile.getFileName());
            }
        });
    }
}
//>>>>>>>>>>>>>>>>>>>>>>>>MY CODE<<<<<<<<<<<<<<<<<<<<<<<<<<

void DeckGUI::sliderValueChanged(Slider *slider)
{
    // Implementation of slider functionalities as before
    if (slider == &volSlider)
      {
          player->setGain(slider->getValue());
      }
      if (slider == &speedSlider)
      {
          player->setSpeed(slider->getValue());
      }
      if (slider == &posSlider)
      {
          player->setPositionRelative(slider->getValue());
      }
}

void DeckGUI::timerCallback()
{
    waveformDisplay.setPositionRelative(player->getPositionRelative());
}

//>>>>>>>>>>>>>>>>>>>>>>>>MY CODE<<<<<<<<<<<<<<<<<<<<<<<<<<
bool DeckGUI::isInterestedInFileDrag(const StringArray &files)
{
    return files.size() > 0;
}

void DeckGUI::filesDropped(const StringArray &files, int x, int y)
{
    //ensuring only one file is dropped
    if (files.size() == 1)
    {
        File droppedFile = File(files[0]);
        //checking if file exists
        if (droppedFile.existsAsFile())
        {
            player->loadURL(URL{droppedFile});
            waveformDisplay.loadURL(URL{droppedFile});
            //automatically plays the dropped file
            player->start();
        }
    }
}
//>>>>>>>>>>>>>>>>>>>>>>>>MY CODE<<<<<<<<<<<<<<<<<<<<<<<<<<






