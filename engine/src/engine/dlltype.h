
int init(void);

// Format:
// "typ_spec { name="typ_"<string>; }
const char* getSpec(void); // "typ_blahbal"

void* newInstance(void);
void assign(void*,const void*); //kopieren
void deleteInstance(void*); //löschen

int serialize(void* type, char* buffer, int bufferLen);
void deSerialize(const char* buffer, int len,void*);

void shutDown(void);

// Liefert Informationen über den Typ zurueck.
int getInfo(char* buf,int bufLen);

// Setzt einen Parameter, dessen Name und Typ aus dem Infostring bekannt ist
//void setParam(void* type,const char* paramName, char* buf, int bufLen);

// 0-> not equal
// 1-> equal
int attributesEqual(void* type, void* attributes);

// dstType must already be allocated
void convertType(void* dstType, void* srcType, void* attributes);
