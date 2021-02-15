void initHardware() {
  pinMode(LED_BUILTIN, OUTPUT);
  alpha4.begin(0x70); 
  alpha4.setBrightness(1);
  pinMode(PIN_LED_GRN, OUTPUT);
  digitalWrite(PIN_LED_GRN, HIGH);
  pinMode(PIN_LED_RED, OUTPUT);
  digitalWrite(PIN_LED_RED, HIGH);
}

void initMIDI() {
  MIDI.setHandleControlChange(handleCC);
  MIDI.begin(MAP_CHANNEL);
  MIDI.sendProgramChange(0, ND_GLOB_CHANNEL);
}
