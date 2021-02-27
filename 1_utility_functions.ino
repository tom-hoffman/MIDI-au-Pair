// utility functions

// MIDI au Pair
// by Tom Hoffman

int incrementPreset(byte current_preset) {
  if (current_preset < (preset_count - 1)) {
    return (current_preset + 1);
  }
  else {
    return 0;
  }
}
byte getPadChannel(byte pad) {
  return ND_PAD_CHANNELS[pad - 1];
}

bool isNotEmptyPatch(Patch p) {
  return ((p.controller != 0) || (p.toe_down != 0) || (p.toe_up != 0));
}

int scaleCC(byte value, byte toe_down, byte toe_up) {
  int range = toe_up - toe_down;
  float factor = range * TOETH;
  float scaled ((factor * value) + toe_down);
  int scaled_int = (int) scaled;
  return scaled_int;
}
