from beacon_timer import BeaconTimer
from SerialCommunication import StationSerial
import time
# thread1 = BeaconTimer(1,0.5, cb)
# thread1.start()
# thread2 = timer(2, 0.5)
# thread2.start()


if __name__ == '__main__':
    station1 = StationSerial("COM3", tx_power=-51, record=True,file_path='F:\PersonalProject\BLE-CC2541\BLE_Meeting\DataProcess\\temp.txt')
    station1.start_communication()
    time.sleep(60)
    station1.stop_communication()

