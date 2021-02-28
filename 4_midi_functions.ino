// midi functions

// MIDI au Pair
// by Tom Hoffman

void sendCC(PadButtonState b, Patch p, byte value) {
  digitalWrite(PIN_LED_GRN, LOW);
  int scaled = scaleCC(value, p.toe_down, p.toe_up);
  MIDI.sendControlChange(p.controller, 
                         scaled,
                         getPadChannel(b.pad_number));
  b.cc_value = scaled;  // this might not work
  digitalWrite(PIN_LED_GRN, HIGH); 
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
          sendCC(button, pat, value);
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
