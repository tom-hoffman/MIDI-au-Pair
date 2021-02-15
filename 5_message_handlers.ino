void handleCC(byte channel, byte controller, byte value) {
  digitalWrite(PIN_LED_RED, LOW);
  switch (controller) {
    case 12:
      handlePadPress(LEFT, value);
      break;
    case 13:
      handlePadPress(RIGHT, value);
      break;
  }
  digitalWrite(PIN_LED_RED, HIGH);
}

void handlePadPress(byte side, byte value) {
  switch (value) {
    case HOLD:
      pad_buttons[side].preset = incrementPreset(pad_buttons[side].preset);
      displayPadButtonState(side);
      alpha4.writeDisplay();
  }
}
