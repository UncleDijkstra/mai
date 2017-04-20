import time

class Profiler(object):
    def __enter__(self):
        self._startTime = time.time()
         
    def __exit__(self, type, value, traceback):
        print ("time python: {:.6f} sec".format(time.time() - self._startTime))

with Profiler() as p:
    while True:
        try:
            x = input()
        except EOFError:
            break
        y = int(input())
        s = input()
        x = int(x)
        if s in ('+','-','*','/', '<'):
            if s == '+':
                print("%d" % (x + y))
            elif s == '-':
                print("%d" % (x - y))
            elif s == '*':
                print("%d" % (x * y))
            elif s == '/':
                if y != 0:
                    print("%d" % (x / y))
                else:
                    print("Error")
            elif s == '<':
                print("%d" % (x < y))
        else:
            print("Error")