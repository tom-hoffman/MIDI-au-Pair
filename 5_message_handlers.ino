// message handlers

// MIDI au Pair
// by Tom Hoffman

void handleCC(byte channel, byte controller, byte value) {
  #ifdef DEBUG
    digitalWrite(PIN_LED_RED, LOW);
  #endif
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
  #ifdef DEBUG
    digitalWrite(PIN_LED_RED, HIGH);
  #endif
}

void handlePadPress(byte side, byte value) {
  switch (value) {
    case PRESS:
      pad_buttons[side].active = !pad_buttons[side].active;
      firePadButtonState(side);
      updatePadButtonActiveLED(side);      
      break;
    case HOLD:
      changePreset(side, 1);
      break;
    case LONG_HOLD:
      changeOscillator(side, 1);
      changePreset(side, -1);
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
    #ifdef DEBUG
      digitalWrite(PIN_LED_RED, LOW);
    #endif
    osc_handler();
    quarter_count = 0;
    #ifdef DEBUG
      digitalWrite(PIN_LED_RED, HIGH);
    #endif
  }
  quarter_count++;
  last_millis = new_millis;
  new_millis = millis();
  clock_millis = new_millis - last_millis;
  // The multiplier is based on eyeball testing.
  OSC_INC = twoPI / ((clock_millis * 26) / OSC_DELAY);        
}

void handleSysex(byte *a, unsigned int len) {
  // this should write to FRAM and 
  // then rebuild the presets.
  if (*(a + 1) == 58) {
    buildPresets(a);
    writePresetstoFRAM(a, len);
    resetDisplay();
  }
}
