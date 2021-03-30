// oscillators

// MIDI au Pair
// by Tom Hoffman

// These are hard-wired here.

void osc_handler() {
  PadButtonState button;
  // for each button
  for (int i = 0; i <= 1; i++) {
    // get the button
    button = pad_buttons[i];
    // check to see if it is active
    if (button.active) {
      switch (button.oscillator) {
        case 2:
          updateOscillator(i, calculateSineWave());
          break;
        case 3:
          updateOscillator(i, calculate3rdFourier());
          break;
      }
    }
  }
}

int calculateSineWave() {
  return (sin(osc_counter) + 1) * 64;
}

int calculate3rdFourier() {
  // this is a square-ish wave
  return (sin(osc_counter) + 
            ((sin(3 * osc_counter) * 0.33333)) +
            ((sin(5 * osc_counter) * 0.2)) + 1) * 64; 
}

void updateOscillator(byte b, int value) {
  PadButtonState button = pad_buttons[b];
  // Generates one full cycle per second.
  // Will be called every OSC_DELAY,
  Preset pre;
  Patch pat;
  int scaled;
  pre = presets[button.preset];
  osc_counter = osc_counter + OSC_INC;
  for (int i = 0; i <= (PATCH_COUNT - 1); i++) {
    pat = pre.patches[i];
    if (isNotEmptyPatch(pat)) {
      scaled = scaleCC(value, pat.toe_down, pat.toe_up);
      if (scaled != last_cc_values[b][i]) {
        sendCC(button, pat, scaled);
        analogWrite(PULSE_LED, value);
        last_cc_values[b][i] = scaled;
      }
    }
  }
}
