// midi functions

// MIDI au Pair
// by Tom Hoffman

void sendCC(PadButtonState b, Patch p, byte scaled) {
  digitalWrite(PIN_LED_GRN, LOW);  
  MIDI.sendControlChange(p.controller, 
                         scaled,
                         getPadChannel(b.pad_number));
  digitalWrite(PIN_LED_GRN, HIGH);  
}

void checkCCChange(byte b, Patch pat, byte value) {
  int scaled;
  PadButtonState button = pad_buttons[b];
  scaled = scaleCC(value, pat.toe_down, pat.toe_up);
  if (scaled != last_cc_values[b]) {
    sendCC(button, pat, scaled);
    analogWrite(PULSE_LED, value);
    last_cc_values[b] = scaled;
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
