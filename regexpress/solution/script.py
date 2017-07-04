#!/usr/bin/python
import sre_parse
from sre_constants import *
from pwn import *

category_chars = {
    CATEGORY_DIGIT: '0',
    CATEGORY_SPACE: ' ',
    CATEGORY_WORD: 'A'
}

def handle_any(value):
    return 'A'

def handle_branch(value):
    return parse(value[1][0])

def handle_category(value):
    return category_chars[value][0]

def handle_in(value):
    return parse(value[:1])

def handle_literal(value):
    return chr(value)

def handle_max_repeat(value):
    s = parse(value[2])
    return s * value[0]

def handle_range(value):
    return chr(value[0])

def handle_subpattern(value):
    return parse(value[1])

def handle(token, value):
    handlers = {
        ANY: handle_any,
        BRANCH: handle_branch,
        CATEGORY: handle_category,
        IN: handle_in,
        LITERAL: handle_literal,
        MAX_REPEAT: handle_max_repeat,
        RANGE: handle_range,
        SUBPATTERN: handle_subpattern
    }
    try:
        return handlers[token](value)
    except KeyError:
        raise ValueError("Unsupported regular expression construct: " + token)

def parse(exp):
    return ''.join([handle(token, value) for token, value in exp])

#r = remote('localhost', 5555)
r = remote('regexpress.thcon.party', 2345)
print r.recvline()
while True:
    exp = r.recvline().strip()
    print '> ' + repr(exp)
    if exp == "Failure!" or exp.startswith("THC{"):
        break
    answer = parse(sre_parse.parse(exp))
    print '< ' + repr(answer)
    r.sendline(answer)
