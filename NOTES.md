MIDI au Pair Notes
==================

TODO
----

* test encoder press
* fix memory
* sync clock for real
* hi-hat close

Size of Things
--------------

Currently set to:

* 16 presets
* 4 patches per preset
* each patch controls one CC value

Probably this can be expanded within the constraints of the 
Arduino UNO with no extreme measures, but we'll see.

Arduino Pin Usage
-----------------

### SparkFun MIDI Shield


Hardware Serial -> MIDI IN/OUT
* LED's -> D6, D7
* Buttons -> D2, D3, D4 (not in final version)
* Pots -> A0, A1 (not in final version)

### Adafruit Alphanumeric Backpack

* Clock -> A5
* Data -> A4

### Indicator LED's

* Left -> D8
* Right -> D9
* Pulse -> D5

### Adafruit SPI FRAM

* SCK -> D13
* MISO -> D12
* MOSI -> D11 
* CS -> D10

### Adafruit Rotary Encoder


* A -> D2
* B -> D3
* Switch -> D4


MIDI Counting Notes:
--------------------

MIDI Channels seem consistent across all 3 devices, 1-16?
Mido (Python) does MIDI channels 0-15 (-1).
ND Displays program value +1

Code Organization
-----------------

I'm a C++ novice, so I'm just using the Arduino IDE tab system to divide up the code. I'm using numbers in the filename to control the loading order, although I don't know if that really matters in this case.

Calculating Waves on the Fly
----------------------------

If it is possible from a performance perspective to use trig to calculate waveforms on the fly, I will, because I'm a high school computer science teacher.

SysEx Format
------------

byte 1 -> 58 (Manufacturer ID for Atari)
byte 2 -> length of body of message
byte 3... stream of presets.

FRAM Documentation
------------------

https://learn.adafruit.com/adafruit-spi-fram-breakout


//Preset presets[preset_count] = {
//  {'-',  {{}}, {1, 64}, {1, 1}},
//  // "H" is a natural-ish hi-hat open/close dynamic.
//  {'H', {{17, 64, 0}, {30, 0, 126}, {21, 70, 16}, {50, 70, 16}}, {0, 0}, {0, 0}},
//
//  // "W" is a wah-wah effect sweeping the parametric eq.
//  {'W', {{25, 0, 127}}, {26, 64}, {26, 0}},
//  // "T" is a test preset just sweeping controller 1 from 0 to 127. 
//  {'T', {{1, 0, 127}}, {0, 0}, {0, 0}},
//  // "t" is a test preset sweeping controller 2 from 126 to 0
//  {'t', {{2, 126, 0}}, {0, 0}, {0, 0}},
//};
