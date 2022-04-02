import socket

class Server():
  def __init__(self, ip, port):
    self.s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    self.s.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)

    try:
      self.s.bind((ip, port))
    except: 
      print(f'Failed to bind to {ip}:{port}')
      exit()

  def wait_connection(self):
    self.s.listen(True)
    print("Waiting for connection...")
    self.conn, addr = self.s.accept()
    print(f"Connected to {addr}")

  def __del__(self):
    self.s.close()

  # def send(self, message):
  #   message_size = str(len(message)).ljust(self.__size_message_length).encode()
  #   self.conn.sendall(message_size)  # Send length of msg (in known size, 16)
  #   self.conn.sendall(message.encode())  # Send message

  def receive(self, buffer_size):
    message = self.conn.recv(buffer_size)
    if not message:
      print('No message recieved')
      return False
    return message.decode(encoding='utf_8', errors='replace')

  # def __receive_value(self, conn, buf_lentgh):
  #   buf = b''
  #   while buf_lentgh:
  #     newbuf = conn.recv(buf_lentgh)
  #     # if not newbuf: return None
  #     buf += newbuf
  #     buf_lentgh -= len(newbuf)
  #   return buf.decode()
