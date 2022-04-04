import re

def parse(str_to_parse):
  tempArr = []
  parsed = re.findall("[\wÀ-ú\d .\-\(\)#]+:[\wÀ-ú\d .]+", str_to_parse)
  for str in parsed:
    key, value = str.split(sep=":")
    tempArr.append((key, value))
  return tempArr

def parse_package(message:str):
  floorName, inputComponents, outputComponents, temperature = message.split("?")
  floorName = parse(floorName)
  inputComponents = parse(inputComponents)
  outputComponents = parse(outputComponents)
  temperature = parse(temperature)
  return floorName, inputComponents, outputComponents, temperature