MIDI au Pair Notes
==================

Arduino Pin Usage
-----------------

### SparkFun MIDI Shield


Hardware Serial -> MIDI IN/OUT
* LED's -> D6, D7
* Buttons -> D2, D3, D4
* Pots -> A0, A1

### Adafruit Alphanumeric Backpack

* Clock -> A5
* Data -> A4

### Indicator LED's

* Left -> D11
* Right -> D12

MIDI Counting Notes:
--------------------

MIDI Channels seem consistent across all 3 devices, 1-16?
ND Displays program value +1

Code Organization
-----------------

I'm a C++ novice, so I'm just using the Arduino IDE tab system to divide up the code. I'm using numbers in the filename to control the loading order, although I don't know if that really matters in this case.
