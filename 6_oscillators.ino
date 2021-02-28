// oscillators

// MIDI au Pair
// by Tom Hoffman

void second_sine_oscillator(byte b) {
  PadButtonState button = pad_buttons[b];
  // Generates one full cycle per second.
  // Will be called every OSC_DELAY,
  // so it should increment at (twoPI / (1000 / OSC_DELAY))
  // This will be called once every OSC_DELAY
  // IF one of the buttons is using it.
  // This will calculate a new value based on 
  // the sine function and osc_counter, and
  // IF THAT VALUE IS DIFFERENT from the old
  // CC value, it will spit a CC message.
  // AT THAT POINT IT DOES THE SAME AS A EXP. PEDAL 
  // CC EVENT.
  Preset pre;
  Patch pat;
  int value;
  pre = presets[button.preset];
  value = (sin(osc_counter) + 1) * 64;
  osc_counter = osc_counter + OSC_INC;
  for (int i = 0; i <= (PATCH_COUNT - 1); i++) {
    pat = pre.patches[i];
    if (isNotEmptyPatch(pat)) {
      sendCC(button, pat, value);
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
