// display functions

// MIDI au Pair
// by Tom Hoffman

void resetDisplay() {
  for (int i = 0; i < 2; i++) {
    display_buffer[i * 2] = presets[pad_buttons[i].preset].id;
    char a[2];
    display_buffer[(i * 2) + 1] = itoa(pad_buttons[i].oscillator, a, 10)[0];
    writeDisplay();
  }
}

void flashLEDs(int v) { 
  for (int i = 0; i < 2; i++) {
    digitalWrite(BUTTON_LEDS[i], v);
  }
  digitalWrite(PULSE_LED, v);
}

void readyDisplay() {
  // flash and pause on boot
  flashLEDs(HIGH);
  delay(1000);
  flashLEDs(LOW);
}

void writeDisplay() {
  for (int i = 0; i < 4; i++) {
    alpha4.writeDigitAscii(i, display_buffer[i]);
  }
  alpha4.writeDisplay();
}

void displayByte(byte b) {
  // for debugging
  // displays exact value of a byte in hex, right justified.
  char a[2];
  itoa(b, a, 16); // converting 
  if (b <= 15) {
    display_buffer[2] = '0';
    display_buffer[3] = a[0];
  }
  else {
    display_buffer[2] = a[0];
    display_buffer[3] = a[1];
  }
  writeDisplay();
}

void updatePadButtonActiveLED(byte side) {
  if (pad_buttons[side].active) {
    digitalWrite(BUTTON_LEDS[side], HIGH);
  }
  else {
    digitalWrite(BUTTON_LEDS[side], LOW);
  }
}
