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

byte findPreset(char p[3]) {
  // returns index of named preset or 255 for no match.
  byte match = 255;
  for (int i = 0; (i < preset_count); i++) {
    if ((presets[i].id[0] == p[0]) && (presets[i].id[1] == p[1])) {
      match = i;
      break;
    }
  }
  return match;
}
