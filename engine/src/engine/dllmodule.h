#ifndef INCLUDED_DLLMODULE_H
#define INCLUDED_DLLMODULE_H

// This header defines the interface for new effect modules
// Module plugins must implement these function

// a detailed description on implementing new effect modules for GePhex
// is located in the sgml documenation in the doc subdir

/**
 * Every instance of the effect module is identified by an unique ID. 
 * It is up to the caller not to mix the IDs of different effect modules.
 */
typedef void* ModuleInstanceID;

/**
 * datatypes, attributes and their operations are defined in dlltype.h
 */
typedef void* TypeInstanceID;
typedef void* TypeAttributesInstanceID;

/**
 * callback functions to log messages out of the effect module
 */
typedef void (*logT) (int, const char*);
typedef void (*log2T) (int, const char*, const char*);

/** 
 * Initializes the effect module library. It must be called before any other 
 * method is called. Registers the logging callbackfunction in the module.
 */
int init(logT callback);

/** 
 * Closes the module library. Call this method before unloading the shared 
 * library and after destruction of all module instances. After calling 
 * shutdown you mustn't call any method of this module plugin.
 */
void shutDown();

/** 
 * Querys the specification of the type. At the moment the only property 
 * a unique string that identifies the type.
 * "mod_spec { name="mod_"<string>; number_of_inputs=<uint>; 
 *             number_of_outputs=<uint>;
 *             deterministic=<bool> }"
 */
const char* getSpec(void);

/** 
 * Querys infos for the user presentation. At the moment the only property 
 * is a short description of the type.
 */
int getInfo(char* buffer, int bufferLen);

/**
 * Query specification for one input.
 * "input_spec { type="typ_"<string>; const=<bool>; 
 *               strong_dependency=<bool>; }
 */
const char* getInputSpec (int index);

/**
 * Query specification for one output
 * "output_spec { type="typ_"<string>; }
 */
const char* getOutputSpec (int index);

/**
 * Querys if one input needs fixed attributes
 * returns 0 if the input has no fixed attribute
 */
TypeAttributesInstanceID getInputAttributes(int index);

/** 
 * Creates a new instance of the effect module and returns an unique identifier
 * for that.
 */
ModuleInstanceID newInstance(void);

/** 
 * Deletes an module instance
 */
void deleteInstance(ModuleInstanceID instance);

/**
 * Set the input to a new the type instance 
 */
int setInput(ModuleInstanceID instance,int index, TypeInstanceID typePointer);

/**
 * Set the output to a new the type instance 
 */
int setOutput (ModuleInstanceID instance,int index, TypeInstanceID typePointer);
/**
 * query the patch layout of inputs and outputs
 * sets for each output the corresponding input index 
 * or -1 if no patch is requested
 */
void getPatchLayout(ModuleInstanceID instance, int** out2in);

/**
 * calculate the effect and assign the results to the output type instances
 */
void update(ModuleInstanceID instance);

/**
 * returns a set of inputs that need to be calculated before calculation
 * of the effect
 */
void strongDependenciesCalculated(ModuleInstanceID instance,
				  int** neededInputs);

#endif
