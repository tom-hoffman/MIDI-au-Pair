#include <MsTimer2.h>
#include <MIDI.h>
#include <Adafruit_GFX.h>
#include "Adafruit_LEDBackpack.h"

// MIDI au Pair
// by Tom Hoffman

// constants
static const byte MAP_CHANNEL = 15;
static const byte ND_GLOB_CHANNEL = 6;
static const byte ND_PAD_CHANNELS[6] = {0, 1, 2, 3, 4, 5};
static const byte PRESS = 0;
static const byte HOLD = 1;
static const byte LEFT = 0;
static const byte RIGHT = 1; 

// hardware setup boilerplate
MIDI_CREATE_DEFAULT_INSTANCE();
Adafruit_AlphaNum4 alpha4 = Adafruit_AlphaNum4();

static const byte PIN_LED_GRN = 6;
static const byte PIN_LED_RED = 7;
static const byte BUTTON_LEDS[2] = {11, 12};

// global variables & buffer

char display_buffer[] = "Helo";

// presets & patches
// A Preset is an array of up to 4 patches.
typedef struct Patch{
  byte controller;
  byte toe_down;
  byte toe_up;
} Patch;

typedef struct Preset{
  char id[3];               // two character string
  struct Patch patches[4];  // 4 patches should be enough for anyone
  byte on[2];               // controller/value to fire on start
  byte off[2];              // controller/value to fire on end
} Preset;

// remember to set this to the total number of presets 
static const byte preset_count = 3;
Preset presets[preset_count] = {
  {"--", {}, {0, 0}, {0, 0}},
  {"T1", {}, {0, 0}, {0, 0}},
  {"T2", {}, {0, 0}, {0, 0}}, 
};

typedef struct PadButtonState{
  bool active;
  byte preset;
  byte oscillator;
  byte pad_number;
} PadButtonState;

PadButtonState pad_buttons[2] = {{false, 1, 1, 3}, {false, 2, 2, 6}};

// arduino sketch loops

void setup()
{
  initHardware();
  writeDisplay();
  initMIDI();
  updatePadButtonPreset(LEFT);
  updatePadButtonPreset(RIGHT);
}

void loop()
{
  MIDI.read();
}
