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

typedef struct Preset{
  char id[3];
  struct Patch patches[4];
} Preset;

const byte preset_count = 3;
Preset presets[preset_count] = {
  {"--", {0, 0, 0}},
  {"T1", {1, 1, 1}},
  {"T2", {2, 2, 2}}
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

// Code below from SparkFun example code (MIT Licensed).
static const byte PIN_BTN0 = 2;
static const byte PIN_BTN1 = 3;
static const byte PIN_BTN2 = 4;

static const byte PIN_POT0 = 0;
static const byte PIN_POT1 = 1;

static const byte PIN_LED_GRN = 6;
static const byte PIN_LED_RED = 7;
 


void initHardware() {
  pinMode(LED_BUILTIN, OUTPUT);
  alpha4.begin(0x70); 
  alpha4.setBrightness(1);
  pinMode(PIN_LED_GRN, OUTPUT);
  digitalWrite(PIN_LED_GRN, HIGH);
  pinMode(PIN_LED_RED, OUTPUT);
  digitalWrite(PIN_LED_RED, HIGH);
}

// utility functions

void writeDisplay() {
  for(int i=0; i<4; i++) {
    alpha4.writeDigitAscii(i, display_buffer[i]);
  }
  alpha4.writeDisplay();
}

void displayByte(byte b) {
  // displays exact value of a byte in hex, right justified.
  char a[2];
  itoa(b, a, 16); // converting 
  if (b <= 15) {
    display_buffer[2] = '0';
    display_buffer[3] = a[0];
  }
  else {
    display_buffer[2] = a[0];
    display_buffer[3] = a[1];
  }
  writeDisplay();
}

void displayButtonStatus(struct ButtonStatus B, char side) {
  char t[3];
  int i;
  strcpy(t, presets[B.preset].id);
  if (side == 'l') {i = 0;}
  else {i = 2;}
  display_buffer[i] = t[0];
  display_buffer[i+1] = t[1];
  writeDisplay();
}

int incrementPreset(byte current_preset) {
  if (current_preset < (preset_count - 1)) {
    return (current_preset + 1);
  }
  else {
    return 0;
  }
}

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

// MIDI & message handlers
void initMIDI() {
  MIDI.setHandleControlChange(handleCC);
  MIDI.begin(MAP_CHANNEL);
  MIDI.sendProgramChange(0, ND_GLOB_CHANNEL);
}

void handleCC(byte channel, byte controller, byte value) {
  digitalWrite(PIN_LED_RED, LOW);
  switch (controller) {
    case 12:
      handleLeftPress(value);
      break;
    case 13:
      handleRightPress(value);
      break;
  }
  digitalWrite(PIN_LED_RED, HIGH);
}

void handleLeftPress(byte value) {
  switch (value) {
    case HOLD:
      left_button.preset = incrementPreset(left_button.preset);
      displayButtonStatus(left_button, 'l');
      alpha4.writeDisplay();
      break;
  }
}

void handleRightPress(byte value) {
  switch (value) {
    case HOLD:
      right_button.preset = incrementPreset(right_button.preset);
      displayButtonStatus(right_button, 'r');
      alpha4.writeDisplay();
      break;
  }
}
