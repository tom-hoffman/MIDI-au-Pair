// utility functions

void writeDisplay() {
  for(int i=0; i<4; i++) {
    alpha4.writeDigitAscii(i, display_buffer[i]);
  }
  alpha4.writeDisplay();
}

void displayByte(byte b) {
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

void displayPadButtonState(byte side) {
  PadButtonState B = pad_buttons[side];
  char t[3];
  int i;
  strcpy(t, presets[B.preset].id);
  i = side * 2;
  display_buffer[i] = t[0];
  display_buffer[i+1] = t[1];
  writeDisplay();
}

int incrementPreset(byte current_preset) {
  if (current_preset < (preset_count - 1)) {
    return (current_preset + 1);
  }
  else {
    return 0;
  }
}
