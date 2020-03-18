#!/usr/bin/python3

from os import walk
from os.path import isfile, join
import sys

dirs = ["Minecraft/src", "Minecraft/lua", "Minecraft/res/shaders"]
files = ["Minecraft/count.sh", "countlines.py", "lines.txt", "gitlines.py", "README.md", "premake5.lua", "generate.sh", "Minecraft/vendor/freetype-gl/premake5.lua", "Minecraft/vendor/FreeType/premake5.lua", "Minecraft/vendor/GLFW/premake5.lua", "Minecraft/vendor/Glad/premake5.lua", "Minecraft/vendor/lua/premake5.lua", "Minecraft/vendor/freetype-gl/build.sh", "Minecraft/vendor/lua/build.sh", "build-web.sh", ".gitignore"]

linecount = 0
filecount = 0
charcount = 0

for dir in dirs:
    dirlines = 0
    dirchars = 0
    for (dirpath, dirname, filename) in walk(dir):
        for fff in filename:
            path = join(dirpath, fff)
            f = open(path, "r")
            flines = f.readlines()
            if "-a" in sys.argv:
                print("%s : %d" % (path, flines))
            filecount += 1
            linecount += len(flines)
            dirlines += len(flines)
            for l in flines:
                dirchars += len(l)
                charcount += len(l)
    print("Directory: %s : %d, %d" % (dir, dirlines, dirchars))

for file in files:
    flines = open(file, "r").readlines()
    filecount += 1
    linecount += len(flines)
    filechars = 0
    for l in flines:
        charcount += len(l)
        filechars += len(l)
    print("%s : %d, %d" % (file, len(flines), filechars))

print("%d lines in %d files, with an average of %f lines per file with a total character length of %d" % (linecount, filecount, linecount / filecount, charcount))
