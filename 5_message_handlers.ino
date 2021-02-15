void handleCC(byte channel, byte controller, byte value) {
  digitalWrite(PIN_LED_RED, LOW);
  switch (controller) {
    case 12:
      handleLeftPress(value);
      break;
    case 13:
      handleRightPress(value);
      break;
  }
  digitalWrite(PIN_LED_RED, HIGH);
}

void handleLeftPress(byte value) {
  switch (value) {
    case HOLD:
      left_button.preset = incrementPreset(left_button.preset);
      displayButtonStatus(left_button, 'l');
      alpha4.writeDisplay();
      break;
  }
}

void handleRightPress(byte value) {
  switch (value) {
    case HOLD:
      right_button.preset = incrementPreset(right_button.preset);
      displayButtonStatus(right_button, 'r');
      alpha4.writeDisplay();
      break;
  }
}
