#!/usr/bin/python
#TODO:
#      die ganzen checks

import re, sys, string, os

#
# regular expressions for scanning:
#
# begin of a block (for example "\t  { \n")
beginblock_string = r"^\s*\{\s*$"
endblock_string   = r"^\s*\}\s*$"

# something like "\tabc\t"
identifier_string = r"^\s*(?P<id>[a-zA-z_0-9-][a-zA-Z0-9 \t_-]*)\s*$"

# something like "agag = 100"
assignment_string = r"\s*(?P<name>.*)\s*=\s*(?P<value>.*)\s*"

beginblock = re.compile(beginblock_string)
endblock = re.compile(endblock_string)
identifier = re.compile(identifier_string)
assignment = re.compile(assignment_string)
emptyline = re.compile(r"\s*");

def removeComment(s):
        " Entfernt alles ab einem '#' Zeichen aus dem String s"
        p = string.find(s,'#')
        if p != -1:
                return s[:p]
        else:
                return s

def readBlock(file):
        " Liest einen Block aus file. wenn keiner da ist wird ('',[])"
        " zurueckgegeben. Wenn eine schliessende Klammer gelesen wird,"
        " wird None zurueckgegeben. "
        line = ' '
        id = ''
        pairs = {}
        matchedEndBlock = 0

        while line != '':
                line = file.readline()
                strippedLine = removeComment(line)
                m = identifier.match(strippedLine)
                if m:
                        id = m.group('id')
                        break
                elif endblock.match(strippedLine):
                        return None

        if id == '':
                sys.stderr.write("Module identifier missing!\n")
                sys.stderr.write("Line = " + line + "\n");
                return ('',{})

        while line != '':
                line = file.readline()
                strippedLine = removeComment(line)
                m = beginblock.match(strippedLine)
                if m:
                        break
        if line == '':
                sys.stderr.write("{ missing!\n")
                sys.exit(1)

        while line != '':
                line = file.readline()
                strippedLine = removeComment(line)
                m = assignment.match(strippedLine)
                if m:
                        name  = string.strip(m.group('name'))
                        value = string.strip(m.group('value'))
                        pairs[name] = value
                elif endblock.match(strippedLine):
                        matchedEndBlock = 1
                        break;
                elif emptyline.match(strippedLine):
                        continue;
                else:
                        sys.stderr.write("Error: " + line + " at line " \
                                         + `1` + "\n");
                        
        if matchedEndBlock == 0:
              sys.stderr.write("Error: missing }\n");
        
        return (id, pairs)

def readRekBlock(file):
        " Liest einen Block aus file der wieder Blocks als Eintraege hat. "
        " Es wird eine Liste von Blocks zurueckgegeben."
        line = ' '
        id = ''
        pairs = {}
        matchedEndBlock = 0

        while line != '':
                line = file.readline()
                strippedLine = removeComment(line)
                m = identifier.match(strippedLine)
                if m:
                        id = m.group('id')
                        break

        if id == '':
                sys.stderr.write("Block identifier missing!\n")
                sys.stderr.write("Line = '" + line + "'\n");
                sys.exit(1)

        while line != '':
                line = file.readline()
                strippedLine = removeComment(line)
                m = beginblock.match(strippedLine)
                if m:
                        break
        if line == '':
                sys.stderr.write("{ missing!\n")
                sys.exit(1)

        blocks = []
        while 1:
                block = readBlock(file)
                if block:
                        if block[0] == '':
                                break
                        blocks.append(block)
                else:
                        matchedEndBlock = 1
                        break


        if matchedEndBlock == 0:
              sys.stderr.write("Error: missing }\n");
        
        return blocks

def checkMapForKeys(map,keys):
        if len(keys) == 0:
                return ""
        else:
           if not map.has_key(keys[0]):
                return keys[0]
           else:
                return checkMapForKeys(map,keys[1:])
                

def checkType(s,type):
        if type == 'text':
                return 1
        elif type == 'bool':
                return s == 'true' or s == 'false'
        elif type == 'path':
                return 1
        else:
                return 0

def checkKeyTypes(map,keys):
        if len(keys) == 0:
                return 1
        else:
                return checkType(map[keys[0][0]],keys[0][1]) and checkKeyTypes(map,keys[1:])

def checkModuleOptions(id, options):    
        "Ueberprueft ob der Module Block ok ist"
        error = checkMapForKeys(options,['name','group','deterministic','xpm'])
        if error != "":
                sys.stderr.write("Missing Key! " + error +'\n')
                sys.exit(1)

        error = checkMapForKeys(options,['author','version'])
        if error != '':
                sys.stderr.write("Warning! Missing Key! " + error +'\n')

        if not checkKeyTypes(options,[('name','text'),('group','text'),
                                      ('deterministic','bool'),('xpm','path')]):
                sys.stderr.write('Type error!=!?!\n')

def checkInputs(inputs):
        "Ueberprueft ob der Inputs Block ok ist"
        return

def checkOutputs(outputs):
        "Ueberprueft ob der Outputs Block ok ist"
        return


def usesStrongDepFeature(inputs):
        if inputs == []:
                return 0
        
        list = map(lambda x: x[1]['strong_dependency'] == 'false', inputs)
        uses = reduce(lambda x, y: x or y, list)
        return uses
        

def usesAttributesFeature(inputs):
        if inputs == []:
                return 0
        
        list = map(lambda x: x[1].has_key('attributes'), inputs)        
        uses = reduce(lambda x, y: x or y, list)
        
        return uses

def usesPatchFeature(options):
        return options.has_key('enablePatching') and options['enablePatching'] == 'true'
                


def createModuleSpec(id, options, numberOfInputs, numberOfOutputs):
        return "mod_spec { " + "name=[" + id \
                + "] number_of_inputs=[" +  `numberOfInputs`  \
                + "] number_of_outputs=[" + `numberOfOutputs` \
                + "] deterministic=[" + options['deterministic'] + "] }"

def createInputSpec(input):
        (id,options) = input
        if options.has_key('default'):
                default = 'default=['+options['default']+']'
        else:
                default = ''

        return "input_spec { type=" + options['type'] + \
                            " id=" + id + \
                            " const=" + options['const'] + \
                            " strong_dependency=" + \
                            options['strong_dependency'] + ' ' \
                            + default + " } "

def createInputSpecs(inputs):
        specs = []
        for i in range(0,len(inputs)):
                spec = createInputSpec(inputs[i])
                specs.append(spec)

        return specs

def createOutputSpec(input):
        (id,options) = input
        return "output_spec { type=" + options['type'] +\
                            " id=" + id + " } "

def createOutputSpecs(outputs):
        specs = []
        for i in range(0,len(outputs)):
                spec = createOutputSpec(outputs[i])
                specs.append(spec)

        return specs

def getTypeName(typeID):
        return string.replace(typeID,'typ_','')

def getInputVarName(input):
        id, options = input
        return "in_" + id
        
def getInputVarDecl(input):
        id, options = input
        return ' ' + getTypeName(options['type']) + '* ' + getInputVarName(input) + ';\n'

def getOutputVarName(output):
        id, options = output
        return "out_" + id

def getOutputVarDecl(output):
        id, options = output
        return ' ' + getTypeName(options['type']) + '* ' + getOutputVarName(output) + ';\n'

def createStruct(inputs, outputs):
       prelog =  "struct _MyInstance;\ntypedef struct _Instance\n{\n" \
                 "struct _MyInstance* my;\n"
       epilog = "} Instance, *InstancePtr;"

       if len(inputs) > 0:
               inputvars = reduce(lambda a, b: a + b,
                                  map(getInputVarDecl,inputs))
       else:
               inputvars = ''   

       if len(outputs) > 0:
               outputvars = reduce(lambda a, b: a + b,
                                   map(getOutputVarDecl,outputs))
       else:
                outputvars = ''

       return prelog + inputvars + outputvars + epilog

def createEnums(inputs, outputs):                                         
        if len(inputs) > 0:
                   prelog = "enum Inputs { "
                   numbers = range(0,len(inputs))
                   names = map(getInputVarName,inputs)
                   enumList = map(lambda a, b: a + ' = ' + `b`,names, numbers)
                   enumContent = reduce(lambda a, b: a + ', ' + b ,enumList)
                   inputEnum = prelog + enumContent + ' };\n'
                                  
        else:
               inputEnum = ''

        if len(outputs) > 0:
                   prelog = "enum Outputs { "
                   numbers = range(0,len(outputs))
                   names = map(getOutputVarName,outputs)
                   enumList = map(lambda a, b: a + ' = ' + `b`,names, numbers)
                   enumContent = reduce(lambda a, b: a + ', ' +  b ,enumList)
                   outputEnum = prelog + enumContent + ' };\n'
                                  
        else:
               outputEnum = ''  
       

        return inputEnum + outputEnum


def putInDict(dict, x):
        dict[x] = 1

def make_unique(list):
        dict = {}
        map(lambda x, d=dict: putInDict(d,x), list)
        return dict.keys()

def createUsedTypes(inputs, outputs):
        typelist = make_unique(map(lambda x: x[1]['type'],inputs+outputs))
        return typelist

def createTypeIncludes(inputs,outputs):
        typelist = map(lambda x: string.lower(string.replace(x,'typ_','')),
                       createUsedTypes(inputs,outputs))


        typeincludes = reduce(lambda a,b: a+ b,
                               map(lambda x: '#include "' + x + '.h"\n',
                                   typelist))

        return typeincludes

def createPrelog(xpmfile,inputs, outputs, fileprefix, id):
        structinclude = '#include "' + fileprefix + '.h' + '"\n'
        stdincludes = '#include <stdlib.h>\n//#include <assert.h>\n' \
                      '//#include <stdio.h>\n//#include <string.h>\n' \
                      '#include "dllutils.h"\n'

        logstuffr = """
static log2T s_log_function = 0;

static void logger(int level, const char* msg)
{
   if (s_log_function)
      s_log_function(level, \"XXX_MODULE_CLASS_NAME_XXX\", msg);
}
"""
        logstuff = string.replace(logstuffr,'XXX_MODULE_CLASS_NAME_XXX', id)


        return structinclude + stdincludes + '#include "' + xpmfile + '"\n' + logstuff
        
        
def createSetInput(inputs):
        prelog = "int setInput(void* instance,int index,void* typePointer)\n{"\
                 "\n InstancePtr inst = (InstancePtr) instance;\n"\
                 " switch(index) {\n"
                
        epilog = " } //switch(index) \n return 1;\n}"

        caseList = []
        for i in range(0,len(inputs)):
                input = inputs[i]
                caseList.append("  case " + `i` + ":\n   inst->" + \
                                getInputVarName(input) + \
                                ' = (' + getTypeName(input[1]['type']) + \
                                ' *) typePointer;\n  break;\n')
        
        if caseList != []:
                cases = reduce(lambda a, b: a + b, caseList)
        else:
                cases = ''

        return prelog + cases + epilog


def createSetOutput(outputs):
        prelog = "int setOutput(void* instance,int index, void* typePointer)\n{"\
                 "\n InstancePtr inst = (InstancePtr) instance;\n"\
                 " switch(index) {\n"
                
        epilog = " } //switch(index) \n return 0;\n}"

        caseList = []
        for i in range(0,len(outputs)):
                output = outputs[i]
                caseList.append("  case " + `i` + ":\n   inst->" + \
                                getOutputVarName(output) + \
                                ' = (' + getTypeName(output[1]['type']) \
                                + '* ) typePointer;\n  break;\n')

        if caseList != []:       
                cases = reduce(lambda a, b: a + b, caseList)
        else:
                cases = ''

        return prelog + cases + epilog

def createSpecFunctions(module_spec, input_specs, output_specs):
        moduleFunc = 'const char* getSpec(void) {\n return "' \
                     +  module_spec + '";\n}'

        inputSpecPrelog = 'const char* getInputSpec(int index) {\n' \
                          + ' switch(index) {\n '

        caseList = []
        for i in range(0,len(input_specs)):
                caseList.append("  case " + `i` + ':\n    return "' + \
                                input_specs[i] + '";\n  break;\n')

        if caseList != []:
                inputCases = reduce(lambda a, b: a + b, caseList)
        else:
                inputCases = ''

        inputFunc = inputSpecPrelog + inputCases + ' }\n return 0;\n}'

        outputSpecPrelog = 'const char* getOutputSpec(int index) {\n' \
                          + ' switch(index) {\n '
        caseList = []
        for i in range(0,len(output_specs)):
                caseList.append("  case " + `i` + ':\n    return "' + \
                                output_specs[i] + '";\n  break;\n')

        if caseList != []:
                outputCases = reduce(lambda a, b: a + b, caseList)
        else:
                outputCases = ''

        outputFunc = outputSpecPrelog + outputCases + ' }\n return 0;\n}'

        return moduleFunc + '\n' + inputFunc + '\n' + outputFunc

def isExtraInputArgument(name):
        return not name in ['name','type','default','const','strong_dependency','attributes']

def isExtraOutputArgument(name):
        return not name in ['name','type']

def inputToInfo(input):
        id,options = input
        filteredOptions = filter(lambda x: isExtraInputArgument(x[0]),
                                 options.items())

        if len(filteredOptions) > 0:
          args = reduce(lambda x, y: x + y,map(lambda x: x[0]+'=['+x[1]+'] ',
                                               filteredOptions))

          return options['name'] + '{' + args + '} '
        else:
          return options['name'] + ' '

def outputToInfo(output):
        id,options = output
        filteredOptions = filter(lambda x: isExtraOutputArgument(x[0]),
                                 options.items())
 
        if len(filteredOptions) > 0:
          args = reduce(lambda x, y: x + y,map(lambda x: x[0]+'=['+x[1]+'] ',
                                               filteredOptions))

          return options['name'] + '{' + args + '} '
        else:
          return options['name'] + ' '
        
def createInputInfoArray(inputs):
        if len(inputs) == 0:
                return '0'
        else:
                entries = reduce(lambda x, y: x + y,map(inputToInfo,inputs))
                return `len(inputs)` + ' ' + entries

def createOutputInfoArray(outputs):
        if len(outputs) == 0:
                return '0'
        else:
                entries = reduce(lambda x, y: x + y,map(outputToInfo,outputs))
                return `len(outputs)` + ' ' + entries


def createGetInfo(options,inputs,outputs):
        template = """
int getInfo(char* buf,int bufLen)
{
  static const char* INFO = XXX_INFOSTRING_XXX;
  char* tmpBuf;
  int reqLen = 1 + strlen(INFO) + getSizeOfXPM(XXX_XPMNAME_XXX);
  if (buf != 0 && reqLen <= bufLen)
    {
      char* offset;
      int i;
      int lines = getNumberOfStringsXPM(XXX_XPMNAME_XXX);
      tmpBuf = (char*) malloc(reqLen);
          if (tmpBuf == 0)
          {
             printf("Could not allocate memory in getInfo\\n");
                 return 0;
          }
      memcpy(tmpBuf,INFO,strlen(INFO)+1);
      offset = tmpBuf + strlen(INFO) + 1;
      for (i = 0; i < lines; ++i)
        {
          char* source = XXX_XPMNAME_XXX[i];
          memcpy(offset,source,strlen(source)+1);
          offset += strlen(source) + 1;
        }                       
      memcpy(buf,tmpBuf,reqLen);
      free(tmpBuf);
    }
  return reqLen;        
}
"""
        inputArray = createInputInfoArray(inputs)
        outputArray = createOutputInfoArray(outputs)
        
        
        # TODO
        infoString = '"info { name=[' + options['name'] + '] group=[' \
                     + options['group'] + '] inputs=[' + inputArray + \
                     '] outputs=[' + outputArray + '] type=xpm } "'
        xpmName = string.replace(options['xpm'],'.xpm','_xpm');
        return string.replace(string.replace(template,
                                             'XXX_XPMNAME_XXX', xpmName),
                              'XXX_INFOSTRING_XXX',infoString)

def createCtorDtor(static):
        template = """void* newInstance()
{
  Instance* inst = (Instance*) malloc(sizeof(Instance));

  if (inst == 0)
  {
          logger(0, "Could not allocate memory for instance struct!\\n");
          return 0;
  }

  inst->my = construct();

  if (inst->my == 0)
  {
    free(inst);
    return 0;
  }

  return inst;
}

void deleteInstance(void* instance)
{
  Instance* inst = (Instance*) instance;

  destruct(inst->my);

  free(inst);
}
"""
        templateStatic = """static struct _MyInstance* s_inst = 0;
static int s_ref_count = 0;

void* newInstance()
{
  Instance* inst = (Instance*) malloc(sizeof(Instance));

  if (inst == 0)
  {
          logger(0, "Could not allocate memory for instance struct!\\n");
          return 0;
  }

  s_ref_count += 1;

  if (s_ref_count == 1)
  {
    s_inst = construct();
    if (s_inst == 0)
    {
      free(inst);
      s_ref_count = 0;
      return 0;
    }
  }
  
  inst->my = s_inst;    

  return inst;
}

void deleteInstance(void* instance)
{
  Instance* inst = (Instance*) instance;

  s_ref_count -= 1;

  if (s_ref_count == 0)
        destruct(s_inst);
        
  free(inst);
}
"""

        if string.lower(static) == 'true':
                return templateStatic
        else:
                return template
                
        
def createStrongDepFunc(inputs):
        template = """void strongDependenciesCalculated(void* instance,int** neededInputs)
{
  InstancePtr inst = (InstancePtr) instance;

  static int neededIns[X_NUMINS_X];
  *neededInputs = neededIns;
        
X_INI_LIST_X


  strongDependencies(inst, neededIns);
}
"""
        names = map(getInputVarName,inputs)
        list = []
        for i in range(0,len(inputs)):
                if inputs[i][1]['strong_dependency'] == 'true':
                        val = '0;\n'
                else:
                        val = '1;\n'
                list.append('\tneededIns[' + names[i] + '] = ' + val)

        iniList = reduce(lambda x,y: x + y, list)
        return string.replace(string.replace(template,'X_NUMINS_X',
                                             `len(inputs)`),
                              'X_INI_LIST_X',iniList)

def createPatchFunc(outputs):
        template = """void getPatchLayout(void* instance,int** out2in)
{
  InstancePtr inst = (InstancePtr) instance;

  static int out2in_[X_NUMOUTS_X];
  *out2in = out2in_;
        
X_INI_LIST_X


  patchLayout(inst, out2in_);
}
"""
        names = map(getOutputVarName,outputs)
        list = []
        for i in range(0,len(outputs)):         
                list.append('\tout2in_[' + names[i] + '] = -1;')

        iniList = reduce(lambda x,y: x + y, list)
        return string.replace(string.replace(template,'X_NUMOUTS_X',
                                             `len(outputs)`),
                              'X_INI_LIST_X',iniList)


def typeName2AttributeStruct(name):
        return string.replace(string.replace(name,'Type','Attributes'),'typ_','')

def createAttribDecls(inputs):
        'creates declaration code for all fixed attributes'

        if len(inputs) == 0:
                return ''

        decls = []
        for i in range(0,len(inputs)):          
                if inputs[i][1].has_key('attributes'):
                        decls.append('static ' + typeName2AttributeStruct(inputs[i][1]['type'])\
                                                 + ' attr' + `i` + ';\n')

        return reduce(lambda x, y: x + y, decls)


def createAttribBlock(val, name):
        'creates init code for one fixed attribute'
        code_ = string.replace(val,'~','=')
        code = string.replace(code_,'a$', name)

        return code + '\n'

def createAttribBlocks(inputs):
        'creates init code for all fixed attributes'
        
        code = []
        for i in range(0,len(inputs)):
                if inputs[i][1].has_key('attributes'):
                        code.append(createAttribBlock(inputs[i][1]['attributes'], 'attr' + `i`))
                        code.append('\tattributes[' + `i` + '] = &attr' + `i` + ';'); 
                else:
                        code.append('')

        return reduce(lambda x, y: x + y, code)

                
def createCFile(id,options,inputs,outputs,file,fileprefix):
        prelog = createPrelog(options['xpm'],inputs,outputs,fileprefix,id)

        static = options.get('static','false')
        module_spec = createModuleSpec(id,options,len(inputs),len(outputs))
        input_specs = createInputSpecs(inputs)
        output_specs = createOutputSpecs(outputs)
        ctor_dtor = createCtorDtor(static)
        setInput = createSetInput(inputs)
        setOutput = createSetOutput(outputs)
        specFuncs = createSpecFunctions(module_spec,input_specs,output_specs)
        getInfo = createGetInfo(options,inputs,outputs)

        if usesStrongDepFeature(inputs):
                strongDepFunc = createStrongDepFunc(inputs)
        else:
                strongDepFunc = ''

        if usesAttributesFeature(inputs):
                attributeInitCode = 'initAttributes();'
        else:
                attributeInitCode = ''

        initTemplate = """
int initSO(log2T log_function) 
{
        s_log_function = log_function;
        
        XXX_ATTRIB_CODE

        return init(logger);
}
"""
        initFunc = string.replace(initTemplate, 'XXX_ATTRIB_CODE', attributeInitCode)

        file.write(prelog)
        file.write('\n')

        file.write(specFuncs)
        file.write('\n')

        file.write(ctor_dtor)
        file.write('\n')

        file.write(setInput)
        file.write('\n')

        file.write(setOutput)
        file.write('\n')

        file.write(getInfo)
        file.write('\n')

        file.write(strongDepFunc)
        file.write('\n')

        if usesPatchFeature(options):
                file.write(createPatchFunc(outputs))
                file.write('\n')        

        
        fixedAttributesTemplate = """static void* attributes[XXX_NUMINPUTS_XXX];

void initAttributes()
{
        XXX_DECLS_XXX
        int i = 0;

        for (i = 0; i < XXX_NUMINPUTS_XXX; ++i)
                attributes[i] = 0;

        XXX_BLOCKS_XXX  

}

void* getInputAttributes(int index)
{
        return attributes[index];
}
        """
        if usesAttributesFeature(inputs):       
                
                decls = createAttribDecls(inputs)
                blocks = createAttribBlocks(inputs)
                attributesCode__ = \
                        string.replace(fixedAttributesTemplate,'XXX_NUMINPUTS_XXX',`len(inputs)`)
                attributesCode_ =  \
                        string.replace(attributesCode__,'XXX_BLOCKS_XXX',blocks)
                attributesCode = \
                        string.replace(attributesCode_,'XXX_DECLS_XXX',decls)
                

                file.write(attributesCode)
                file.write('\n')


        file.write(initFunc)
        



def createHFile(inputs,outputs,file,filename):
        struct = createStruct(inputs,outputs)
        enums = createEnums(inputs, outputs)

        macroName = string.upper(string.replace(filename,'.','_'))

        file.write('#ifndef INCLUDED_' + macroName + '\n')
        file.write('#define INCLUDED_' + macroName + '\n')
        file.write('\n')
        file.write('#ifdef __cplusplus\nextern "C"\n{\n#endif\n');
        file.write('#include "dllmodule.h"\n')
        file.write(createTypeIncludes(inputs,outputs))
        file.write('\n')
        file.write(struct)
        file.write('\n')
        file.write(enums)
        file.write('\n')
        file.write('struct _MyInstance* construct(void);\n')
        file.write('void destruct(struct _MyInstance*);\n')
        file.write('int init(logT log_function);\n')
        if usesStrongDepFeature(inputs):
                file.write('void strongDependencies(Instance*,int[]);\n')

        if usesPatchFeature(options):
                file.write('void patchLayout(Instance*,int[]);\n')

        file.write('#ifdef __cplusplus\n}\n#endif\n');

        file.write('\n#endif\n')

def createSkelFile(file, fileprefix, inputs):
        file.write('#include "' + fileprefix + '.h' + '"\n\n')
#       file.write('#include "dllmodule.h"\n\n')
        template = """static logT s_log;

typedef struct _MyInstance {

 int dummy; // replace this with your favourite vars

} MyInstance, *MyInstancePtr;

int init(logT log_function)
{
  s_log = log_function;
  
  return 1;
}

void shutDown(void)
{
}

MyInstance* construct()
{
  MyInstance* my = (MyInstancePtr) malloc(sizeof(MyInstance));

  if (my == 0)
  {
          s_log(0, "Could not allocate memory for MyInstance struct\\n");
          return 0;
  }

  // Add your initialization here

  return my;
}

void destruct(MyInstance* my)
{
  // Add your cleanup here
  free(my);
}

void update(void* instance)
{
  InstancePtr inst = (InstancePtr) instance;
  MyInstancePtr my = inst->my;

  // Add your effect here!
}

"""
        strongDepTemplate = """void strongDependencies(Instance* inst, int neededInputs[])
{
        // set the inputs to 0 that are not needed!
}

"""

        patchTemplate = """void patchLayout(Instance* inst, int out2in[])
{
        // set the outputs to the patched inputs
}

"""

        file.write(template);
        if usesStrongDepFeature(inputs):
                file.write(strongDepTemplate)

        if usesPatchFeature(options):
                file.write(patchTemplate)
        

def createAMFile(file, fileprefix, inputs, outputs):
        template = """libdir = @libdir@/gephex-0.4/modules

PLUC=python @top_srcdir@/modules/pluc.py

XXX_NAME_XXX_auto.c: XXX_NAME_XXX.spec XXX_NAME_XXX.h
	$(PLUC) c @srcdir@/XXX_NAME_XXX.spec

XXX_NAME_XXX.h: XXX_NAME_XXX.spec
	$(PLUC) h @srcdir@/XXX_NAME_XXX.spec

lib_LTLIBRARIES = XXX_NAME_XXX.la

XXX_NAME_XXX_la_SOURCES = \\
        XXX_NAME_XXX_auto.c \\
        XXX_NAME_XXX.c \\
        XXX_NAME_XXX.h \\
        XXX_NAME_XXX.spec \\
        XXX_NAME_XXX.xpm

XXX_NAME_XXX_la_LDFLAGS = -module -avoid-version -no-undefined

INCLUDES = -I@srcdir@/../../../engine/src/engine \\
           -I@srcdir@/../../../util/include \\
XXX_TYPE_INCLUDES_XXX


DISTCLEANFILES = XXX_NAME_XXX.h XXX_NAME_XXX_auto.c

#EXTRA_DIST = XXX_NAME_XXX.dsp XXX_NAME_XXX.mak XXX_NAME_XXX.dep

"""
        usedtypes = createUsedTypes(inputs,outputs)
        typedirs = map(lambda y: string.replace(y,'typ_',''),
                       usedtypes)

        typeinclude = ''

        typeincludes = map(lambda x: '           -I@srcdir@/../../../types/src/' + 
                           string.lower(x) +' ', typedirs)
        typeinclude = reduce(lambda x,y: x + '\\\n' + y,typeincludes)


        am = string.replace(string.replace(template,'XXX_NAME_XXX',fileprefix),
                            'XXX_TYPE_INCLUDES_XXX',typeinclude)

        file.write(am)

def createDefFile(file,fileprefix,inputs,options):
        template = """LIBRARY XXX_NAME_XXX
DESCRIPTION "description"
EXPORTS

 newInstance @1
 deleteInstance @2
 getSpec @3
 setInput @4
 setOutput @5
 update @6
 getInputSpec @7
 getOutputSpec @8
 getInfo @9
 initSO @10
 shutDown @11
"""

        content = string.replace(template,'XXX_NAME_XXX',
                                  string.upper(fileprefix)) 
        file.write(content)

        if usesStrongDepFeature(inputs):
                file.write('strongDependenciesCalculated @12\r\n')
        
        if usesAttributesFeature(inputs):
                file.write('getInputAttributes @13\r\n')
                
        if usesPatchFeature(options):
                file.write('getPatchLayout @14\r\n')


def createDspFile(file, fileprefix):
        template = r"""# Microsoft Developer Studio Project File - Name="X_NAME_X" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** NICHT BEARBEITEN **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=X_NAME_X - Win32 Debug
!MESSAGE Dies ist kein gueltiges Makefile. Zum Erstellen dieses Projekts mit NMAKE
!MESSAGE verwenden Sie den Befehl "Makefile exportieren" und fuehren Sie den Befehl
!MESSAGE 
!MESSAGE NMAKE /f "X_NAME_X.mak".
!MESSAGE 
!MESSAGE Sie koennen beim Ausfuehren von NMAKE eine Konfiguration angeben
!MESSAGE durch Definieren des Makros CFG in der Befehlszeile. Zum Beispiel:
!MESSAGE 
!MESSAGE NMAKE /f "X_NAME_X.mak" CFG="X_NAME_X - Win32 Debug"
!MESSAGE 
!MESSAGE Fuer die Konfiguration stehen zur Auswahl:
!MESSAGE 
!MESSAGE "X_NAME_X - Win32 Release" (basierend auf  "Win32 (x86) Dynamic-Link Library")
!MESSAGE "X_NAME_X - Win32 Debug" (basierend auf  "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "X_NAME_X - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "X_NAME_X_EXPORTS" /YX /FD /c
# ADD CPP /nologo /G6 /MD /W3 /GX /O2 /Ob2 X_TYPEINCLUDES_X /I "../../../engine/src/engine" /I "../../../" /I "../../../util/include" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "X_NAME_X_EXPORTS" /D "WIN32" /D "NDEBUG" /D "HAVE_CONFIG_H" /YX /FD /c
# SUBTRACT CPP /X
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x407 /d "NDEBUG"
# ADD RSC /l 0x407 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /machine:I386
# Begin Special Build Tool
TargetPath=.\Release\X_NAME_X.dll
SOURCE="$(InputPath)"
PostBuild_Desc=Kopiere Dll...
PostBuild_Cmds=copy $(TargetPath) ..\..\..\dlls\modules
# End Special Build Tool

!ELSEIF  "$(CFG)" == "X_NAME_X - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "X_NAME_X_EXPORTS" /YX /FD /GZ /c
# ADD CPP /nologo /G6 /MDd /W2 /Gm /GX /ZI /Od X_TYPEINCLUDES_X /I "../../../" /I "../../../engine/src/engine" /I "../../../util/include" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "X_NAME_X_EXPORTS" /D "WIN32" /D "_DEBUG" /D "HAVE_CONFIG_H" /YX /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x407 /d "_DEBUG"
# ADD RSC /l 0x407 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /debug /machine:I386 /nodefaultlib:"msvcrt" /nodefaultlib:"winspool" /nodefaultlib:"comdlg32" /nodefaultlib:"uuid" /nodefaultlib:"odbc32" /nodefaultlib:"odbccp32" /nodefaultlib:"oleaut32" /pdbtype:sept
# SUBTRACT LINK32 /incremental:no
# Begin Special Build Tool
TargetPath=.\Debug\X_NAME_X.dll
SOURCE="$(InputPath)"
PostBuild_Desc=Kopiere Dll...
PostBuild_Cmds=copy $(TargetPath) ..\..\..\dlls\modules
# End Special Build Tool
!ENDIF 

# Begin Target

# Name "X_NAME_X - Win32 Release"
# Name "X_NAME_X - Win32 Debug"
# Begin Group "Quellcodedateien"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\X_NAME_X.c

!IF  "$(CFG)" == "X_NAME_X - Win32 Release"

!ELSEIF  "$(CFG)" == "X_NAME_X - Win32 Debug"

# ADD CPP /MDd

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\X_NAME_X_auto.c
# End Source File
# End Group
# Begin Group "Header-Dateien"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\X_NAME_X.h
# End Source File
# End Group
# Begin Group "Ressourcendateien"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# End Group
# Begin Source File

SOURCE=.\X_NAME_X.def
# End Source File
# Begin Source File

SOURCE=.\X_NAME_X.spec

!IF  "$(CFG)" == "X_NAME_X - Win32 Release"

# Begin Custom Build
InputPath=.\X_NAME_X.spec
InputName=X_NAME_X

BuildCmds= \
	python ..\..\pluc.py c $(InputName).spec \
	python ..\..\pluc.py h $(InputName).spec \
	python ..\..\pluc.py def $(InputName).spec \


"$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputName)_auto.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputName).def" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "X_NAME_X - Win32 Debug"

# Begin Custom Build
InputPath=.\X_NAME_X.spec
InputName=X_NAME_X

BuildCmds= \
	python ..\..\pluc.py c $(InputName).spec \
	python ..\..\pluc.py h $(InputName).spec \
	python ..\..\pluc.py def $(InputName).spec \
        

"$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputName)_auto.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputName).def" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\X_NAME_X.xpm
# End Source File
# End Target
# End Project

"""
        name = fileprefix       

        content = string.replace(template,'X_NAME_X',name)

        usedtypes = createUsedTypes(inputs,outputs)
        typedirs = map(lambda y: string.replace(y,'typ_',''),
                       usedtypes)
        typeincludes = map(lambda x: '/I "../../../types/src/' + 
                           string.lower(x) +'" ',
                           typedirs)
        typeinclude = reduce(lambda x,y: x + y,typeincludes)

        content = string.replace(content,'X_TYPEINCLUDES_X',typeinclude)

        file.write(content)

def removeExtension(filename):
        p = string.rfind(filename,'.')
        if p != -1:
                return filename[:p]
        else:
                return filename

def printUsage():
        sys.stderr.write("""Usage: pluc.py <command> <specfile>
    where
     <command> ::= c|h|am|def|dsp|skel
     <specfile> ::= 'any filename'\n""")


def scanSpecfile(specFile):
        (id,options) = readBlock(specFile)

        inputs = readRekBlock(specFile)
        outputs = readRekBlock(specFile)

        return ((id,options),inputs,outputs)

if len(sys.argv) != 3:  
        printUsage()
        sys.exit(-1)


cmd = sys.argv[1]
specfileName = sys.argv[2]

if not cmd in ['c','h','skel','am','def','dsp']:
        sys.stderr.write('Error, wrong command: ' + cmd + '\n')
        printUsage()
        sys.exit(-1)

try:
        specFile = open(specfileName,'r')
except IOError:
        sys.stderr.write('Error, couldnt open ' + specfileName + '\n')
        sys.exit(-1)
        
        
((id,options),inputs,outputs) = scanSpecfile(specFile)

checkModuleOptions(id,options)
checkInputs(inputs)
checkOutputs(outputs)

(tmp,filename_ext) = os.path.split(specfileName)
fileprefix = removeExtension(filename_ext)

if cmd == 'c':
        filename = fileprefix + '_auto.c'
        file = open(filename,'w')
        print "Writing cfile to " + filename
        createCFile(id,options,inputs,outputs,file,fileprefix)
        file.close()
elif cmd == 'h':
        filename = fileprefix + '.h'
        file = open(filename,'w')
        print "Writing header to " + filename
        createHFile(inputs,outputs,file, filename)
        file.close()
elif cmd == 'skel':
        filename = fileprefix + '.c'
        if os.access(filename,os.F_OK):
                sys.stderr.write(filename + ' already exists! aborting.\n')
                sys.exit(-1)
        file = open(filename,'w')
        print "Writing skel to " + filename
        createSkelFile(file, fileprefix,inputs)
        file.close()
elif cmd == 'am':
        filename = 'Makefile.am'
        file = open(filename,'w')
        print "Writing  Makefile to  " + filename
        createAMFile(file, fileprefix, inputs, outputs)
        file.close()
elif cmd == 'def':
        filename = fileprefix + '.def'  
        file = open(filename,'w')
        print "Writing def file to  " + filename
        createDefFile(file, fileprefix,inputs,options)
        file.close()
elif cmd == 'dsp':
        filename = fileprefix + '.dsp'
        file = open(filename,'w')
        print "Writing dsp file to  " + filename
        createDspFile(file, fileprefix)
        file.close()
        
else:
     sys.stderr.write("Command not implemented yet!\n");


