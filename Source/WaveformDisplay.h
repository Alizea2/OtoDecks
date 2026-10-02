/*
  ==============================================================================

    WaveformDisplay.h
    Created: 14 Mar 2020 3:50:16pm
    Author:  matthew

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class WaveformDisplay : public juce::Component,
                        public juce::ChangeListener,
                        public juce::Button::Listener
{
public:
    enum Theme { Neon, Dark, Fire };

    WaveformDisplay(juce::AudioFormatManager& formatManagerToUse, juce::AudioThumbnailCache& cacheToUse);

    void paint(juce::Graphics&) override;
    void resized() override;
    
    void changeListenerCallback(juce::ChangeBroadcaster* source) override;

    void loadURL(juce::URL audioURL);
    
    /* set the relative position of the playhead*/
    void setPositionRelative(double pos);
    
    //>>>>>>>>>>>>>>>>>>>>>>>>MY CODE<<<<<<<<<<<<<<<<<<<<<<<<<<
    //setting the display theme and handling button cliclk
    void setTheme(Theme newTheme);
    void buttonClicked(juce::Button* button) override;
    //>>>>>>>>>>>>>>>>>>>>>>>>MY CODE<<<<<<<<<<<<<<<<<<<<<<<<<<
    
private:
    juce::AudioThumbnail audioThumbnail;
    bool fileLoaded;
    double position;
    
    //>>>>>>>>>>>>>>>>>>>>>>>>MY CODE<<<<<<<<<<<<<<<<<<<<<<<<<<
    //setting the intensity of the glow effect based on the currently selected theme
    Theme currentTheme;
    float glowIntensity;

    //theme buttons
    juce::TextButton neonButton { "Neon" };
    juce::TextButton darkButton { "Dark" };
    juce::TextButton fireButton { "Fire" };

    //custom LookAndFeel for rounded buttons
    struct RoundedButtonLookAndFeel : public juce::LookAndFeel_V4
    {
        void drawButtonBackground(juce::Graphics& g, juce::Button& button, const juce::Colour& backgroundColour,
                                  bool shouldDrawButtonAsHighlighted, bool shouldDrawButtonAsDown) override
        {
            auto bounds = button.getLocalBounds().toFloat().reduced(2.0f);
            //corner radius
            float cornerSize = 10.0f;

            juce::Colour fillColour = backgroundColour;

            //click effect
            if (shouldDrawButtonAsDown)
                fillColour = fillColour.darker(0.2f);
            //hover effect
            else if (shouldDrawButtonAsHighlighted)
                fillColour = fillColour.brighter(0.2f);

            //main button area
            g.setColour(fillColour);
            g.fillRoundedRectangle(bounds, cornerSize);

            //border effect
            g.setColour(juce::Colours::black);
            g.drawRoundedRectangle(bounds, cornerSize, 2.0f);
        }
    };
    //instance of LookAndFeel
    RoundedButtonLookAndFeel buttonLookAndFeel;
    //>>>>>>>>>>>>>>>>>>>>>>>>MY CODE<<<<<<<<<<<<<<<<<<<<<<<<<<
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(WaveformDisplay)
};
