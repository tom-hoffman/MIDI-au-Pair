#include <math.h>
#include <MsTimer2.h>
#include <MIDI.h>
#include <Adafruit_GFX.h>
#include "Adafruit_LEDBackpack.h"

// MIDI au Pair
// by Tom Hoffman

// constants
const byte MAP_CHANNEL = 15;
const byte ND_GLOB_CHANNEL = 6;
const byte ND_PAD_CHANNELS[6] = {0, 1, 2, 3, 4, 5};
const byte PATCH_COUNT = 4;
const byte PRESS = 0;
const byte HOLD = 1;
const byte LEFT = 0;
const byte RIGHT = 1; 
const byte TOE_DOWN = 0;
const byte TOE_UP = 127;

// hardware setup boilerplate
MIDI_CREATE_DEFAULT_INSTANCE();
Adafruit_AlphaNum4 alpha4 = Adafruit_AlphaNum4();

const byte PIN_LED_GRN = 6;
const byte PIN_LED_RED = 7;
const byte BUTTON_LEDS[2] = {11, 12};

// global variables & buffer

char display_buffer[] = "Helo";

// presets & patches
// A Preset is an array of up to PATCH_COUNT patches.
typedef struct Patch{
  byte controller;
  byte toe_up;
  byte toe_down;
} Patch;

typedef struct Preset{
  char id[3];               // two character string
  struct Patch patches[PATCH_COUNT]; 
  byte on[2];               // controller/value to fire on start
  byte off[2];              // controller/value to fire on end
} Preset;

// remember to set this to the total number of presets 
const byte preset_count = 3;
Preset presets[preset_count] = {
  {"--",  {}, {0, 0}, {0, 0}},
  // "Hi" is a natural-ish hi-hat open/close dynamic.
  {"Hi", {{17, 64, 0}, {30, 0, 127}, {21, 70, 16}, {50, 70, 16}}, {0, 0}, {0, 0}},
  // "WA" is a wah-wah effect sweeping the parametric eq.
  {"WA", {25, 0, 127}, {26, 64}, {26, 0}}, 
};

float patchScales[preset_count][PATCH_COUNT];

// oscillator values
// 0 - no oscillation -- just on and off messages.
// 1 - expression pedal controlled oscillation

typedef struct PadButtonState{
  bool active;
  byte pad_number;
  byte preset; 
  byte oscillator;
} PadButtonState;

PadButtonState pad_buttons[2] = {{false, 3, 1, 1}, {false, 6, 2, 1}};

// arduino sketch loops

void setup()
{
  initHardware();
  writeDisplay();
  initMIDI();
  calculatePatchScales();
  for (int i = 0; i <= 1; i++) {
    updatePadButtonPreset(i);
    updatePadButtonActiveLED(i);
  }  
}

void loop()
{
  MIDI.read();
}
