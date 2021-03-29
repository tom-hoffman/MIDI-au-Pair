// presets

// MIDI au Pair
// by Tom Hoffman

void buildPresets(byte *a) {
  // note that this expects the complete sysex data stream.
  byte counter = 3;
  byte len = *(a + 2);
  preset_count = (len - 4) / 17;
  for (int i = 0; i < preset_count; i++) {
    digitalWrite(PIN_LED_RED, LOW);
    presets[i].id = *(a + counter);
    counter++;
    for (int j = 0; j < PATCH_COUNT; j++) {
      presets[i].patches[j].controller = *(a + counter);
      counter++;
      presets[i].patches[j].toe_up = *(a + counter);
      counter++;
      presets[i].patches[j].toe_down = *(a + counter);
      counter++;
    }
    presets[i].on[0] = *(a + counter);
    counter++;
    presets[i].on[1] = *(a + counter);
    counter++;
    presets[i].off[0] = *(a + counter);
    counter++;
    presets[i].off[1] = *(a + counter);
    counter++;
    digitalWrite(PIN_LED_RED, HIGH);
  }
}

void writePresetstoFRAM(byte *a, unsigned int len) {
  // note that this writes the whole sysex data stream.
  // for now go with 17 bytes for a patch
  digitalWrite(PIN_LED_GRN, LOW);
  for (uint8_t i = 0; i < len; i++) {
    fram.writeEnable(true);
    fram.write8(i, *(a + i));
    fram.writeEnable(false);
  }
  digitalWrite(PIN_LED_GRN, HIGH);
}
