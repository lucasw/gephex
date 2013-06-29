#!/usr/bin/python

import re, sys, string, os

#
# The moc tool delivered with qt2.3 on windows does not play
# well with classes that use namespaces.
# Therefore it is necessary to postprocess the moced files.
# This script automates the postprocessing. It just removes
# the namespace in the strcmp() call as shown below.
#
# regular expressions for scanning:
#
# if ( strcmp(gui::TypeView::className(), "gui::TypeView") != 0 )
strcmp_string = r"^\s*if\s*\(\s*strcmp\([a-zA-Z]+[:][:](.*)\)$"

strcmp = re.compile(strcmp_string)


def process(file):
	" Liest aus file. "
	line = ' '
	id = ''
	pairs = {}
	matchedEndBlock = 0

	while line != '':
		line = file.readline()		
		
		sys.stdout.write(re.sub(strcmp, r' if ( strcmp(\1)', line))
	

def printUsage():
	sys.stderr.write("Usage: postmoc.py <mocedfile>\n")
    

if len(sys.argv) != 2:	
	printUsage()
	sys.exit(-1)

fileName = sys.argv[1]

try:
	inFile = open(fileName,'r')
	process(inFile)
except IOError:
	sys.stderr.write('Error, couldnt open ' + fileName + '\n')
	sys.exit(-1)
