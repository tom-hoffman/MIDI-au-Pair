#include <MsTimer2.h>
#include <MIDI.h>
#include <Adafruit_GFX.h>
#include "Adafruit_LEDBackpack.h"

// MIDI au Pair
// by Tom Hoffman

// constants
const byte MAP_CHANNEL = 15;                        // MIDI au Pair's channel
const byte ND_GLOB_CHANNEL = 6;                     // Nord Drum III's global channel
// For now we're going to require the pad channels to be 0-5.
const byte PATCH_COUNT = 4;                         // Max. number or patches per preset
const byte PRESS = 0;                               // MIDI Baby l/r button press is set to value 0
const byte HOLD = 1;                                // MIDI Baby l/r button hold is set to value 1
const byte LONG_HOLD = 2;                           // MIDI Baby l/r button long hold is set to value 2
const byte LEFT = 0;                                // pad_buttons index
const byte RIGHT = 1;                               // pad_buttons index
const byte TOE_DOWN = 0;                            // MIDI CC value of toe down position
const byte TOE_UP = 127;                            // MIDI CC value of toe up position
const float TOETH = 1.0 / TOE_UP;                   // usually 1/127
const byte OSC_DELAY = 20;                          // wait between oscillator updates in milliseconds
const float twoPI = 2 * PI;                         // handy for sine wave calculations

// hardware setup boilerplate
MIDI_CREATE_DEFAULT_INSTANCE();
Adafruit_AlphaNum4 alpha4 = Adafruit_AlphaNum4();

const byte PIN_LED_GRN = 6;
const byte PIN_LED_RED = 7;
const byte PULSE_LED = 5;
const byte BUTTON_LEDS[2] = {8, 9};

// global variables & buffer

char display_buffer[] = "Helo";
byte last_pedal_pos = 0;
byte quarter_count = 0;
float osc_counter = 0;
unsigned long last_millis = 0;
unsigned long new_millis = 0;
unsigned int clock_millis = 0;
float OSC_INC = 0.001;    // calculate when clock changes

// presets & patches
// A Preset is an array of up to PATCH_COUNT patches.
typedef struct Patch{
  byte controller;
  byte toe_up;
  byte toe_down;
} Patch;

typedef struct Preset{
  char id;               
  struct Patch patches[PATCH_COUNT]; 
  byte on[2];               // controller/value to fire on start
  byte off[2];              // controller/value to fire on end
} Preset;

// remember to set this to the total number of presets 
const byte preset_count = 5;

Preset presets[16];

// oscillator values
// 0 - no oscillation -- just on and off messages.
// 1 - expression pedal controlled oscillation
// 2 - second sine wave
byte oscillator_count = 3;

typedef struct PadButtonState{
  bool active;
  byte pad_number;
  byte preset; 
  byte oscillator;
} PadButtonState;

PadButtonState pad_buttons[2] = {{false, 3, 0, 1}, {false, 6, 0, 1}};
byte last_cc_values[2][PATCH_COUNT]; 

// arduino sketch loops

void setup()
{
  initHardware();
  writeDisplay();
  initMIDI();
  for (int i = 0; i <= 1; i++) {
    updatePadButtonActiveLED(i);
  }  
  MsTimer2::set(OSC_DELAY, osc_handler);
  MsTimer2::start();
  readyDisplay();
  resetDisplay();
}

void loop()
{
  MIDI.read();
}
