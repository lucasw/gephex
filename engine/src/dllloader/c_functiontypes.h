#ifndef INCLUDED_FUNCTION_TYPES_H
#define INCLUDED_FUNCTION_TYPES_H

typedef int (*initT)(void (*)(int,const char*));
typedef void (*shutDownT)();

typedef void*  (*newInstanceT) ();

typedef const char* (*getSpecT) (void);
typedef const char* (*getInputSpecT) (int);
typedef const char* (*getOutputSpecT) (int);
typedef int (*getInfoT)(char* ,int);

typedef void (*deleteInstanceT) (void* instance);
typedef int (*setInputT) (void* instance,int index,void* typePointer);
typedef int (*setOutputT) (void* instance,int index,void* typePointer);
typedef void (*updateT) (void* instance);

typedef void (*parseInputT)(void* ,const char* ,int);
typedef void (*strongDependenciesCalculatedT)(void* ,int** );
typedef void (*getPatchLayoutT)(void* instance, int** out2in);

typedef void* (*getInputAttributesT)(int);

typedef void (*assignT)(void*,const void*);
typedef int (*serializeT)(void* type, char* buffer, int bufferLen);
typedef void (*deSerializeT)(const char* buffer,int len, void*);
typedef int (*attributesEqualT)(void*,void*);	
typedef void (*convertTypeT)(void*,void*,void*);
			  
#endif
