import struct
from threading import Thread

import serial
import time
import multiprocessing


class StationSerial(object):
    serial_instance = None
    current_stage = 0
    online_beacon = set()
    beacon_info = dict()
    tx_power = 0
    record_file = None
    record = False
    record_file_path = None
    communicate_state = False
    communicate_thread = None

    rssiNumber = 0
    rssiAverage = 0

    def __init__(self, COM, tx_power = -51, record = False, file_path = None):
        self.serial_instance = serial.Serial(COM, 115200)
        self.current_stage = 0
        self.tx_power = tx_power
        self.record = record
        self.record_file_path = file_path

    def __del__(self):
        self.record_file.close()

    def sync_from_serial(self):
        magic_raw = self.serial_instance.read(1)
        magic, = struct.unpack("<B", magic_raw)
        if self.current_stage == 0 and magic == 0xDE:
            self.current_stage = 1
            return self.current_stage
        elif self.current_stage == 1 and magic == 0xAD:
            self.current_stage = 2
            return self.current_stage
        elif self.current_stage == 2 and magic == 0xBE:
            self.current_stage = 3
            return self.current_stage
        elif self.current_stage == 3 and magic == 0xAF:
            self.current_stage = 0
            packet_raw = self.serial_instance.read(40)
            self.process_packet(packet_raw)
        elif self.current_stage != 0 and magic == 0xDE:
            self.current_stage = 1
            return self.current_stage
        else:
            self.current_stage = 0
            return self.current_stage

    def process_packet(self, packet):
        if (len(packet) != 40):
            return False
        packet_data = []
        for i in range(len(packet)):
            packet_data.append(hex(packet[i]))
        addr = packet_data[1:7]
        rssi = packet_data[7]
        rssi = int(rssi, 16) - 256
        print(rssi)
        self.rssiAverage += rssi
        self.rssiNumber += 1
        print(self.rssiAverage / self.rssiNumber)
        adv_data = packet_data[9:40]
        addr_str = (''.join(addr))
        hour_left = adv_data[25]
        index = adv_data[26]
        flags = adv_data[27]
        battery = adv_data[28]
        self.online_beacon.add(addr_str)
        info = [int(time.time()), self.rssi_to_distance(rssi), rssi, int(hour_left, 16), int(index, 16), flags, int(battery, 16)]
        self.beacon_info[addr_str] = info
        if self.record_file is not None:
            self.record_file.write(str(info))
            self.record_file.write('\n')
        return

    def rssi_to_distance(self, rssi):
        distance = 10 ** ((self.tx_power - rssi) / 20)
        return distance

    def communicate_thread_func(self):
        while(self.communicate_state is True):
            self.sync_from_serial()

    def start_communication(self):
        if self.record is True and self.record_file_path is not None:
            self.record_file = open(self.record_file_path, 'a')
        self.communicate_state = True
        self.communicate_thread = Thread(target=self.communicate_thread_func)
        self.communicate_thread.start()

    def stop_communication(self):
        self.communicate_state = False
        self.communicate_thread.join()

