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

void handlePadPress(byte side, byte value) {
  switch (value) {
    case PRESS:
      pad_buttons[side].active = !pad_buttons[side].active;
      firePadButtonState(side);
      updatePadButtonActiveLED(side);
      break;
    case HOLD:
      pad_buttons[side].preset = incrementPreset(pad_buttons[side].preset);
      updatePadButtonPreset(side);
      alpha4.writeDisplay();
      break;
  }
}

void handleClock() {
  if (quarter_count == 23) {
    digitalWrite(PIN_LED_RED, LOW);
    quarter_count = 0;
    digitalWrite(PIN_LED_RED, HIGH);
  }
  quarter_count++;
  last_millis = new_millis;
  new_millis = millis();
  clock_millis = new_millis - last_millis;
}

 
