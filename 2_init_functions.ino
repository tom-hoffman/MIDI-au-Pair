// init functions

// MIDI au Pair
// by Tom Hoffman

void initHardware() {
  pinMode(LED_BUILTIN, OUTPUT);
  alpha4.begin(0x70); 
  alpha4.setBrightness(1);
  pinMode(PIN_LED_GRN, OUTPUT);
  digitalWrite(PIN_LED_GRN, HIGH);
  pinMode(PIN_LED_RED, OUTPUT);
  digitalWrite(PIN_LED_RED, HIGH);
  pinMode(BUTTON_LEDS[LEFT], OUTPUT);
  digitalWrite(BUTTON_LEDS[LEFT], LOW);
  pinMode(BUTTON_LEDS[RIGHT], OUTPUT);
  digitalWrite(BUTTON_LEDS[RIGHT], LOW);
  pinMode(PULSE_LED, OUTPUT);
  analogWrite(PULSE_LED, 255);
}

void initMIDI() {
  MIDI.setHandleControlChange(handleCC);
  MIDI.setHandleClock(handleClock);
  MIDI.begin(MAP_CHANNEL);
  MIDI.sendProgramChange(0, ND_GLOB_CHANNEL);
}
