import socket
import struct
from json_loader import get_floor_tcp_info

floor_data = get_floor_tcp_info('configuracao_andar_terreo.json')

PORT = int(floor_data['porta_servidor_distribuido'])
HOST_IP = floor_data['ip_servidor_distribuido']
server_address = (HOST_IP, PORT)

socket_instance = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
socket_instance.bind(server_address)
socket_instance.listen()

with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
    s.bind((HOST_IP, PORT))
    s.listen()
    print("starting to listen")
    conn, addr = s.accept()
    with conn:
        print('Connected by', addr)
        while True:
            t = int(input("value (int): "))
            assert t >= 0
            d = struct.pack('I', t)
            conn.sendall(d)