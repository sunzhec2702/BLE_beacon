import multiprocessing
import time

class Test(object):
    flag = False
    process = None
    def __init__(self):
        self.flag = False

    def start_func(self, instance):
        while(1):
            instance.flag = True
            print (instance.flag)
            time.sleep(1)

    def start(self):
        self.process = multiprocessing.Process(target=self.start_func, args=(self, ))
        test.process.start()

    def stop(self):
        self.process.terminate()
        print(self.flag)

if __name__ == '__main__':
    test = Test()
    test.start()

    while(1):
        time.sleep(1)
        print(test.flag)