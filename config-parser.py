import xml.etree.ElementTree as ET
import mido

data = []

tree = ET.parse("map.xml")
config = tree.getroot()
patch_count = int(config.attrib['patch_count'])
data.append(patch_count)
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
        
    
                
                
    

print(data)