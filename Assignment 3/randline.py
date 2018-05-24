#!/usr/bin/python

"""
Output lines selected randomly from a file

Copyright 2005, 2007 Paul Eggert.
Copyright 2010 Darrell Benjamin Carbajal.

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

Please see <http://www.gnu.org/licenses/> for a copy of the license.

$Id: randline.py,v 1.4 2010/04/05 20:04:43 eggert Exp $
"""

import random, sys
from optparse import OptionParser

class randline:
    def __init__(self, filename):
        f = open(filename, 'r')
        self.lines = f.readlines()
        f.close()

    def addLines(self, filename):
        f = open(filename, 'r')
        self.lines = self.lines + f.readlines()
        f.close()

    def uniqueLine(self):
        self.lines = list(set(self.lines))

    def chooseLine(self):
        return random.choice(self.lines)

    def noReplace(self):
        chosenline = random.choice(self.lines)
        if (self.lines==[]):
            parser.error("insufficient non-duplicate input lines")
        self.lines.remove(chosenline)
        return chosenline

    def printLines(self):
        print self.lines

    def checkEnd(self):#check the end of the last line
        listlen = len(self.lines)
        strlen=len(self.lines[listlen-1])
        if self.lines[listlen-1][strlen-1] != '\n':
            self.lines[listlen-1]=self.lines[listlen-1]+'\n'

def main():
    version_msg = "%prog 2.0"
    usage_msg = """%prog [OPTION]... FILE

Output randomly selected lines from FILE."""

    parser = OptionParser(version=version_msg,
                          usage=usage_msg)
    parser.add_option("-n", "--numlines",
                      action="store", dest="numlines", default=1,
                      help="output NUMLINES lines (default 1)")
    parser.add_option("-u", "--unique",
                      action="store_true", dest="uniqueline", default=False)
    parser.add_option("-w", "--without-replacement",
                      action="store_true", dest="noreplace", default=False)
    options, args = parser.parse_args(sys.argv[1:])

    try:
        numlines = int(options.numlines)
    except:
        parser.error("invalid NUMLINES: {0}".
                     format(options.numlines))
    if numlines < 0:
        parser.error("negative count: {0}".
                     format(numlines))
    if len(args) < 1:
        parser.error("wrong number of operands")
    input_file = args[0]
 
    try:
        generator = randline(input_file)
        generator.checkEnd()
        for i in range(len(args)-1):
            more_input = args [i+1]
            generator.addLines(more_input)
            generator.checkEnd()

        if options.uniqueline:
            generator.uniqueLine()

        for index in range(numlines):
            if options.noreplace:
                sys.stdout.write(generator.noReplace())
            else:
                sys.stdout.write(generator.chooseLine())
    except:
        parser.error("I/O error({0}): {1}".
                     format(errno, strerror))

if __name__ == "__main__":
    main()
