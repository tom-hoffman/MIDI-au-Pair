// oscillators

// MIDI au Pair
// by Tom Hoffman

void second_sine_oscillator(byte b) {
  PadButtonState button = pad_buttons[b];
  // This will be called once every osc_delay
  // IF one of the buttons is using it.
  // This will calculate a new value based on 
  // the sine function and osc_counter, and
  // IF THAT VALUE IS DIFFERENT from the old
  // CC value, it will spit a CC message.
  
}

void osc_handler() {
  PadButtonState button;
  // for each button
  for (int i = 0; i <= 1; i++) {
    // get the button
    button = pad_buttons[i];
    // check to see if it is active
    if (button.active) {
      switch (button.oscillator) {
        case 2:
          second_sine_oscillator(i);
          break;
      }
    }
  }
}

//    && (button.oscillator == 1)) {
//      // button.preset is a byte.  
//      pre_index = button.preset;
//      // get the preset for that index...
//      pre = presets[pre_index];
//      // go through the patches for the preset
//      for (int j = 0; j <= (PATCH_COUNT - 1); j++) {
//        // check to see if the patch is empty
//        if ((pat.controller != 0) || (pat.toe_down != 0) || (pat.toe_up != 0)) {
//          digitalWrite(PIN_LED_GRN, LOW);
//          pat = pre.patches[j];
//          scaled = scaleCC(value, pat.toe_down, pat.toe_up);
//          MIDI.sendControlChange(pat.controller, 
//                                 scaled,
//                                 getPadChannel(button.pad_number));
//          digitalWrite(PIN_LED_GRN, HIGH);
//        }
//      }
//    }
//  }
//}}
