#!/usr/bin/python
#TODO: in der receiver implementierung reicht es wohl, buffer forward zu dekl.
import string, sys, os

def startsWith(s, pattern):
	return string.find(s,pattern) == 0

def endsWith(s, pattern):
	if len(s) < len(pattern):
		return 0
	return string.find(s,pattern) == len(s)-len(pattern)

def readComment(file):
	commentLines = []
	line = ' '
	while line != '':
		line = file.readline()
		if string.strip(line) == '':
			pass
		elif startsWith(string.strip(line),'/*'):
			break
		else:
			sys.stderr.write("Unexpected line: " + line)
			sys.stderr.write("Expected begin of  comment\n")
			sys.exit(1)

	if line == '':
		return ''
	
	while line != '':
		commentLines.append(line)
		if endsWith(string.strip(line),'*/'):
			break
		line = file.readline()

	return reduce(lambda x, y: x + y, commentLines)

def readToken(s, delim):
	p1 = -1
	for i in range(0,len(s)):
		if string.find(delim,s[i]) == -1:
			p1 = i
			break
	if p1 == -1:
		return ''

	p2 = len(s)
	for i in range(p1,len(s)):
		if string.find(delim,s[i]) != -1:
			p2 = i
			break
	
	return s[p1:p2]


def tokenize(s, delims):
	if s == '':
		return []
	else:
	   s = string.strip(s)
	   token = readToken(s,delims)
	   return [token] + tokenize(s[len(token)+1:],delims)

def varTokenToVarDecl(token):
	i = string.rfind(token,' ')
	return (string.strip(token[:i]),string.strip(token[i+1:]))

def readArgList(argListString):
	argList = []
	tokenList = map(string.strip,tokenize(argListString,','))
	
	return map(varTokenToVarDecl,tokenList)
		
def readDef(file):
	line = ' '
	while line != '':
		line = file.readline()
		if string.strip(line) == '':
			pass
		else:
			break

	line = string.strip(line)

	if line == '':
		return None

	name = readToken(line,' \t\n')
	argListString = line[len(name)+1:]
	argList = readArgList(argListString)
	
	return (name,argList)

def readHeader(file):
	line = ' '	
	while line != '':
		line = file.readline()
		sline = string.strip(line)
		if sline == '':
			pass
		elif startsWith(sline,'name:'):
			name = string.strip(sline[5:])
			return {'name':name}
		else:
			sys.stderr.write("Error: expected name:")

def readInterface(file):
	header = readHeader(file)
	globalComment = readComment(file)
	list = []
	while 1:
		comment = readComment(file)
		definition = readDef(file)

		if definition == None:
		       break
		list.append((comment,definition))

	return (header,globalComment,list)


def typeToCType(type):
	if type == 'string':
		return 'utils::String'
	elif type == 'buffer':
		return 'utils::Buffer'
	else:
		return type
def typeToCTypeDecl(type):
	if type == 'string':
		return 'const std::string&'
	elif type == 'buffer':
		return 'const utils::Buffer&'
	else:
		return type

def definition2Decl(definition, className = ''):

	methodName = definition[0]
	argList = definition[1]

	if argList != []:
		cArgList = map(lambda x: typeToCTypeDecl(x[0]) + ' ' + x[1],
			        argList)
		cArgs = reduce(lambda x, y: x + ', ' + y,cArgList)
	else:
		cArgs = ''

	if className == '':
		methodName_ = methodName
	else:
		methodName_ = className + '::' + methodName

	return 'void ' + methodName_ + '( ' + cArgs + ' )'


def createIfaceRecHeader(file,name_,comment,interface):
	def createInterfaceDefinitions(methodDefs):
		methodCDefs = map(lambda x: x + ' = 0;\n\n',
				  map(lambda x: x[0] + '\tvirtual ' + definition2Decl(x[1]),
				      methodDefs))

		return reduce(lambda x, y: x + y, methodCDefs)

	name = 'I' + name_ + 'Receiver'
	includeGuard = 'INCLUDED_' + string.upper(name) + '_H\n'
	file.write('#ifndef ' + includeGuard)
	file.write('#define ' + includeGuard)

	file.write('#include <string>\n\n')
	
	file.write('namespace utils {\n\tclass Buffer;\n}\n\n')

	file.write(comment)
	file.write('\n')
	
	file.write('class ' + name + '\n{\n')
	file.write('public:\n')
	file.write(createInterfaceDefinitions(interface))
		
	file.write('};\n#endif\n')

def createIfaceSendHeader(file,name_):
	name = 'I' + name_ + 'Sender'
	includeGuard = 'INCLUDED_' + string.upper(name) + '_H\n'
	file.write('#ifndef ' + includeGuard)
	file.write('#define ' + includeGuard)
	template = """class IX_NAME_XReceiver;
class IX_NAME_XSender
{
 public:
  virtual void registerX_NAME_XReceiver(IX_NAME_XReceiver& r) = 0;
};

#endif
"""

	file.write(string.replace(template,'X_NAME_X',name_))



def createNetIfaceRecHeader(file, name_,interface):
	def createNetInterfaceDefinitions(methodDefs):
		methodCDefs = map(lambda x: '\t' + x + ';\n\n',
				  map(lambda x: definition2Decl(x[1]),
				      methodDefs))

		return reduce(lambda x, y: x + y, methodCDefs)

	name = name_ + 'ReceiverNet'
	includeGuard = 'INCLUDED_' + string.upper(name) + '_H\n'
	file.write('#ifndef ' + includeGuard)
	file.write('#define ' + includeGuard + '\n')

	file.write('#include "interfaces/i' + string.lower(name_) 
		   + 'receiver.h"\n\n')

	file.write('namespace net {\n\ttemplate <typename Key>\n\tclass ITagger;\n}\n\n')
	
	file.write('class ' + name + ' : public I' + name_ + 'Receiver\n{\n')
	file.write('private:\n\tnet::ITagger<std::string>* m_tagger;\n\n')
	file.write('public:\n')
	file.write('\t' + name + '(net::ITagger<std::string>& tagger);\n\n')
	file.write('\tvirtual ~' + name + '();\n\n')
	file.write(createNetInterfaceDefinitions(interface))
		
	file.write('};\n#endif\n')

def createNetIfaceSendHeader(file, name_):
	template = """#ifndef INCLUDED_XXX_BIGNAME_XXX_SENDER_NET_H
#define INCLUDED_XXX_BIGNAME_XXX_SENDER_NET_H

#include <string>

#include "interfaces/iXXX_LITTLENAME_XXXsender.h"

#include "net/itaginterpreter.h"

class XXX_NAME_XXXSenderNet : public IXXX_NAME_XXXSender,
			      public net::ITagInterpreter<std::string>
{
public:
        XXX_NAME_XXXSenderNet();
	
	virtual void registerXXX_NAME_XXXReceiver(IXXX_NAME_XXXReceiver&);
	virtual void dataReceived(const std::string& command,const utils::Buffer&);

private:
	IXXX_NAME_XXXReceiver* m_rec;
};

#endif
"""

	temp1 = string.replace(template,'XXX_BIGNAME_XXX',string.upper(name_))
	temp2 = string.replace(temp1,'XXX_LITTLENAME_XXX',string.lower(name_))
	temp3 = string.replace(temp2,'XXX_NAME_XXX',name_)
	file.write(temp3)

def createCommandName(methodNames):

	print commandNames

def stringShit(pair):
	(type, var) = pair;
	if type == 'string':
		return 'utils::String(' + var + ')'
	else:
		return var;
	

def createRecMethodBody(signature):
#	pre = '\tutils::OutByteStream bs;\n'
	(methodName,argList,commandName) = signature

	if len(argList) > 0:
		maxLengthHint = `len(argList)*16`
		pre = '\tutils::Buffer temp_buf_(' + maxLengthHint + ');\n' \
		      '\tutils::OBufferStream bs(temp_buf_);\n'
	else:
		pre = '\tutils::Buffer temp_buf_((unsigned char*) "",1);\n'

#	commandName = createCommandName(methodName)
	post = '\tm_tagger->setTag( "' + commandName + '" );\n' \
	       '\tm_tagger->send( temp_buf_ );\n'
#	       '", bs.getBuffer() );\n'
	if len(argList) > 0:
		serCodes = map(lambda x: " << "
			       + stringShit(x), argList)
		serCode = '\tbs' + reduce(lambda x,y: x + " << ' ' " +  y,
					  serCodes) + ';\n\tbs.flush();\n'
					  
	else:
		serCode = ''

	return pre + serCode + post

def expand24Digits(str):
	return '0000'[len(str):] + str

def number24string(i):
	istr = `i`
	return expand24Digits(istr)
	
def insertCommandNames(methodDefs):		
	newDefs = []
	for i in range(0,len(methodDefs)):
		newDefs.append((methodDefs[i][0],(methodDefs[i][1][0],
						  methodDefs[i][1][1],
						  number24string(i))))
		
	return newDefs
	
def createNetIfaceRecImpl(file, name_,interface):

	def createNetInterfaceMethods(methodDefs, className):
		methodCImpls = map(lambda x,c = className: definition2Decl(x[1], c) 
					     + '\n{\n' 
					     + createRecMethodBody(x[1])
					     + '\n}\n\n',
				   methodDefs)

		return reduce(lambda x, y: x + y, methodCImpls)



	className = name_ + 'ReceiverNet'

	preTemplate = '#include "X_SMALLNAME_X.h"\n\n' \
		      '#include "net/itagger.h"\n' \
		      '#include "utils/buffer.h"\n' \
		      '#include "utils/bufferstream.h"\n' \
		      '#include "utils/string_.h"\n' \
		      '#include "utils/bufferutils.h"\n' \
		      'X_NAME_X::X_NAME_X(net::ITagger<std::string>& tagger)\n' \
		      '\t: m_tagger(&tagger)\n{}\n\n' \
		      'X_NAME_X::~X_NAME_X()\n{}\n\n' \

		      #		      '#include "utils/outbytestream.h"\n' \
#		      '#include "utils/outbytestreamutils.h"\n\n' \


	file.write(string.replace(string.replace(preTemplate,'X_SMALLNAME_X',
				  		 string.lower(className)),
				  'X_NAME_X',className))

	newInterface = insertCommandNames(interface)
	file.write(createNetInterfaceMethods(newInterface,className))

def createSendCode(signature):
	(methodName, argList, commandName) = signature[1]

	if len(argList) > 0:	
		decls = map(lambda x: '\t\t' + typeToCType(x[0]) + ' ' + x[1]
		    + ';\n',argList)
		declBlock = reduce(lambda x,y: x + y, decls)

		scans = map(lambda x: ' >> ' + x[1], argList)
		scanBlock = '\t\tbs ' + reduce(lambda x,y: x + y, scans) + ';\n'

		params = reduce(lambda x, y: x + ', ' + y,
				map(lambda x: x[1], argList))
	else:
		declBlock = scanBlock = params = ''
	
	callBlock = '\t\tm_rec->' + methodName + '( ' + params + ' );\n'
		    
	return '\tif (command == "' + commandName + '")\n\t {\n' \
	       + declBlock+ scanBlock + callBlock + '\t }\n';
	

def createNetIfaceSendImpl(file, name_, interface):
	template = '#include "X_LITTLENAME_Xsendernet.h"\n\n' \
		   '#include <iostream>\n' \
		   '#include <sstream>\n' \
		   '#include <stdexcept>\n\n' \
		   '#include "interfaces/iX_LITTLENAME_Xreceiver.h"\n' \
		   '#include "utils/buffer.h"\n' \
		   '#include "utils/bufferstream.h"\n' \
		   '#include "utils/string_.h"\n' \
		   '#include "utils/bufferutils.h"\n' \
		   'X_NAME_XSenderNet::X_NAME_XSenderNet()\n' \
		   '\t : m_rec(0) {}\n\n' \
		   'void X_NAME_XSenderNet::registerX_NAME_XReceiver' \
		   '(IX_NAME_XReceiver& r)\n{\n\tm_rec = &r;\n}\n\n' \
		   'void X_NAME_XSenderNet::dataReceived(' \
		   'const std::string& command,const utils::Buffer& buf)\n' \
		   '{\n\tif (!m_rec) \n' \
		   '\t{\n\t\tstd::cerr << "Receiver not set at "\n' \
		   '\t\t "' + name_ + 'SenderNet::commandReceived()" \n' \
		   '\t\t  << std::endl;\n' \
		   '\t\treturn;\n\t}\n\n' \
		   '\tutils::IBufferStream bs(buf);\n' \
		   'X_CODE_X\n}\n\n'


#		   '\tutils::InByteStream bs(buf);\n' \

#		   '#include "utils/inbytestream.h"\n' \
#		   '#include "utils/inbytestreamutils.h"\n\n' \

	temp1 = string.replace(string.replace(template,'X_NAME_X',name_),
			       'X_LITTLENAME_X',string.lower(name_))

	newInterface = insertCommandNames(interface)
	sendCodes = map(lambda x: createSendCode(x), newInterface)
	sendCode = reduce(lambda x,y: x + '\telse ' + y, sendCodes) + \
		   '\t else\n\t {\n\t\tstd::ostringstream stream;\n' \
		   '\t\tstream << "Laenge: " << command.length() << std::endl;\n' \
		   '\t\tstream << "Received invalid command: <"' \
		   ' \n\t\t\t<< command << "> at X_NAME_X";\n' \
		   '\t\tstream << std::endl << "Haeh?" << std::endl;\n' \
		   '\t\tstream.flush();\n' \
		   '\t\tthrow std::runtime_error(stream.str().c_str());'\
		   '\n\t }\n'
	file.write(string.replace(string.replace(temp1,'X_CODE_X',sendCode),
               'X_NAME_X', name_))

def printUsage():
	sys.stderr.write("""Usage: nic.py <command> <outputpath> <interface-file>
    where
     <command> ::= ir|is|nrh|nrc|nsh|nsc
     <outputpath> ::= 'any valid path'
     <interface-file> ::= 'any filename'\n""")


def scanSpecfile(specFile):
	(id,options) = readBlock(specFile)

	inputs = readRekBlock(specFile)
	outputs = readRekBlock(specFile)

	return ((id,options),inputs,outputs)

if len(sys.argv) != 4:	
	printUsage()
	sys.exit(-1)

cmd = sys.argv[1]
path = sys.argv[2]
interfaceFilename = sys.argv[3]

if not cmd in ['ir','is','nrh','nrc','nsh','nsc','iam','nam']:
	sys.stderr.write('Error, wrong command: ' + cmd + '\n')
	printUsage()
	sys.exit(-1)


file = open(interfaceFilename,"r")
(header,comment,interface) = readInterface(file)
baseName = header['name']

#createIfaceRecHeader(sys.stdout,header['name'],interface)
#createIfaceSendHeader(sys.stdout,header['name'])
#createNetIfaceRecHeader(sys.stdout,header['name'],interface)
#createNetIfaceSendHeader(sys.stdout,header['name'])
#createNetIfaceRecImpl(sys.stdout,header['name'],interface)
#createNetIfaceSendImpl(sys.stdout,header['name'],interface)



if cmd == 'ir':
	filename = os.path.join(path,
				'i' + string.lower(baseName) + 'receiver.h')
	file = open(filename,'w')
	print "Writing interface receiver file to " + filename
	createIfaceRecHeader(file,baseName,comment,interface)
	file.close()
elif cmd == 'is':
	filename = os.path.join(path,
				'i' + string.lower(baseName) + 'sender.h')
	file = open(filename,'w')
	print "Writing interface receiver file to " + filename
	createIfaceSendHeader(file,baseName)
	file.close()
elif cmd == 'nrh':
	filename = os.path.join(path,
				string.lower(baseName) + 'receivernet.h')
	file = open(filename,'w')
	print "Writing net interface receiver header file to " + filename
	createNetIfaceRecHeader(file,baseName,interface)
	file.close()
elif cmd == 'nsh':
	filename = os.path.join(path,
				string.lower(baseName) + 'sendernet.h')
	file = open(filename,'w')
	print "Writing net interface sender header file to " + filename
	createNetIfaceSendHeader(file,baseName)
	file.close()
elif cmd == 'nrc':
	filename = os.path.join(path,
				string.lower(baseName) + 'receivernet.cpp')
	file = open(filename,'w')
	print "Writing net interface receiver c++ file to " + filename
	createNetIfaceRecImpl(file,baseName,interface)
	file.close()
elif cmd == 'nsc':
	filename = os.path.join(path,
				string.lower(baseName) + 'sendernet.cpp')
	file = open(filename,'w')
	print "Writing net interface sender c++ file to " + filename
	createNetIfaceSendImpl(file,baseName,interface)
	file.close()
elif cmd == 'iam':
	template = 'iX_NAME_Xreceiver.h: X_NAME_X.if\n' \
		   '\tpython $(top_builddir)/nic.py ir . X_NAME_X.if\n\n'\
		   'iX_NAME_Xsender.h: X_NAME_X.if\n' \
		   '\tpython $(top_builddir)/nic.py is . X_NAME_X.if\n'

	print 'Appending build rules to Makefile.am...'
	file = open('Makefile.am','a')
	file.write(string.replace(template,'X_NAME_X',
				  string.lower(baseName)))


elif cmd == 'nam':
	template = """
X_NAME_Xreceivernet.h: ../interfaces/X_NAME_X.if
	python $(top_builddir)/nic.py nrh . ../interfaces/X_NAME_X.if

X_NAME_Xreceivernet.cpp: ../interfaces/X_NAME_X.if X_NAME_Xreceivernet.h
	python $(top_builddir)/nic.py nrc . ../interfaces/X_NAME_X.if

X_NAME_Xsendernet.h: ../interfaces/X_NAME_X.if
	python $(top_builddir)/nic.py nsh . ../interfaces/X_NAME_X.if

X_NAME_Xsendernet.cpp: ../interfaces/X_NAME_X.if X_NAME_Xsendernet.h
	python $(top_builddir)/nic.py nsc . ../interfaces/X_NAME_X.if"""

	print 'Appending build rules to Makefile.am...'
	file = open('Makefile.am','a')
	file.write(string.replace(template,'X_NAME_X',
				  string.lower(baseName)))



