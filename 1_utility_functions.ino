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

byte scaleCC(byte value, byte toe_down, byte toe_up) {
  byte range = toe_up - toe_down;
  float factor = range / 127;
  return ((factor * value) + toe_down);
}
