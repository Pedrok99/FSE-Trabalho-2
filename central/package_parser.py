from os import sep
import re

def parse_package(message):
  # print(re.findall("[\wÀ-ú\d .]+:[\wÀ-ú\d .]+;", message))
  parsed = re.findall("[\wÀ-ú\d .]+:[\wÀ-ú\d .]+", message)
  tempArr = []
  for str in parsed:
    key, value = str.split(sep=":")
    tempArr.append((key, value))
  return tempArr
