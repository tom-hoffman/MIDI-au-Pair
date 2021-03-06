// utility functions

// MIDI au Pair
// by Tom Hoffman

byte getPadChannel(byte pad) {
  return ND_PAD_CHANNELS[pad - 1];
}

bool isNotEmptyPatch(Patch p) {
  return (p.controller != 0);
}

int scaleCC(byte value, byte toe_down, byte toe_up) {
  // FIXME -> doesn't work right with reversed range 127 - 0 (only)
  int range = toe_up - toe_down;
  float factor = range * TOETH;
  float scaled ((factor * value) + toe_down);
  int scaled_int = scaled;
  return scaled_int;
}
