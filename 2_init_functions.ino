// init functions

// MIDI au Pair
// by Tom Hoffman

void initMIDI() {
  MIDI.setHandleControlChange(handleCC);
  MIDI.setHandleClock(handleClock);
  MIDI.setHandleSystemExclusive(handleSysex);
  MIDI.begin(MAP_CHANNEL);
  MIDI.sendProgramChange(0, ND_GLOB_CHANNEL);
}

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
  pinMode(ROTARY_PIN_1, INPUT_PULLUP);
  pinMode(ROTARY_PIN_2, INPUT_PULLUP);
  pinMode(ROTARY_PRESS, INPUT_PULLUP);
  digitalWrite(ROTARY_PIN_1, HIGH);
  pinMode(SIDE_SWITCH, INPUT_PULLUP);
 
  bouncer.attach(ROTARY_PIN_1);
  bouncer.interval(5); 
  fram.begin();
  readPresetsfromFRAM();
}

void readPresetsfromFRAM() {
  byte len = fram.read8(2);
  byte a[len];
  for (int i; i < len; i++) {
    a[i] = fram.read8(i);
  }
  buildPresets(a);
}




  
