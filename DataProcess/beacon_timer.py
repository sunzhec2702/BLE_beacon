import threading
import time

class BeaconTimer(threading.Thread):  # The timer class is derived from the class threading.Thread
    def __init__(self, num, interval, callback):
        threading.Thread.__init__(self)
        self.thread_num = num
        self.interval = interval
        self.thread_stop = False
        self.callback = callback

    def run(self):  # Overwrite run() method, put what you want the thread do here
        while not self.thread_stop:
            self.callback()
            time.sleep(self.interval)

    def stop(self):
        self.thread_stop = True