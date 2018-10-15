# -*- coding: utf-8 -*-
import sys
import random
import socket

def main(host, port):
    sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    try:
        sock.connect((host, port))
        while True:
            recv = sock.recv(4096)
            print(f"[*] Receive from server: {recv.decode('utf-8')}")
            message = input("What you wanna send:")
            print(f"[*] Sent to server: {message}")
            sock.send(message.encode("utf-8"))
    except Exception as e:
        print(f"Error: {e}")
        sock.close()

if __name__ == "__main__":
    main(sys.argv[1], int(sys.argv[2]))
