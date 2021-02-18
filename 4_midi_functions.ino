// midi functions

// MIDI au Pair
// by Tom Hoffman

void handleExpressionInput(byte value) {
  PadButtonState button;
  Preset pre;
  byte pre_index;
  Patch pat;
  // for each button
  for (int i = 0; i <= 1; i++) {
    // get the button
    button = pad_buttons[i];
    // check to see if it is active and set to use the foot "oscillator"
    if ((button.active) && (button.oscillator == 1)) {
      // button.preset is a byte.  
      pre_index = button.preset;
      // get the preset for that index...
      pre = presets[pre_index];
      // go through the patches for the preset
      for (int j = 0; j <= (PATCH_COUNT - 1); j++) {
        // check to see if the patch is empty
        if ((pat.controller != 0) || (pat.toe_down != 0) || (pat.toe_up != 0)) {
          digitalWrite(PIN_LED_GRN, LOW);
          pat = pre.patches[j];
          MIDI.sendControlChange(pat.controller, value, 
                                 getPadChannel(button.pad_number));
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
