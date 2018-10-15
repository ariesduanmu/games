# -*- coding: utf-8 -*-
import sys
import socket
import random
import argparse
import threading
import subprocess
from helper import send, receive

def run_command(command):
    command = command.rstrip()
    try:
        output = subprocess.check_output(command, stderr=subprocess.STDOUT, shell=True)
    except Exception as error:
        output = command.encode("utf-8")
    return output

def client_handler(client_socket):
    try:
        send(client_socket, b"Welcome to my server!")
        while True:
            client_buf = receive(client_socket)
            print(f"[*] Receive from server: {client_buf.decode('utf-8')}")
            send(client_socket, run_command(client_buf.decode('utf-8')))

    except Exception as e:
        print(f"[-] Error: {e}")
        client_socket.close()

def main(port):
    sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    try:
        sock.bind(("localhost", port))
        sock.listen(5)
        while True:
            client_socket, addr = sock.accept()
            print(f"[*] Get connection from {addr[0]}:{addr[1]}")
            client_thread = threading.Thread(target=client_handler, args=(client_socket,))
            client_thread.start()
    except Exception as e:
        print(f"Error: {e}")
        sock.close()

def parse_options():
    parser = argparse.ArgumentParser(usage='%(prog)s [options]',
                                     description='Socket server @Qin',
                                     formatter_class=argparse.RawDescriptionHelpFormatter,
                                     epilog=
'''
Examples:
python socket_server.py -p 8888
'''
                                        )
    parser.add_argument('-p','--port', type=int, default=8888)
    args = parser.parse_args()
    return args

if __name__ == "__main__":
    args = parse_options()
    main(args.port)