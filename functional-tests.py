import time
import mido

# Test suite for 

print("Input ports:")
print(mido.get_input_names())
print("Output ports:")
print(mido.get_output_names())

TEST_PORT = 'UM-ONE:UM-ONE MIDI 1 28:0'
MIDI_BABY_CHANNEL = 14 # seems to be -1?

with mido.open_ioport(TEST_PORT) as port:
    print("Simulating MIDI Baby Right Button Press")
    port.send(mido.Message('control_change', channel=14, control=13, value=0))



# print('Update %d' % i, end='\r')