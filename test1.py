import ctypes

ll = ctypes.cdll.LoadLibrary
lib = ll('./test1.so')
lib.cfoo2(3,4)
