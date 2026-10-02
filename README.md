# OtoDecks

A two-deck **DJ application** written in **C++** with the **JUCE** framework. Load tracks onto two decks, mix them together, adjust volume, speed and position, pan each deck left or right, and watch an animated waveform with switchable colour themes.

Built as the final project for an Object-Oriented Programming course.

## Features

- **Two independent decks**, mixed together through a `MixerAudioSource`
- **Play / Stop** buttons with colour feedback
- **Sliders** for **volume**, **speed** and **playback position**
- **Playlist**: four track slots per deck
  - click an empty slot to choose an audio file, and the button shows *"Track Loaded: <file name>"*
  - click a loaded slot to load it onto the deck and start playing
- **Drag and drop**: drop an audio file onto a deck to load it
- **Pan control** for each deck: **Pan Left**, **Pan Right** and **Pan Off** (centre)
- **Waveform display** with a moving position marker, a pulsing glow and three themes: **Neon**, **Dark** and **Fire**
- **Oval buttons** drawn with a custom `LookAndFeel`

## Running the App

### Quick start (one command, macOS)

Run this command in the terminal. It downloads the project from GitHub into a temporary folder, downloads JUCE, builds the app and opens it:

```bash
D=$(mktemp -d) && gh repo clone Alizea2/OtoDecks "$D" && cd "$D" && cmake -B build -DCMAKE_BUILD_TYPE=Release && cmake --build build --config Release -j8 && open build/OtoDecks_artefacts/Release/OtoDecks.app
```

The first build takes a few minutes, because JUCE is downloaded and compiled too. When it finishes, the **OtoDecks** window opens by itself.

> This needs the Xcode Command Line Tools (`xcode-select --install`), [CMake](https://cmake.org/) 3.22+ (`brew install cmake`), and the [GitHub CLI](https://cli.github.com/) (`gh`) signed in to an account that can access this repository.

### With the Projucer (original setup)

1. Download [JUCE](https://juce.com/get-juce/) and open **Projucer**.
2. Open `otodecks_opp_app.jucer`.
3. In the exporter's module paths, point the modules to your JUCE `modules` folder.
4. Click **Save and Open in IDE**, then build and run in Xcode.

## How to use

1. On a deck, click **Track 1** (or another slot) and choose an audio file. You can also drag a file onto the deck.
2. Click the loaded track button, or **PLAY**, to start playback.
3. Use the **volume**, **speed** and **position** sliders while the track plays.
4. Use **Pan Left / Pan Right / Pan Off** to move the deck's sound between speakers.
5. Switch the waveform theme with **Neon**, **Dark** or **Fire**.
6. Load a second track on the other deck to mix the two.

## Project Structure

| File | Purpose |
|------|---------|
| `Source/Main.cpp` | Application entry point and main window |
| `Source/MainComponent.*` | Holds both decks, both pan controls and the audio mixer |
| `Source/DeckGUI.*` | One deck's interface: buttons, sliders, playlist and drag and drop |
| `Source/DJAudioPlayer.*` | Audio playback: loading, gain, speed, position and stereo panning |
| `Source/WaveformDisplay.*` | Waveform drawing, position marker and colour themes |
| `Source/PanControl.*` | Pan Left / Right / Off buttons |
| `otodecks_opp_app.jucer` | Projucer project |
| `CMakeLists.txt` | CMake build used by the Quick start (downloads JUCE 8.0.6) |

## Built With

- C++17
- [JUCE](https://juce.com/) 8: audio playback, mixing, waveform thumbnails and GUI

## Author

[@Alizea2](https://github.com/Alizea2)
