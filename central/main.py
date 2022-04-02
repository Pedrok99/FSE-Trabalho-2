from base64 import decode
from time import sleep
from socket_tcp import Server
from json_loader import get_floor_tcp_info

floor_data = get_floor_tcp_info('configuracao_andar_terreo.json')

# PORT = int(floor_data['porta_servidor_distribuido'])
PORT = 10057
# HOST_IP = floor_data['ip_servidor_distribuido']
HOST_IP = 'localhost'

single_server = Server(HOST_IP, PORT)

while True:
    single_server.wait_connection()
    while True:
        decoded_message = single_server.receive(1024)
        if(not decoded_message):
            break
        print(decoded_message)
