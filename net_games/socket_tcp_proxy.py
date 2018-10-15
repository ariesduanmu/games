# -*- coding: utf-8 -*-
import sys
import os
import re
import socket
import argparse
import threading


def receive_from(connection):
    buf = b""
    # connection.settimeout(2)
    try:
        while True:
            data = connection.recv(4096)
            buf += data
            if len(data) < 4096:
                break
    except Exception as e:
        print (f"[-] Receving Error: {e}")
    return buf

def proxy_handler(client_socket, remotehost, remoteport, receivefirst):
    remote_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    try:
        remote_socket.connect((remotehost, remoteport))
        while True:
            remote_buf = receive_from(remote_socket)
            client_socket.send(remote_buf)
            local_buf = receive_from(client_socket)
            remote_socket.send(local_buf)
            
            if len(local_buf) == 0 or len(remote_buf) == 0:
                client_socket.close()
                remote_socket.close()
                print("[*] No more data. Closing connections")
                break

    except Exception as e:
        print(f"[-] Error: {e}")
        remote_socket.close()
        client_socket.close()

def main(localhost, localport, remotehost, remoteport, receivefirst):
    server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    try:
        server.bind((localhost, localport))
        server.listen(5)

        while True:
            client_socket, addr = server.accept()
            print(f"Recevied incoming connection from {addr[0]}:{addr[1]}")
            proxy_thread = threading.Thread(target=proxy_handler, args=(client_socket, remotehost, remoteport, receivefirst))
            proxy_thread.start()
    except Exception as e:
        print(f"[-] Error:{e}")
        server.close()

def parse_options():
    parser = argparse.ArgumentParser(usage='%(prog)s [options]',
                                     description='Socket TCP Proxy @Qin',
                                     formatter_class=argparse.RawDescriptionHelpFormatter,
                                     epilog=
'''
Examples:
python socket_tcp_proxy.py -l localhost -p 8888 -r 127.0.0.1 -t 8000 
'''
                                        )
    parser.add_argument('-l','--localhost', type=str, default="localhost")
    parser.add_argument('-p','--localport', type=int, default=8888)
    parser.add_argument('-r','--remotehost', type=str)
    parser.add_argument('-t','--remoteport', type=int)
    parser.add_argument('-f','--receivefirst', action="store_true")
    args = parser.parse_args()
    return args

if __name__ == "__main__":
    args = parse_options()
    main(args.localhost, args.localport, args.remotehost, args.remoteport, args.receivefirst)
