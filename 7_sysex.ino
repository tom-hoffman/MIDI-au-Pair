// oscillators

// MIDI au Pair
// by Tom Hoffman

void buildPresets(byte *a, unsigned int len) {
  byte counter = 3;
  byte number_of_presets = len / 17; // this could be calculated using patch_count?
  for (int i = 0; i < number_of_presets; i++) {
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
