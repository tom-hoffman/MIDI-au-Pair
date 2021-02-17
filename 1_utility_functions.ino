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
