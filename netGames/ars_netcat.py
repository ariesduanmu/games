# -*- coding: utf-8 -*-
import sys
import socket
import getopt
import threading
import subprocess

def server_loop(host, port):
    server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    server.bind((host, port))
    server.listen(5)

    while True:
        client_socket, addr = server.accept()
        client_thread = threading.Thread(target=client_handler, args=(client_socket,))
        client_thread.start()

def run_command(command):
    command = command.rstrip()
    try:
        output = subprocess.check_output(command, stderr=subprocess.STDOUT, shell=True)
    except:
        output = "Failed to execute command.\n"
    return output

def client_handler(client_socket):
    pass

def parse_arguments():
    parser = argparse.ArgumentParser(description="FAKE NETCAT")
    parser.add_argument('-t','--target_host', default="localhost", type=str, help="host to listen")
    parser.add_argument('-p','--port', type=str, help="port to listen")
    parser.add_argument('-l','--listen', action="store_true", help="where to listen [host]:[port] or not")
    parser.add_argument('-e','--execute', type=str, default=100, help="file to run")
    parser.add_argument('-c','--command', action="store_true", help="initialize a command shell or not")
    parser.add_argument('-u','--upload_destination', type=str, help="upload receving connection")

    args = parser.parse_args()
    return args

if __name__ == "__main__":
    args = parse_arguments()

