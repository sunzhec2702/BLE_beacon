import multiprocessing
import time

class Test(object):
    flag = False
    process = None
    def __init__(self):
        self.flag = False

    def start_func(self):
        while(1):
            self.flag = True
            print (self.flag)
            time.sleep(1)

    def start(self):
        self.start_func()

    def stop(self):
        self.process.terminate()
        print(self.flag)


def target_func():
    test = Test()
    test.start()

p = multiprocessing.Process(target=target_func)
p.start()

while(1):
    time.sleep(5)
    print("OK")