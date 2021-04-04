import xml.etree.ElementTree as ET
import mido

# MIDI au Pair
# by Tom Hoffman


print("Output ports:")
print(mido.get_output_names())

TEST_PORT = 'UM-ONE:UM-ONE MIDI 1 28:0'
MAP_CHANNEL = 14 # seems to be -1?
MANUFACTURER_ID = 58 # Atari!

data = []
presets = 0

tree = ET.parse("map.xml")
config = tree.getroot()
patch_count = 4
for preset in config:
    data.append(ord(preset.attrib['id']))
    # order has to be patches, on, off
    patches = preset[0]
    if patches.tag != 'patches':
        raise Exception("Preset out of order")
    count = 0
    empty_patches = [0] * (3 * patch_count)
    for patch in patches:
        empty_patches[count] = int(patch.attrib['controller'])
        count += 1
        empty_patches[count] = int(patch.attrib['toe_up'])
        count += 1
        empty_patches[count] = int(patch.attrib['toe_down'])
        count += 1
    data = data + empty_patches
    try:
        on = preset[1]
        data.append(int(on.attrib['controller']))
        data.append(int(on.attrib['value']))
    except:
        data = data + [0, 0]
    try:
        off = preset[2]
        data.append(int(off.attrib['controller']))
        data.append(int(off.attrib['value']))
    except:
        data = data + [0, 0]
    presets += 1
predicted_count = (presets * 5) + (presets * patch_count * 3) + 2
data = [58, predicted_count] + data
if predicted_count == len(data):
    data[1] = data[1] + 2  # adjust for start and end bytes.
    msg = mido.Message('sysex', data=data)
    with mido.open_output(TEST_PORT) as port:
        port.send(msg)
        print(len(msg.bytes()))
        print("Message sent.")
else:
    raise Exception("Message length is off.")
