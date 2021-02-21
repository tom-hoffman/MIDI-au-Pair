MIDI au Pair
============

This is a personal project to create an Arduino middleware device which sits between a [Disaster Area Designs MIDI Baby 3](https://www.disasterareadesigns.com/shop/p/midi-baby-3) and a [Nord Drum 3p](https://www.nordkeyboards.com/products/nord-drum-3p) in the DIN MIDI chain. 

Since this is all MIDI, nothing is exclusive to the Nord Drum 3p, or the MIDI Baby, as such, but it is written with this configuration in mind. In particular managing a set of presets each of which take one CC stream in and output several CC's based on the input values.

The main use case is to allow hi-hat style control of the output of a pad on the Nord Drum 3p. The MIDI Baby 3 (or a single MIDI Baby) does this nicely with an attached expression pedal. The MIDI Baby's web editor allows you to sweep through multiple parameters in specified ranges while manipulating the expression pedal. If that's what you're looking for, you may only need a MIDI Baby and expression pedal.

With that setup, when you lift your toe on the pedal, not only can you increase the decay time of the hi-hat sound, you can change the resonance and spectra of the sound to make the tone more "open" in a way that is satisfying and dynamic, if not literally realistic (like the Nord Drum tones in general). 

The only "problem" with this arrangement is that it is hard not to think about what else could be added. Presets would be nice, so you could switch between different sets of effects controlled by the pedal, e.g., getting a wah effect by sweeping the parametric eq. Maybe something that would sync the MIDI Baby's clock signal with the Nord Drum's delay parameter. How about some LFO's to modulate parameters on it own. It isn't hard to think of more features!

The MIDI au Pair is designed to sit between the MIDI Baby 3 and the Nord Drum 3p in the MIDI chain. I experimented with incorporating USB MIDI into this, but found just using old fashioned DIN MIDI to be most straightforward. 

In my configuration, the MIDI Baby 3 gives me a nice solid enclosure for three footswitches and an expression pedal. That still leaves an additional "multi-jack" which can add another external double footswitch or another expression pedal. 

In theory the MIDI Baby's microcontroller could probably just be reprogrammed directly, but I don't have the background to dive down that rabbit hole. Alternately, this also could be done by connecting proper footswitches and an expression pedal directly to an Arduino, but since I already had the well constructed MIDI Baby 3, and I'm terrible with hardware construction, I built this around the MIDI Baby. For the record, for less than the cost of all the parts that go into this, including a pedal board and proper power supply, you could just get a [cheap MIDI foot controller](https://www.sweetwater.com/store/detail/FCB1010--behringer-midi-foot-controller-fcb1010), which might(?) be as good or better for this task.

The development hardware I'm using for this project is:

 * [Arduino Uno](https://store.arduino.cc/usa/arduino-uno-rev3)
 * [Sparkfun MIDI Shield](https://www.sparkfun.com/products/12898)
 * [Adafruit Alphanumeric Backpack](https://learn.adafruit.com/adafruit-led-backpack/0-54-alphanumeric)
 * a few LED's connected to D11 & D12.
 
Libraries
---------

* [47 Effects MIDI Library](https://github.com/FortySevenEffects/arduino_midi_library)
