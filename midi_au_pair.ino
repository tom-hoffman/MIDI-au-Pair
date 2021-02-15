#include <MsTimer2.h>
#include <MIDI.h>
#include <Adafruit_GFX.h>
#include "Adafruit_LEDBackpack.h"

// MIDI au Pair
// by Tom Hoffman

// MIDI Counting Notes:
// Channels seem consistent across all 3 devices, 1-16?
// ND Displays PC value +1

// constants
const byte MAP_CHANNEL = 15;
const byte ND_GLOB_CHANNEL = 6;
const byte ND_PAD_CHANNELS[6] = {0, 1, 2, 3, 4, 5};
const byte PRESS = 0;
const byte HOLD = 1;

// global variables & buffer

char display_buffer[] = "Helo";

// presets & patches
// A Preset is an array of up to 4 patches.
typedef struct Patch{
  byte controller;
  byte toe_down;
  byte toe_up;
} Patch;

// add ON/OFF
typedef struct Preset{
  char id[3];               // two character string
  struct Patch patches[4];  // 4 patches should be enough for anyone
  byte on[2];               // controller/value to fire on start
  byte off[2];              // controller/value to fire on end
} Preset;

// remember to set this to the total number of presets 
const byte preset_count = 3;
Preset presets[preset_count] = {
  {"--", {}, {0, 0}, {0, 0}},
  {"T1", {}, {0, 0}, {0, 0}},
  {"T2", {}, {0, 0}, {0, 0}}, 
};

typedef struct ButtonStatus{
  byte preset;
  byte oscillator;
  byte pad_number;
} ButtonStatus;

ButtonStatus left_button = {1, 1, 3};
ButtonStatus right_button = {2, 2, 6};

// hardware setup boilerplate
MIDI_CREATE_DEFAULT_INSTANCE();
Adafruit_AlphaNum4 alpha4 = Adafruit_AlphaNum4();

static const byte PIN_LED_GRN = 6;
static const byte PIN_LED_RED = 7;

// arduino sketch loops

void setup()
{
  initHardware();
  writeDisplay();
  initMIDI();
  displayButtonStatus(left_button, 'l');
  displayButtonStatus(right_button, 'r');
}

void loop()
{
  MIDI.read();
}
