# -*- coding: utf-8 -*-
import sys
import socket
import getopt
import threading
import subprocess
import argparse
import re

def run_command(command):
    command = command.rstrip()
    try:
        output = subprocess.check_output(command, stderr=subprocess.STDOUT, shell=True)
    except:
        output = "Failed to execute command.\n"
    return output

def client_handler(client_socket, upload_destination, execute):
    if upload_destination is not None:
        file_buf = ""
        while True:
            data = client.socket.recv(1024)
            if not data:
                break
            else:
                file_buf += data

        try:
            with open(upload_destination, "wb") as f:
                f.write(file_buf)

            client_socket.send(f"Successfully saved file to {upload_destination}")
        except Exception as e:
            client_socket.send(f"[-] Failed to save file to {upload_destination}")

    if len(execute):
        output = run_command(execute)
        client_socket.send(output)
    if command:
        while True:
            client_socket.send("<BHP:#> ")
            cmd_buf = ""
            while "\n" not in cmd_buf:
                cmd_buf += client_socket.recv(1024)

            response = run_command(cmd_buf)
            client_socket.send(response)

def server_loop(host, port, command, upload_destination, execute):
    server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    server.bind((host, port))
    server.listen(5)

    while True:
        client_socket, addr = server.accept()
        client_thread = threading.Thread(target=client_handler, args=(client_socket,upload_destination,execute))
        client_thread.start()

def client_sender(host, port):
    client = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    try:
        client.connect((host, port))
        while True:
            recv_len = 1
            response = ""
            while recv_len:
                data = client.recv(4096)
                recv_len = len(data)
                response += data
                if recv_len < 4096:
                    break
            print(response)

            buf = input("")
            buf += "\n"

            client.send(buf)
    except Exception as e:
        print(f"[-] Exiting...exception: {e}")
        client.close()


def parse_arguments():
    parser = argparse.ArgumentParser(description="FAKE NETCAT")
    parser.add_argument('-t','--target_host', default="localhost", type=str, help="host to listen")
    parser.add_argument('-p','--port', type=int, help="port to listen")
    parser.add_argument('-l','--listen', action="store_true", help="where to listen [host]:[port] or not")
    parser.add_argument('-c','--command', action="store_true", help="initialize a command shell or not")
    parser.add_argument('-e','--execute', type=str, required=False, help="file to run")
    parser.add_argument('-u','--upload_destination', type=str, help="upload receving connection")

    args = parser.parse_args()

    ip_pattern = "((?:25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)(?:(?<!\.)|\.)){4}"
    ip = re.match(ip_pattern, args.target_host)
    valid_ip = (ip and ip.group(0) == args.target_host)

    if not (args.target_host == "localhost" or valid_ip):
        print("[-] target_host is not valid. Exit...")
        sys.exit(1)

    if args.upload_destination is not None and not os.path.exists(args.upload_destination):
        print("[-] upload_destination file not exist. Exit...")
        sys.exit(1)

    if not (1000 < args.port <= 65535):
        print("[-] Invalid port number. Exiting")
        sys.exit(1)

    return args

if __name__ == "__main__":
    args = parse_arguments()
    if not args.listen:
        client_sender(args.target_host, args.port) 
    else:
        server_loop(args.target_host, args.port, args.command, args.upload_destination, args.execute)
