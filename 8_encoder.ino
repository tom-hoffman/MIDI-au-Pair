// presets

// MIDI au Pair
// by Tom Hoffman
// this code from 
// http://practicalusage.com/arduino-using-a-rotary-encoder/

void checkRotary() {
  bouncer.update();
  if ( bouncer.risingEdge()) {
    if (digitalRead(rotary_pin_2)) {
      if (digitalRead(rotary_press) == LOW) {
        updatePreset(1, 1);
      }
      else {
        updatePreset(1, 0); 
      }
    }
    else {
      updatePreset(0, 0);
    }
  } 
}
