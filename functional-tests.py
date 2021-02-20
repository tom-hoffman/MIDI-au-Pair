import time
import mido

# Test suite for 

print("Input ports:")
print(mido.get_input_names())
print("Output ports:")
print(mido.get_output_names())

TEST_PORT = 'UM-ONE:UM-ONE MIDI 1 28:0'
MAP_CHANNEL = 14 # seems to be -1?
LEFT_BUTTON = 12
RIGHT_BUTTON = 13
EX_PEDAL = 11

with mido.open_ioport(TEST_PORT) as port:
    print("Simulating MIDI Baby Left Button Press...")
    port.send(mido.Message('control_change', channel=MAP_CHANNEL,
                           control=LEFT_BUTTON, value=0))
#     print("Simulating MIDI Baby Right Button Press...")
#     port.send(mido.Message('control_change', channel=MAP_CHANNEL,
#                            control=RIGHT_BUTTON, value=0))

    time.sleep(1)
    print("Simulating stream of CC values from expression pedal.")
    print("From heel-down to toe-down.")
    for i in range(128):
        port.send(mido.Message('control_change', channel=MAP_CHANNEL,
                               control=EX_PEDAL, value=i))
        time.sleep(0.1)
        msg = port.poll()
        while (msg != None):
            print(msg)
            time.sleep(0.2)
            msg = port.poll()
        print('Sending value %d... Recieved %d.' % (i, msg.value), end='\r')
        
        time.sleep(0.1)
    
    print("Simulating MIDI Baby Left Button Press...")
    port.send(mido.Message('control_change', channel=MAP_CHANNEL,
                           control=LEFT_BUTTON, value=0))
    
#     print("Simulating MIDI Baby Right Button Press...")
#     port.send(mido.Message('control_change', channel=MAP_CHANNEL,
#                            control=RIGHT_BUTTON, value=0))

