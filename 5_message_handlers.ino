// message handlers

// MIDI au Pair
// by Tom Hoffman

void handleCC(byte channel, byte controller, byte value) {
  digitalWrite(PIN_LED_RED, LOW);
  switch (controller) {
    case 11: // expression pedal
      handleExpressionInput(value);
      break;
    case 12: // left button
      handlePadPress(LEFT, value);
      break;
    case 13: // right button
      handlePadPress(RIGHT, value);
      break;
  }
  digitalWrite(PIN_LED_RED, HIGH);
}

void fix_preset(byte side) {
  if (pad_buttons[side].preset == 0) {
    pad_buttons[side].preset = preset_count - 1;
  }
  else { 
    pad_buttons[side].preset = (pad_buttons[side].preset - 1) % preset_count;
  }
  display_buffer[side * 2] = presets[pad_buttons[side].preset].id;
}

void handlePadPress(byte side, byte value) {
  switch (value) {
    case PRESS:
      pad_buttons[side].active = !pad_buttons[side].active;
      firePadButtonState(side);
      updatePadButtonActiveLED(side);
      break;
    case HOLD:
      pad_buttons[side].preset = (pad_buttons[side].preset + 1) % preset_count;
      display_buffer[side * 2] = presets[pad_buttons[side].preset].id;
      writeDisplay();
      break;
    case LONG_HOLD:
      pad_buttons[side].oscillator = (pad_buttons[side].oscillator + 1) % oscillator_count;
      char a[2];
      display_buffer[(side * 2) + 1] = itoa(pad_buttons[side].oscillator, a, 10)[0];
      fix_preset(side);
      writeDisplay();
      break;
  }
}




void handleExpressionInput(byte value) {
  PadButtonState button;
  Preset pre;
  Patch pat;
  int scaled;
  // for each button
  for (int i = 0; i <= 1; i++) {
    button = pad_buttons[i];
    if ((button.active) && (button.oscillator == 1)) {
      pre = presets[button.preset];
      // go through the patches for the preset
      for (int j = 0; j <= (PATCH_COUNT - 1); j++) {
        pat = pre.patches[j];
        if (isNotEmptyPatch(pat)) {
          scaled = scaleCC(value, pat.toe_down, pat.toe_up);
          if (scaled != last_cc_values[i][j]) {
            sendCC(button, pat, scaled);
            last_cc_values[i][j] = scaled;
          }
        }
      }
    }
  }
}

void handleClock() {
  if (quarter_count == 23) {
    digitalWrite(PIN_LED_RED, LOW);
    osc_handler();
    quarter_count = 0;
    digitalWrite(PIN_LED_RED, HIGH);
  }
  quarter_count++;
  last_millis = new_millis;
  new_millis = millis();
  clock_millis = new_millis - last_millis;
}

 
