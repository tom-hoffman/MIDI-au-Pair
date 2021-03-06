#include <SPI.h>
#include <MsTimer2.h>
#include <MIDI.h>
#include <Bounce2.h>
#include <Adafruit_GFX.h>
#include "Adafruit_FRAM_SPI.h"
#include "Adafruit_LEDBackpack.h"

#define DEBUG

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

// FRAM setup
const byte FRAM_CS = 10;
Adafruit_FRAM_SPI fram = Adafruit_FRAM_SPI(FRAM_CS);  // use hardware SPI
const byte FRAM_SCK = 13;
const byte FRAM_MISO = 12;
const byte FRAM_MOSI = 11;
const byte addrSizeInByte = 2; 
uint32_t memSize;

const byte PIN_LED_GRN = 6;
const byte PIN_LED_RED = 7;
const byte PULSE_LED = 5;
const byte BUTTON_LEDS[2] = {8, 9};

// rotary encoder
const byte ROTARY_PIN_1 = 2;
const byte ROTARY_PIN_2 = 3;
const byte ROTARY_PRESS = 4;
Bounce bouncer = Bounce();

// switch to choose side for encoder 
const byte SIDE_SWITCH = A2;

// global variables & buffer

byte preset_count = 0;
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

Preset presets[16];

// oscillator values
// 0 - '/' - no oscillation -- just on and off messages.
// 1 - 'X' - expression pedal controlled oscillation
// 2 - '1' - 1x sine wave
// 3 - 'U' - squarish fourier transform
byte const oscillator_count = 4;
byte oscillators[oscillator_count] = {'-', 'X', '1', 'U'};

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
  checkRotary();
}
