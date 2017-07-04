#!/usr/bin/python
import random
from Tkinter import *

root = Tk()

w = Label(root, text="Hello, world!")
root.overrideredirect(True)
root.geometry("{0}x{1}+0+0".format(root.winfo_screenwidth(), root.winfo_screenheight()))
root.focus_set()  # <-- move focus to this widget
root.bind("<Escape>", lambda e: e.widget.quit())

MESSAGE = "THC{nyanyanyanyanyanyanyan}"
lst = []
for i in xrange(0, len(MESSAGE), 3):
    j = ord(MESSAGE[i]) << 16
    j |= ord(MESSAGE[i + 1]) << 8
    j |= ord(MESSAGE[i + 2])
    lst.append(j)
    print hex(j)

i, j = 0, 0

def task():
    global lst, i, j
    colors = ['#000000', '#0000ff', '#00ff00', '#00ffff',
              '#ff0000', '#ff00ff', '#ffff00', '#ffffff']
    print i, j
    #print bin(lst[i] & 0b111)
    #print colors[lst[i] & 0b111]
    root.configure(background=colors[(lst[i] >> 21) & 0b111])
    lst[i] = lst[i] << 3
    j += 1
    if j == 8:
        j = 0
        i += 1
    #print i, j
    if i == len(lst):
        root.after(1000, lambda: root.configure(background='black'))
        root.after(11000, root.quit)
    else:
        root.after(1000, task)

root.configure(background='black')
root.after(10000, task)
w.pack()

root.mainloop()