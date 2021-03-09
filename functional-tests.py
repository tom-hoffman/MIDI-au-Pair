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
    time.sleep(1)
    cc_return = {30:0, 17:0, 50:0, 21:0}

    for msg in port.iter_pending():
        cc_return[msg.control] = msg.value


    print("Simulating stream of CC values from expression pedal.")
    print("From heel-down to toe-down.")
    for i in range(128):
        port.send(mido.Message('control_change', channel=MAP_CHANNEL,
                               control=EX_PEDAL, value=i))
        for msg in port.iter_pending():
            cc_return[msg.control] = msg.value
        print(f"i: {i}, Spec: {cc_return[30]}, Res:{cc_return[17]}, TDec: {cc_return[50]}, NDec: {cc_return[21]}")
        time.sleep(0.05)

    time.sleep(1)
    print("Simulating MIDI Baby Left Button Press...")
    port.send(mido.Message('control_change', channel=MAP_CHANNEL,
                           control=LEFT_BUTTON, value=0))
    
    time.sleep(1)
    
    print("Simulating MIDI Baby Right Button Hold...")
    port.send(mido.Message('control_change', channel=MAP_CHANNEL,
                           control=RIGHT_BUTTON, value=1))
    print("Simulating MIDI Baby Right Button Hold...")
    port.send(mido.Message('control_change', channel=MAP_CHANNEL,
                           control=RIGHT_BUTTON, value=1))
    print("Simulating MIDI Baby Right Button Hold...")
    port.send(mido.Message('control_change', channel=MAP_CHANNEL,
                           control=RIGHT_BUTTON, value=1))
    print("Simulating MIDI Baby Right Button Long Hold...")
    port.send(mido.Message('control_change', channel=MAP_CHANNEL,
                           control=RIGHT_BUTTON, value=2))
    print("Starting right side with oscillator 2.")
    print("Simulating MIDI Baby Right Button Press...")
    port.send(mido.Message('control_change', channel=MAP_CHANNEL,
                           control=RIGHT_BUTTON, value=0))
    for msg in port:
        cc_return[msg.control] = msg.value
        print(f"Spec: {cc_return[30]}, Res:{cc_return[17]}, TDec: {cc_return[50]}, NDec: {cc_return[21]}")
