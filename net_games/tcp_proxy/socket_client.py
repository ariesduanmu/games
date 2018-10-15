# -*- coding: utf-8 -*-
import sys
import random
import socket
import argparse
from helper import send, receive

def main(host, port):
    client = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    try:
        client.connect((host, port))
        print(f"Connecting to {host}:{port}...")
        while True:
            receive_buf = receive(client)
            print(f"[*] Receive from server({host}:{port}): {receive_buf.decode('utf-8')}")
            message = input(">> ")
            send(client, message.encode("utf-8"))
    except Exception as e:
        print(f"[-] Error: {e}")
        client.close()

def parse_options():
    parser = argparse.ArgumentParser(usage='%(prog)s [options]',
                                     description='Socket client @Qin',
                                     formatter_class=argparse.RawDescriptionHelpFormatter,
                                     epilog=
'''
Examples:
python socket_client.py -h localhost -p 8888
'''
                                        )
    parser.add_argument('-t','--host', type=str, default="localhost")
    parser.add_argument('-p','--port', type=int, default=8888)
    args = parser.parse_args()
    return args

if __name__ == "__main__":
    args = parse_options()
    main(args.host, args.port)
