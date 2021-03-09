// oscillators

// MIDI au Pair
// by Tom Hoffman



void second_sine_oscillator(byte b) {
  PadButtonState button = pad_buttons[b];
  // Generates one full cycle per second.
  // Will be called every OSC_DELAY,
  Preset pre;
  Patch pat;
  int value;
  int scaled;
  pre = presets[button.preset];
  value = (sin(osc_counter) + 1) * 64;
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
          second_sine_oscillator(i);
          break;
      }
    }
  }
}
