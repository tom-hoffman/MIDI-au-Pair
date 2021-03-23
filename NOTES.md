MIDI au Pair Notes
==================

TODO
----

* hi-hat close
* char labels for oscillators
* square oscillator
* sysex format

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

* Left -> D11 (need to move for FRAM) 
* Right -> D12 (need to move for FRAM)
* Pulse -> D5

### Adafruit SPI FRAM

* SCK -> D13
* MISO -> D12
* MOSI -> D11 
* CS -> D10

### Adafruit Rotary Encoder
* 3 digital pins each.

MIDI Counting Notes:
--------------------

MIDI Channels seem consistent across all 3 devices, 1-16?
Mido (Python) does MIDI channels 0-15 (-1).
ND Displays program value +1

Code Organization
-----------------

I'm a C++ novice, so I'm just using the Arduino IDE tab system to divide up the code. I'm using numbers in the filename to control the loading order, although I don't know if that really matters in this case.

FRAM Documentation
------------------

https://learn.adafruit.com/adafruit-spi-fram-breakout

