/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#include "MainComponent.h"

//==============================================================================
MainComponent::MainComponent()
                          : panControl1(player1), panControl2(player2)
{
    // Make sure you set the size of the component after
    // you add any child components.
    setSize (800, 600);

    // Some platforms require permissions to open input channels so request that here
    if (RuntimePermissions::isRequired (RuntimePermissions::recordAudio)
        && ! RuntimePermissions::isGranted (RuntimePermissions::recordAudio))
    {
        RuntimePermissions::request (RuntimePermissions::recordAudio,
                                     [&] (bool granted) { if (granted)  setAudioChannels (2, 2); });
    }
    else
    {
        // Specify the number of input and output channels that we want to open
        setAudioChannels (0, 2);
    }

    addAndMakeVisible(deckGUI1);
    addAndMakeVisible(deckGUI2);

    formatManager.registerBasicFormats();

    //>>>>>>>>>>>>>>>>>>>>>>>>MY CODE<<<<<<<<<<<<<<<<<<<<<<<<<<
    //adding pan controls
    addAndMakeVisible(panControl1);
    addAndMakeVisible(panControl2);
    //>>>>>>>>>>>>>>>>>>>>>>>>MY CODE<<<<<<<<<<<<<<<<<<<<<<<<<<
}

MainComponent::~MainComponent()
{
    // This shuts down the audio device and clears the audio source.
    shutdownAudio();
}

//==============================================================================
void MainComponent::prepareToPlay (int samplesPerBlockExpected, double sampleRate)
{
    player1.prepareToPlay(samplesPerBlockExpected, sampleRate);
    player2.prepareToPlay(samplesPerBlockExpected, sampleRate);
    
    mixerSource.prepareToPlay(samplesPerBlockExpected, sampleRate);

    mixerSource.addInputSource(&player1, false);
    mixerSource.addInputSource(&player2, false);

 }

//>>>>>>>>>>>>>>>>>>>>>>>>MY CODE<<<<<<<<<<<<<<<<<<<<<<<<<<
void MainComponent::getNextAudioBlock (const AudioSourceChannelInfo& bufferToFill)
{
    //clears the buffer
    bufferToFill.clearActiveBufferRegion();
    //processes audio mixing
    mixerSource.getNextAudioBlock(bufferToFill);

    //analyzes and logs the max audio level for monitoring
    auto* leftChannelData = bufferToFill.buffer->getReadPointer(0, bufferToFill.startSample);
    float maxLevel = 0.0f;
    for (int i = 0; i < bufferToFill.numSamples; ++i) {
        maxLevel = std::max(maxLevel, std::abs(leftChannelData[i]));
    }
    DBG("Max level: " + juce::String(maxLevel));
}
//>>>>>>>>>>>>>>>>>>>>>>>>MY CODE<<<<<<<<<<<<<<<<<<<<<<<<<<

void MainComponent::releaseResources()
{
    // This will be called when the audio device stops, or when it is being
    // restarted due to a setting change.

    // For more details, see the help for AudioProcessor::releaseResources()
    player1.releaseResources();
    player2.releaseResources();
    mixerSource.releaseResources();
}

//==============================================================================
void MainComponent::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));

    // You can add your drawing code here!
}

//>>>>>>>>>>>>>>>>>>>>>>>>MY CODE<<<<<<<<<<<<<<<<<<<<<<<<<<
void MainComponent::resized()
{
    //layout calculation for GUI components
    auto area = getLocalBounds();
    //deck area
    auto topHalf = area.removeFromTop(area.getHeight() - 100);
    //pan area
    auto bottomHalf = area;

    //settinf the deck GUI positions
    deckGUI1.setBounds(topHalf.removeFromLeft(getWidth() / 2));
    deckGUI2.setBounds(topHalf);

    //Setting pan control positions
    panControl1.setBounds(bottomHalf.removeFromLeft(getWidth() / 2));
    panControl2.setBounds(bottomHalf);
}
//>>>>>>>>>>>>>>>>>>>>>>>>MY CODE<<<<<<<<<<<<<<<<<<<<<<<<<<
