// utility functions

// MIDI au Pair
// by Tom Hoffman

void changePreset(byte side, int value) {
  if ((pad_buttons[side].preset == 0) && (value == -1)) {
    pad_buttons[side].preset = (preset_count - 1);
  }
  else {
    pad_buttons[side].preset = (pad_buttons[side].preset + value) % preset_count;
  }
  display_buffer[side * 2] = presets[pad_buttons[side].preset].id;
  writeDisplay();
}

void changeOscillator(byte side, int value) {
  if ((pad_buttons[side].oscillator == 0) && (value == -1)) {
    pad_buttons[side].oscillator = (oscillator_count - 1);
  }
  else {
    pad_buttons[side].oscillator = (pad_buttons[side].oscillator + value) % oscillator_count;
  }
  char a[2];
  display_buffer[(side * 2) + 1] = oscillators[pad_buttons[side].oscillator];
  changePreset(side, -1);
  writeDisplay();
}

bool isNotEmptyPatch(Patch p) {
  return (p.controller != 0);
}

int scaleCC(byte value, byte toe_down, byte toe_up) {
  // FIXME -> doesn't work right with reversed range 127 - 0 (only?)
  int range = toe_up - toe_down;
  float factor = range * TOETH;
  float scaled ((factor * value) + toe_down);
  int scaled_int = scaled;
  return scaled_int;
}
