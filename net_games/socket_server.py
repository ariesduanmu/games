# -*- coding: utf-8 -*-
import sys
import socket
import random
import threading

messages = [b"Hello", b"Can I help you", b"Welcome to my server", b"Bye"]

def client_handler(client_socket):
    try:
        while True:
            message = messages[random.randint(0,3)]
            print(f"[*] Sent to client {message.decode('utf-8')}")
            client_socket.send(message)
            client_buf = client_socket.recv(4096)
            print(f"[*] Receive from server: {client_buf.decode('utf-8')}")

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

if __name__ == "__main__":
    main(int(sys.argv[1]))