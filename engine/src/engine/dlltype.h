#ifndef INCLUDED_DLLTYPE_H
#define INCLUDED_DLLTYPE_H

// This header defines the interface for new types
// Type plugins must implement these function

// a detailed description on implementing new datatypes for GePhex
// is located in the sgml documenation in the doc subdir


/**
 * Every instance of the type is identified by an unique ID. It is up to the
 * caller not to mix the IDs of different types.
 */
typedef void* TypeInstanceID;

/**
 * Every instance of an type attribute description is identified by an 
 * unique ID. Do not mix IDs of attribute descriptions of different types.
 */
typedef void* TypeAttributesInstanceID;



/** 
 * Initializes the type library. It must be called before any other method 
 * is called.
 */
int init(void);

/** 
 * Closes the type library. Call this method before unloading the shared 
 * library and after destruction of all type instances. After calling 
 * shutdown you mustn't call any method of this type.
 */
void shutDown(void);

/** 
 * Querys the specification of the type. At the moment the only property 
 * a unique string that identifies the type.
 */
const char* getSpec(void);

/** 
 * Querys infos for the user presentation. At the moment the only property 
 * is a short description of the type.
 */
int getInfo(char* buf, int bufLen);

/** 
 * Creates a new instance of the type and returns an unique identifier
 * for that.
 */
TypeInstanceID newInstance(void);

/** 
 * Deletes an instance of the type.
 */
void deleteInstance(TypeInstanceID instancePtr);

/**
 * Assigns the value of source to the destination.
 */
void assign(TypeInstanceID destination, 
	    TypeInstanceID source);

/** 
 * Serializes the value of the instance in the buffer
 */
int serialize(TypeInstanceID instance, 
	      char* buffer, 
	      int bufferLen);

/** 
 * Deserializes the buffer in the instance
 */
void deSerialize(const char* buffer, 
		 int len, 
		 TypeInstanceID instance);

/** 
 * compares the attributes with the ones of the instance
 */
int attributesEqual(TypeInstanceID instance, 
		    TypeAttributesInstanceID attributes);

/** 
 * assigns ths value from src to dst and changes the attributes while doing
 * that.
 */
void convertType(TypeInstanceID destination, 
		 TypeInstanceID source, 
		 TypeAttributesInstanceID attributes);

#endif
