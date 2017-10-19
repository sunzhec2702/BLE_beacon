import serial
#import PyQt4

DATA = set()
INFO = dict()
serial_instance = serial.Serial('COM1', 115200)
while(1):
    magic = serial_instance.read(1)
    if (magic == 0xDE):


def serial_read_packet(serial_instance):
    serial_instance.read(1)

def process_packet(packet):
    if (len(packet) != 41):
        return False
    addr = packet[5:11]
    rssi = packet[11]
    adv_data = packet[13:42]
    major_1 = adv_data[25]
    major_2 = adv_data[26]
    minor_1 = adv_data[27]
    minor_2 = adv_data[28]
    DATA.add(addr)
    info = [rssi, major_1, major_2, minor_1, minor_2]
    INFO[''.join(map(str, addr))] = info
    return addr, rssi, major_1, major_2, minor_1, minor_2

def show_adv_info():







FILE_NAME = "E:\PersonalProject\BLE-CC2541\BLE_Meeting\DataProcess\datas.txt"








file = open(FILE_NAME, 'r')
while(1):
    data = file.read(132)
    print(data)
    if (len(data) == 0):
        break;
    addr = data[15:32]
    DATA.add(addr)
file.close()
print(DATA)
print(len(DATA))