import curses
from time import sleep
from package_parser import parse_package
from threading import Thread
from socket_tcp import Server

raw_package = 'estado:Aguardando...'

def update_package():
  HOST_IP = '192.168.0.53'
  PORT = 10057
  global raw_package
  single_server = Server(HOST_IP, PORT)

  while True:
      single_server.wait_connection()
      while True:
          decoded_message = single_server.receive(1024)
          if(not decoded_message):
              break
          raw_package = decoded_message


def init_monitoring():

  listener = Thread(target=update_package)
  listener.daemon = True  # This thread dies when main thread (only non-daemon thread) exits.
  listener.start()
  def monitoring_screen(screen):
    top_shift = 3;
    init_colors()
    screen.clear()
    screen.refresh()
    
    while True:
      parsed_package = parse_package(raw_package)
      height, width = screen.getmaxyx()
      title = f"Monitorando: {parsed_package[0][1]}\n\n"

      screen.addstr(0, (width//2)-len(title)//2, title, curses.color_pair(1))
      screen.addstr(top_shift, 0, 'Componente', curses.color_pair(5))
      screen.addstr(top_shift, width//2, 'Estado', curses.color_pair(5))

      for index, pair in enumerate(parsed_package[1:]):
        component = pair[0]
        state = formatValue(pair[1])

        screen.addstr((index*2)+5, 0,  f' {component} ')
        screen.addstr(
          (index*2)+5, 
          (width)//2, 
          f' {state} \n', 
          curses.color_pair(2) if state == 'Ligado' else 
          (curses.color_pair(3) if state == 'Desligado' else curses.color_pair(4))
        )
      screen.refresh()
      sleep(1)
      screen.clear()

  curses.wrapper(monitoring_screen)

def init_colors():
  curses.start_color()
  curses.init_pair(1, curses.COLOR_CYAN, curses.COLOR_BLACK) # title
  curses.init_pair(2, curses.COLOR_BLACK, curses.COLOR_GREEN) # on
  curses.init_pair(3, curses.COLOR_BLACK, curses.COLOR_RED) # off
  curses.init_pair(4, curses.COLOR_WHITE , curses.COLOR_BLACK) # text
  curses.init_pair(5, curses.COLOR_MAGENTA , curses.COLOR_BLACK) # header


def formatValue(value):
  value = str(value)
  if(value == '1'):
    return 'Ligado'
  elif(value == '0'):
    return 'Desligado'
  elif(value.isdigit()):
    return value
  elif (value.isdecimal()):
    return value[:5]
  else:
    return value
