# -*- coding: utf-8 -*-
import struct

def send(sock, data):
    if data is None:
        sock.sendall("None")
        return 0
    header = struct.pack('<L', len(data))
    try:
        sock.sendall(header+data)
        return 1
    except IOError as e:
        return 0

def receive(sock):
    try:
        header_data = recv_n_bytes(sock, 4)
        if len(header_data) == 4:
            msg_len = struct.unpack('<L', header_data)[0]
            data = recv_n_bytes(sock, msg_len)
            if len(data) == msg_len:
                return data
        return None
    except IOError as e:
        return None

def recv_n_bytes(sock, n):
    data = b''
    while len(data) < n:
        chunk = sock.recv(n - len(data))
        if chunk == b'':
            break
        data += chunk
    return data
