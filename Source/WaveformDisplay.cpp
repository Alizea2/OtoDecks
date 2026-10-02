/*
  ==============================================================================

    WaveformDisplay.cpp
    Created: 14 Mar 2020 3:50:16pm
    Author:  matthew

  ==============================================================================
*/

#include "WaveformDisplay.h"

WaveformDisplay::WaveformDisplay(juce::AudioFormatManager& formatManagerToUse, juce::AudioThumbnailCache& cacheToUse)
    : audioThumbnail(1000, formatManagerToUse, cacheToUse), fileLoaded(false), position(0.0),
        //>>>>>>>>>>>>>>>>>>>>>>>>MY CODE<<<<<<<<<<<<<<<<<<<<<<<<<<
        currentTheme(Neon), glowIntensity(0.5f)
        //>>>>>>>>>>>>>>>>>>>>>>>>MY CODE<<<<<<<<<<<<<<<<<<<<<<<<<<
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.
    audioThumbnail.addChangeListener(this);

    //>>>>>>>>>>>>>>>>>>>>>>>>MY CODE<<<<<<<<<<<<<<<<<<<<<<<<<<
    //Setup buttons
    addAndMakeVisible(neonButton);
    addAndMakeVisible(darkButton);
    addAndMakeVisible(fireButton);

    neonButton.addListener(this);
    darkButton.addListener(this);
    fireButton.addListener(this);

    //Setting button colors
    neonButton.setColour(juce::TextButton::buttonColourId, juce::Colours::purple);
    darkButton.setColour(juce::TextButton::buttonColourId, juce::Colours::darkgrey);
    fireButton.setColour(juce::TextButton::buttonColourId, juce::Colours::maroon);
 
    //makking text black
    neonButton.setColour(juce::TextButton::textColourOffId, juce::Colours::black);
    darkButton.setColour(juce::TextButton::textColourOffId, juce::Colours::black);
    fireButton.setColour(juce::TextButton::textColourOffId, juce::Colours::black);
}

void WaveformDisplay::paint(juce::Graphics& g)
{
    //background color
    g.fillAll(juce::Colours::black);

    if (fileLoaded)
    {
        //selecting the gradient colors dynamically
        juce::ColourGradient waveformGradient;

        switch (currentTheme)
        {
        case Neon:
            waveformGradient = juce::ColourGradient(
                juce::Colours::hotpink, 0, 0,
                juce::Colours::purple, getWidth(), getHeight(), false);
            waveformGradient.addColour(0.33, juce::Colours::magenta);
            waveformGradient.addColour(0.66, juce::Colours::blue);
            break;

        case Dark:
            waveformGradient = juce::ColourGradient(
                juce::Colours::lightgrey, 0, 0,
                juce::Colours::black, getWidth(), getHeight(), false);
            waveformGradient.addColour(0.5, juce::Colours::grey);
            break;

        case Fire:
            waveformGradient = juce::ColourGradient(
                juce::Colours::yellow, 0, 0,
                juce::Colours::red, getWidth(), getHeight(), false);
            waveformGradient.addColour(0.5, juce::Colours::orange);
            waveformGradient.addColour(0.75, juce::Colours::maroon);
            break;
        }

        //applying the gradient fill
        g.setGradientFill(waveformGradient);
        audioThumbnail.drawChannel(g, getLocalBounds().reduced(0, 30), 0.0, audioThumbnail.getTotalLength(), 0, 1.0f);

        //adding pulsing glow effect
        juce::Colour glowColor = juce::Colours::white.withAlpha(glowIntensity * 0.6f);
        g.setColour(glowColor);
        g.strokePath(juce::Path(), juce::PathStrokeType(5.0f));

        //drawing the position marker
        float posX = position * getWidth();
        g.setColour(juce::Colours::yellow);
        g.drawLine(posX, 30, posX, getHeight(), 2.0f);
    }
    else
    {
        g.setColour(juce::Colours::grey);
        g.setFont(20.0f);
        g.drawText("No file loaded", getLocalBounds(), juce::Justification::centred, true);
    }

    //animating the glow intensity
    glowIntensity = 0.5f + 0.5f * std::sin(juce::Time::getMillisecondCounterHiRes() * 0.005);
    repaint();
}

void WaveformDisplay::resized()
{
    //setting button dimenssions and positions
    int buttonWidth = getWidth() / 3;
    int buttonHeight = 30;
    neonButton.setBounds(5, 5, buttonWidth - 10, buttonHeight);
    darkButton.setBounds(buttonWidth + 5, 5, buttonWidth - 10, buttonHeight);
    fireButton.setBounds(2 * buttonWidth + 5, 5, buttonWidth - 10, buttonHeight);
}

void WaveformDisplay::changeListenerCallback(juce::ChangeBroadcaster* source)
{
    //repaints if the audio thumbnail updates
    if (source == &audioThumbnail)
        repaint();
}

void WaveformDisplay::buttonClicked(juce::Button* button)
{
    //changes theme based on button clicked
    if (button == &neonButton)
        setTheme(Neon);
    else if (button == &darkButton)
        setTheme(Dark);
    else if (button == &fireButton)
        setTheme(Fire);
}

void WaveformDisplay::loadURL(juce::URL audioURL)
{
    //loads a new audio file from URL
    audioThumbnail.clear();
    fileLoaded = audioThumbnail.setSource(new juce::URLInputSource(audioURL));
}

void WaveformDisplay::setPositionRelative(double pos)
{
    //sets the playback position
    if (pos >= 0 && pos <= 1.0)
    {
        position = pos;
        repaint();
    }
}

void WaveformDisplay::setTheme(Theme newTheme)
{
    //applying the selected theme and updating the display
    currentTheme = newTheme;
    repaint();
}
//>>>>>>>>>>>>>>>>>>>>>>>>MY CODE<<<<<<<<<<<<<<<<<<<<<<<<<<
