// midi functions

// MIDI au Pair
// by Tom Hoffman

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
          digitalWrite(PIN_LED_GRN, LOW);
          scaled = scaleCC(value, pat.toe_down, pat.toe_up);
          MIDI.sendControlChange(pat.controller, 
                                 scaled,
                                 getPadChannel(button.pad_number));
          button.cc_value = scaled;
          digitalWrite(PIN_LED_GRN, HIGH);
        }
      }
    }
  }
}

void firePadButtonState(byte side) {
  PadButtonState button = pad_buttons[side];
  Preset preset = presets[button.preset];
  if (button.active) {
    // array is controller/value
    if ((preset.on[0] != 0) && (preset.on[1] != 0)) {
      digitalWrite(PIN_LED_GRN, LOW);
      MIDI.sendControlChange(preset.on[0], preset.on[1], getPadChannel(button.pad_number));
      digitalWrite(PIN_LED_GRN, HIGH);
    }
  }
  else {
    if ((preset.off[0] != 0) && (preset.off[1] != 0)) {
      digitalWrite(PIN_LED_GRN, LOW);
      MIDI.sendControlChange(preset.off[0], preset.off[1], getPadChannel(button.pad_number));  
      digitalWrite(PIN_LED_GRN, HIGH);

    }
  }
}
