#!/usr/local/cs/bin/python3

import random, sys
from optparse import OptionParser

class randline:
  def __init__(self, filename):
    self.lines = []
    if filename == '-':
       self.lines.append(sys.stdin.readline())
    else:
       f = open (filename, 'r')
       self.lines = f.readlines()
       f.close()

def main():
    version_msg = "%prog 2.0"
    usage_msg = """%prog [OPTION]...
compare two files."""

    parser = OptionParser(version=version_msg,  usage=usage_msg)
    parser.add_option("-1", "--suppressfile1", action="store_true",\
 dest="choice1",default=False, help="suppress lines unique to file1")
    parser.add_option("-2", "--suppressfile2", action="store_true",\
 dest="choice2", default=False, help="suppress lines unique to file2")
    parser.add_option("-3", "--suppresscommon", action="store_true",\
 dest="choice3", default=False, help="suppress duplicated lines in both files")
    parser.add_option("-u", "--unsorted", action="store_true",\
 dest="choice4", default=False, help="compare unsorted files")

    options, args = parser.parse_args(sys.argv[1:])
    
    try:
        choice1 = bool(options.choice1)
    except:
        parser.error("invalid CHOICE: {False}".format(options.choice1))
    try:
        choice2 = bool(options.choice2)
    except:
        parser.error("invalid CHOICE: {False}".format(options.choice2))
    try:
        choice3 = bool(options.choice3)
    except:
        parser.error("invalid CHOICE: {False}".format(options.choice3))
    try:
        choice4 = bool(options.choice4)
    except:
        parser.error("invalid CHOICE: {False}".format(options.choice4))
    if len(args) != 2:
        parser.error("wrong number of operands")
        sys.exit
    if args[0] == "-" and args[1] == "-":
        parser.error("There should not be two files from stdin")
        sys.exit
    if args[0] == args[1]:
        parser.error("Two same operands are not permitted")
        sys.exit
    
    handle1 = randline(args[0])
    handle2 = randline(args[1])
    if handle1.lines[-1][-1] != "\n":
      handle1.lines[-1] = handle1.lines[-1] + "\n"
    if handle2.lines[-1][-1] != "\n":
      handle2.lines[-1] = handle2.lines[-1] + "\n"
    handleunsorted1 = handle1.lines
    handleunsorted2 = handle2.lines
    handletemp1 = handle1.lines
    handletemp2 = handle2.lines
    if choice4 == False:
       if sorted(handle1.lines) != handle1.lines or sorted(handle2.lines)\
 != handle2.lines:
          parser.error("Files cannot be unsorted")
          sys.exit
       else:
          total = []
          for lines in handle1.lines:
             total.append(lines)
          for lines in handle2.lines:
             total.append(lines)
          total.sort()

          if choice1 == True and choice2 == True and choice3 == False:
            for lines in total:
              if lines in handletemp1 and lines in handletemp2:
                sys.stdout.write (lines)
                handletemp1.remove(lines)
                handletemp2.remove(lines)
              elif lines in handletemp1 and lines not in handletemp2:
                handletemp1.remove(lines)               
              elif lines in handletemp2 and lines not in handletemp1:
                handletemp2.remove(lines)
            
          if choice1 == True and choice2 == False and choice3 == True:
            for lines in total:
              if lines in handletemp1 and lines in handletemp2:
                handletemp1.remove(lines)
                handletemp2.remove(lines)
              elif lines in handletemp1 and lines not in handletemp2:
                handletemp1.remove(lines)               
              elif lines in handletemp2 and lines not in handletemp1:
                sys.stdout.write (lines)
                handletemp2.remove(lines)
            
          if choice1 == False and choice2 == True and choice3 == True:
            for lines in total:
              if lines in handletemp1 and lines in handletemp2:
                handletemp1.remove(lines)
                handletemp2.remove(lines)
              elif lines in handletemp1 and lines not in handletemp2:
                sys.stdout.write(lines)
                handletemp1.remove(lines)               
              elif lines in handletemp2 and lines not in handletemp1:
                handletemp2.remove(lines)
            
          if choice1 == True and choice2 == False and choice3 == False:
            for lines in total:
              if lines in handletemp1 and lines in handletemp2:
                sys.stdout.write ("    \t" + lines)
                handletemp1.remove(lines)
                handletemp2.remove(lines)
              elif lines in handletemp1 and lines not in handletemp2:
                handletemp1.remove(lines)               
              elif lines in handletemp2 and lines not in handletemp1:
                sys.stdout.write (lines)
                handletemp2.remove(lines)
            
          if choice1 == False and choice2 == True and choice3 == False:
            for lines in total:
              if lines in handletemp1 and lines in handletemp2:
                sys.stdout.write ("    \t" + lines)
                handletemp1.remove(lines)
                handletemp2.remove(lines)
              elif lines in handletemp1 and lines not in handletemp2:
                sys.stdout.write(lines)
                handletemp1.remove(lines)               
              elif lines in handletemp2 and lines not in handletemp1:
                handletemp2.remove(lines)
          
          if choice1 == False and choice2 == False and choice3 == True:
            for lines in total:
              if lines in handletemp1 and lines in handletemp2:
                handletemp1.remove(lines)
                handletemp2.remove(lines)
              elif lines in handletemp1 and lines not in handletemp2:
                sys.stdout.write(lines)
                handletemp1.remove(lines)               
              elif lines in handletemp2 and lines not in handletemp1:
                sys.stdout.write ("    \t" + lines)
                handletemp2.remove(lines)
          
          if choice1 == False and choice2 == False and choice3 == False:
            for lines in total:
              if lines in handletemp1 and lines in handletemp2:
                sys.stdout.write ("    \t    \t" + lines)
                handletemp1.remove(lines)
                handletemp2.remove(lines)
              elif lines in handletemp1 and lines not in handletemp2:
                sys.stdout.write(lines)
                handletemp1.remove(lines)               
              elif lines in handletemp2 and lines not in handletemp1:
                sys.stdout.write ("    \t" + lines)
                handletemp2.remove(lines)


    elif choice4 == True:
          if choice1 == True and choice2 == True and choice3 == False:
            for lines in handleunsorted1:
              if lines in handletemp2:
                sys.stdout.write (lines)
                handletemp2.remove(lines)
          
          if choice1 == True and choice2 == False and choice3 == True:
            for lines in handleunsorted1:
              if lines in handletemp2:
                handletemp2.remove(lines)
            for lines in handletemp2:               
                sys.stdout.write (lines)

          if choice1 == False and choice2 == True and choice3 == True:
            for lines in handleunsorted1:
              if lines in handletemp2:
                handletemp2.remove(lines)
              else:
                sys.stdout.write(lines)
          
          if choice1 == True and choice2 == False and choice3 == False:
            for lines in handleunsorted1:
              if lines in handletemp2:
                sys.stdout.write ("    \t" + lines)
                handletemp2.remove(lines)
            for lines in handletemp2:               
                sys.stdout.write (lines)
          
          if choice1 == False and choice2 == True and choice3 == False:
            for lines in handleunsorted1:
              if lines in handletemp2:
                sys.stdout.write ("    \t" + lines)
                handletemp2.remove(lines)
              else:
                sys.stdout.write(lines)
          
          if choice1 == False and choice2 == False and choice3 == True:
            for lines in handleunsorted1:
              if lines in handletemp2:
                handletemp2.remove(lines)
              else:
                sys.stdout.write(lines)
            for lines in handletemp2:               
                sys.stdout.write ("    \t" + lines)

          if choice1 == False and choice2 == False and choice3 == False:
            for lines in handleunsorted1:
              if lines in handletemp2:
                sys.stdout.write ("    \t     \t" + lines)
                handletemp2.remove(lines)
              else:
                sys.stdout.write(lines)
            for lines in handletemp2:               
                sys.stdout.write ("    \t" + lines)

if __name__ == "__main__":
   main()
