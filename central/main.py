
from time import sleep
from json_loader import get_floor_tcp_info
from monitoring import init_monitoring
from socket_tcp import Server
floor_data = get_floor_tcp_info('configuracao_andar_terreo.json')

# PORT = int(floor_data['porta_servidor_distribuido'])
PORT = 10057
# HOST_IP = floor_data['ip_servidor_distribuido']
HOST_IP = '192.168.0.53'

#init_monitoring()

single_server = Server("localhost", PORT)

while True:
    single_server.wait_connection()
    while True:
      print("Message sent")
      single_server.getConn().sendall("alo".encode())
      sleep(2)
