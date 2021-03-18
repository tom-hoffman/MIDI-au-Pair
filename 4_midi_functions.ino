// midi functions

// MIDI au Pair
// by Tom Hoffman

void sendCC(PadButtonState b, Patch p, byte scaled) {
  digitalWrite(PIN_LED_GRN, LOW);  
  MIDI.sendControlChange(p.controller, 
                         scaled,
                         b.pad_number);
  digitalWrite(PIN_LED_GRN, HIGH);  
}

void firePadButtonState(byte side) {
  PadButtonState button = pad_buttons[side];
  Preset preset = presets[button.preset];
  if (button.active) {
    // array is controller/value
    if ((preset.on[0] != 0) && (preset.on[1] != 0)) {
      digitalWrite(PIN_LED_GRN, LOW);
      MIDI.sendControlChange(preset.on[0], preset.on[1], button.pad_number);
      digitalWrite(PIN_LED_GRN, HIGH);
    }
  }
  else {
    if ((preset.off[0] != 0) && (preset.off[1] != 0)) {
      digitalWrite(PIN_LED_GRN, LOW);
      MIDI.sendControlChange(preset.off[0], preset.off[1], button.pad_number);  
      digitalWrite(PIN_LED_GRN, HIGH);

    }
  }
}
