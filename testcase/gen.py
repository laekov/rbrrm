#! /usr/bin/env python
from optparse import OptionParser;
import random;

parser = OptionParser();
parser.add_option('-n', default = '5', action = 'store', type = 'int', dest = 'n');
parser.add_option('-m', default = '5', action = 'store', type = 'int', dest = 'm');
parser.add_option('-d', default = '5', action = 'store', type = 'int', dest = 'djs');
(options, args) = parser.parse_args();

n = options.n;
m = options.m;
djs = options.djs;
print n, m;
for i in range(0, n):
    s = '';
    if (i == 0 or i == n - 1):
        for j in range(0, m):
            if (random.randint(0, 10)):
                s = s + 'o';
            else:
                s = s + '.';
    else:
        if (random.randint(0, 10)):
            s = s + 'o';
        else:
            s = s + '.';
        for j in range(2, m):
            if (random.randint(0, 10) == 0 and (abs(i - j) < djs or abs(i + j - (m + n) / 2) < djs)):
                s = s + 'i';
            #elif (random.randint(0, 30) == 0):
                #s = s + 'o';
            else:
                s = s + '.';
        if (random.randint(0, 10)):
            s = s + 'o';
        else:
            s = s + '.';
    print s;
