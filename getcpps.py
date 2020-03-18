#!/usr/bin/python3

import os
from os.path import isfile, join
import sys

for (dirpath, dirname, filename) in os.walk("Minecraft/src"):
    for fff in filename:
        path = join(dirpath, fff)
        fn, ext = os.path.splitext(dirpath + fff)
        if ext == ".cpp":
            print('"' + path + '"', end=" ")
