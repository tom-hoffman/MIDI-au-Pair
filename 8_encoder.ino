// presets

// MIDI au Pair
// by Tom Hoffman
// this code from 
// http://practicalusage.com/arduino-using-a-rotary-encoder/

void checkRotary() {
  bouncer.update();
  if (bouncer.risingEdge()) {
    byte side = digitalRead(SIDE_SWITCH);
    if (digitalRead(ROTARY_PIN_2) == HIGH) {
        changePreset(1, 1);
    }
    else {
      changePreset(1, -1);
    }
  } 
}
