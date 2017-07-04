#!/usr/bin/python
import re
import random
import select
import string
import sys

def get_token():
    p = random.random()
    if p < 0.7:
        t = get_char()
    elif p < 0.9:
        t = get_class()
    else:
        t = get_group()
    return t + get_quantifier()

def get_char():
    return random.choice(list(string.ascii_letters + string.digits) + ['\d', '\s', '\w', '.'])

def get_class():
    if random.random() < 0.5:
        return "[%s]" % random.choice(['a-z', 'A-Z', 'a-zA-Z', '0-9'])
    else:
        e = ''
        for i in xrange(random.randint(2, 6)):
            e += get_char()
        return "[%s]" % e

def get_group():
    return "(%s|%s)" % (get_token(), get_token())

def get_quantifier():
    p = random.random()
    if p < 0.5:
        return ''
    elif p < 0.7:
        return '*'
    elif p < 0.9:
        return '+'
    return '{%d}' % random.randint(2, 9)

def get_regex():
    while True:
        e = ''
        for i in xrange(random.randint(5, 11)):
            e += get_token()
        try:
            re.compile(e)
            return e
        except:
            continue

TIMEOUT = 10

def print_(s):
    sys.stdout.write(s + '\n')
    sys.stdout.flush()

def main():
    print_("Find a match for each of the following regexes:")
    for i in xrange(1000):
        e = get_regex()
        print_(e)
        r, w, x = select.select([sys.stdin], [], [], TIMEOUT)
        if r:
            m = sys.stdin.readline().replace('\n', '')
            if not re.match(e, m):
                print_("Failure!")
                sys.exit(1)
        else:
            print_("Timeout!")
            sys.exit(1)

    with open('flag.txt', 'r') as f:
        print_(f.readline().strip())

if __name__ == '__main__':
    main()
