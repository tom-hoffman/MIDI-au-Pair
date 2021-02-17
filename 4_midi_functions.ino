// midi functions

// MIDI au Pair
// by Tom Hoffman

void firePadButtonState(byte side) {
  digitalWrite(PIN_LED_GRN, LOW);
  PadButtonState button = pad_buttons[side];
  Preset preset = presets[button.preset];
  if (button.active) {
    // fire the on message
    // array is controller/value
    if ((preset.on[0] != 0) && (preset.on[1] != 0)) {
      MIDI.sendControlChange(preset.on[0], preset.on[1], getPadChannel(button.pad_number));
    }
  }
  else {
    if ((preset.off[0] != 0) && (preset.off[1] != 0)) {
      MIDI.sendControlChange(preset.off[0], preset.off[1], getPadChannel(button.pad_number));  
    }
  }
  digitalWrite(PIN_LED_GRN, HIGH);

}
