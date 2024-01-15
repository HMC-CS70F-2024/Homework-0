#!/usr/bin/python3
#
#   _  ___   ___        _                      
#  / |/ _ \ / _ \    __| | ___   ___  _ __ ___ 
#  | | | | | | | |  / _` |/ _ \ / _ \| '__/ __|
#  | | |_| | |_| | | (_| | (_) | (_) | |  \__ \
#  |_|\___/ \___/   \__,_|\___/ \___/|_|  |___/   an example problem
#                                          
#  There are 100 doors in a row that are all initially closed.
#  You make 100 passes by the doors.
#  * The first time through, visit every door and toggle the door
#    (i.e., if the door is closed, open it;  if it is open, close it).
#  * The second time, only visit every 2nd door (door #2, #4, #6, ...),
#    and toggle it.
#  * The third time, visit every 3rd door (door #3, #6, #9, ...), etc,
#  ... until you only visit the 100th door.
#                       (original problem seen on rosettacode.org)
#
#  You can ask python to interpret this code with:
#
#      python3 doors-in-python.py

def irange(start, end, inc=1): return range(start, end+inc, inc)

isOpen = [False] * 100
for step in irange(1,100):
    for door in range(step-1, 100, step):
        isOpen[door] = not isOpen[door]
   
for door in range(100):
    if isOpen[door]:
        print("Door %d is open" % (door+1))
