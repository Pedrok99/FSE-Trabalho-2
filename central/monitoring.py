import curses
from time import sleep
from package_parser import parse_package
from threading import Thread
from socket_tcp import Server

raw_package = 'Andar:Térreo;?Lâmpada da Sala T01#7:1;Lâmpada da Sala T02#0:1;Lâmpadas do Corredor Terreo#2:1;Ar-Condicionado Terreo#11:1;Aspersor de Água (Incêndio)#27:1;?Sensor de Presença#25:0;Sensor de Fumaça#4:0;Sensor de Janela T01#13:0;Sensor de Janela T02#14:0;Sensor de Porta Entrada#12:0;Pessoas no andar:3;?Temperatura:27.100000;Umidade:49.000000;'
#raw_package = 'Andar:Aguardando...;???Temperatura:0;Umidade:0;'
pressed_key = 0
event_queue=[]

def update_package():
  HOST_IP = '192.168.0.53'
  PORT = 10057
  global raw_package
  global event_queue
  single_server = Server(HOST_IP, PORT)

  while True:
      single_server.wait_connection()
      while True:
          decoded_message = single_server.receive(1024)
          if(not decoded_message):
            print("No message recieved")
            break
          raw_package = decoded_message
          if(len(event_queue)>0):
            event = event_queue.pop(0)
            single_server.getConn().sendall(event.encode())

def handle_key_press(input_components):
  global pressed_key
  global event_queue
  if(pressed_key >= 48 and pressed_key < (48+len(input_components))):
    choice = chr(pressed_key)
    if(choice.isdigit()):
      _, gpio = input_components[int(choice)][0].split("#")
      # print("Escolha: ", input_components[int(choice)], gpio, input_components[int(choice)][1])
      event_queue.append(f'{gpio}={0 if int(input_components[int(choice)][1]) == 1 else 1}')


def init_monitoring():
  initialKey = 48
  listener = Thread(target=update_package)
  listener.daemon = True  # This thread dies when main thread (only non-daemon thread) exits.
  listener.start()
  col_size_div = 4
  global pressed_key
  def monitoring_screen(screen):
    top_shift = 3;
    global pressed_key
    init_colors()
    screen.clear()
    screen.refresh()
    screen.nodelay(True)
    while True:
      pressed_key = screen.getch()

      floorName, inputComponents, outputComponents, temp_umi = parse_package(raw_package)
      height, width = screen.getmaxyx()

      # title
      title = f"Monitorando: {floorName[0][1]}\n\n"
      temperature = f' {temp_umi[0][0]} : {temp_umi[0][1]} '
      humidity = f' {temp_umi[1][0]} : {temp_umi[1][1]} '
      # temp title humi
      screen.addstr(0, (width//2)-len(title)//2, title, curses.color_pair(1))
      screen.addstr(0, 0, temperature, curses.color_pair(6))
      screen.addstr(0, width-len(humidity), humidity, curses.color_pair(7))

      #output headers
      screen.addstr(top_shift, width-int(width*1), 'Componente (outputs)', curses.color_pair(5))
      screen.addstr(top_shift, width-int(width*0.75), 'Estado', curses.color_pair(5))
      #create output components
      for index, pair in enumerate(outputComponents):
        component = pair[0]
        state = formatValue(pair[1])
        screen.addstr((index*2)+5, 0,  f'{component}')
        screen.addstr(
          (index*2)+5, 
          (width)//col_size_div, 
          f' {state} \n', 
          curses.color_pair(2) if state == 'Ligado' else 
          (curses.color_pair(3) if state == 'Desligado' else curses.color_pair(4))
        )

      #input headers
      screen.addstr(top_shift, width-int(width*0.6), 'Componente (inputs)', curses.color_pair(5))
      screen.addstr(top_shift, width-int(width*0.3), 'Estado', curses.color_pair(5))
      screen.addstr(top_shift, width-len('Tecla Liga/Desliga'), 'Tecla Liga/Desliga', curses.color_pair(5))
      #create input components
      for index, pair in enumerate(inputComponents):
        component = pair[0]
        state = formatValue(pair[1])
        screen.addstr((index*2)+5,  width-int(width*0.6),  f'{component}')
        screen.addstr(
          (index*2)+5, 
          width-int(width*0.3), 
          f' {state} \n', 
          curses.color_pair(2) if state == 'Ligado' else 
          (curses.color_pair(3) if state == 'Desligado' else curses.color_pair(4))
        )
        screen.addstr(
          (index*2)+5, 
          width-len(str(initialKey))*5, 
          f' {chr(initialKey+index)} \n', 
          curses.color_pair(4) if pressed_key != initialKey+index else curses.color_pair(2)
        )

      handle_key_press(inputComponents)
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
  curses.init_pair(6, curses.COLOR_YELLOW , curses.COLOR_BLACK) # temp
  curses.init_pair(7, curses.COLOR_BLUE , curses.COLOR_BLACK) # humidity


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
