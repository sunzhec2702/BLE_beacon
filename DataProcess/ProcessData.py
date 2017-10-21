import struct
import threading
import time
import serial
#import PyQt4
from pip._vendor.six import byte2int

DATA = set()
INFO = dict()
CNT = dict()
serial_instance = serial.Serial('COM12', 115200)


class timer(threading.Thread):  # The timer class is derived from the class threading.Thread
    def __init__(self, num, interval):
        threading.Thread.__init__(self)
        self.thread_num = num
        self.interval = interval
        self.thread_stop = False

    def run(self):  # Overwrite run() method, put what you want the thread do here
        while not self.thread_stop:
            if (self.thread_num == 1):
                print("Number %d" % len(DATA))
            else:
                print(CNT.values())
            #print
            #'Thread Object(%d), Time:%s\n' % (self.thread_num, time.ctime())
            time.sleep(self.interval)

    def stop(self):
        self.thread_stop = True

def process_packet(packet):
    if (len(packet) != 40):
        return False
    packet_data = []
    for i in range(len(packet)):
        packet_data.append(hex(packet[i]))
    addr = packet_data[1:7]
    rssi = packet_data[7]
    adv_data = packet_data[9:40]
    addr_str = (''.join(addr))
    major_1 = adv_data[25]
    major_2 = adv_data[26]
    minor_1 = adv_data[27]
    minor_2 = adv_data[28]
    DATA.add(addr_str)
    info = [rssi, major_1, major_2, minor_1, minor_2]
    INFO[addr_str] = info
    if (CNT.get(addr_str)):
        CNT[addr_str] += 1
    else:
        CNT[addr_str] = 1
    return addr, rssi, major_1, major_2, minor_1, minor_2

sync_stage = 0

thread1 = timer(1, 20)
thread1.start()
thread2 = timer(2, 1)
thread2.start()
while(1):
    magic_raw  = serial_instance.read(1)
    magic, = struct.unpack("<B", magic_raw)
    if sync_stage == 0 and magic == 0xDE:
        sync_stage = 1
        continue
    elif sync_stage == 1 and magic == 0xAD:
        sync_stage = 2
        continue
    elif sync_stage == 2 and magic == 0xBE:
        sync_stage = 3
        continue
    elif sync_stage == 3 and magic == 0xAF:
        sync_stage = 0
        packet_raw = serial_instance.read(40)
        process_packet(packet_raw)
    elif sync_stage != 0 and magic == 0xDE:
        sync_stage = 1
        continue
    else:
        sync_stage = 0

'''
def show_adv_info():
    return







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
'''