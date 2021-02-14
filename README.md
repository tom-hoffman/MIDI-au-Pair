MIDI au Pair
============

This is a personal project to create an Arduino middleware device which sits between a [Disaster Area Designs MIDI Baby 3](https://www.disasterareadesigns.com/shop/p/midi-baby-3) and a Nord Drum 3p in the DIN MIDI chain. 

The main use case is to allow hi-hat style control of the output of a pad on the Nord Drum 3p.  The MIDI Baby 3 (or a single MIDI Baby) does this nicely with an attached expression pedal. The MIDI Baby's web editor allows you to sweep through multiple parameters in specified ranges while manipulating the expression pedal. 

When you lift your toe on the pedal, not only can you increase the decay of the hi-hat sound, you can change the resonance and spectra of the sound to make the tone more "open" in a way that is satisfying and dynamic, if not literally realistic (like the Nord Drum tones in general). 

In my configuration, the MIDI Baby 3 gives me a nice solid enclosure for three footswitches and an expression pedal. That still leaves an additional "multi-jack" which can add another external double footswitch or another expression pedal. In theory the MIDI Baby's microcontroller could probably just be reprogrammed directly, but I don't have the background to dive down that rabbit hole.

The development hardware I'm using for this project is:

 * Arduino Uno
 * Sparkfun MIDI Shield
 * Adafruit Alphanumeric Backpack
 

