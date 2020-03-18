#!/usr/bin/python3

f = open("lines.txt", "r")
lines = f.readlines()

adds = 0
dels = 0

for line in lines:
    if line == "\n":
        dels = 1
    else:
        if dels == 0:
            adds += int(line[:-1])
        else:
            dels += int(line[:-1])

print("Adds: " + str(adds))
print("Dels: " + str(dels - 1))
print("Diff: " + str(adds - dels - 1))
