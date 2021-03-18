import time
import mido

# Reads incoming message from MIDI au Pair.
# Playing the role of the Nord Drum in this test.

print("Input ports:")
print(mido.get_input_names())
print("Output ports:")
print(mido.get_output_names())

TEST_PORT = 'UM-ONE:UM-ONE MIDI 1 20:0'
MAP_CHANNEL = 14 # seems to be -1?
LEFT_MAP_PAD = 2
RIGHT_MAP_PAD = 5


cc = [0, 0]

# test on/off messages

with mido.open_input(TEST_PORT) as port:
    print("Listening on channels 3 (left) and 6 (right):")
    for msg in port:
        if (msg.type == 'control_change'):
            if (msg.channel == LEFT_MAP_PAD):
                cc[0] = msg.value
                print(f"Left: {cc[0]}, Right: {cc[1]}")
            elif (msg.channel == RIGHT_MAP_PAD):
                cc[1] = msg.value
                print(f"Left: {cc[0]}, Right: {cc[1]}")
