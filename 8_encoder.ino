// presets

// MIDI au Pair
// by Tom Hoffman
// this code from 
// http://practicalusage.com/arduino-using-a-rotary-encoder/

void checkRotary() {
  bouncer.update();
  if (bouncer.risingEdge()) {
    byte side = digitalRead(SIDE_SWITCH);
    byte knob_press = digitalRead(ROTARY_PRESS);
    byte dir = digitalRead(ROTARY_PIN_2);
    if (dir == 0) {
      dir = -1;
    }
    if (knob_press == HIGH) {
      changePreset(side, dir);
    }
    else {
      changeOscillator(side, dir);
    }
  }
}
