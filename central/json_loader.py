import json

def get_floor_tcp_info(file_name):
  json_file = open(file_name)
  floor_props = json.load(json_file)
  json_file.close()
  return floor_props