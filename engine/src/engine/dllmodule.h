#ifndef INCLUDED_DLL_MODULE_H
#define INCLUDED_DLL_MODULE_H
// DLL Schnittstelle

typedef void (*logT) (int,const char*);
// wird aufgerufen wenn die dll reingeladen wird
// optional
int init(logT);

// wird aufgerufen wenn die dll entladen wird
// optional
void shutDown();

// Liefert Informationen über das Modul zurück (bis jetzt nur den Namen
// für die GUI als string)
// erforderlich
int getInfo(char* buf,int bufLen);

// zum Empfangen von Informationen direkt von der GUI
// optional
void parseInput(void* instance,const char* buf,int bufLen);

// Format:
// "input_spec { type="typ_"<string>; const=<bool>; 
//               strong_dependency=<bool>; }
// (Reihenfolge egal)
const char* getInputSpec (int index);


// Format:
// "output_spec { type="typ_"<string>; }
const char* getOutputSpec (int index);

// Format:
// "mod_spec { name="mod_"<string>; number_of_inputs=<uint>; 
//             number_of_outputs=<uint>;
//             deterministic=<bool> }"
// (Reihenfolge egal)
const char* getSpec(void);

// optional
void strongDependenciesCalculated(void* instance,int** neededInputs);

// Eine neue Instanz des Moduls anlegen und einen Pointer auf dieselbe
// zurückgeben.
// erforderlich
void* newInstance(void);

// Eine Instanz löschen
// optional
void deleteInstance(void* instance);

// Der Input Nummer index einer Instanz bekommt einen Pointer
// auf die Daten mit denen das Modul rechnet
// optional
int setInput(void* instance,int index,void* typePointer);

// Pointer auf die Daten des Outputs Nummer index einer Instanz 
// zurückgeben.
// optional
int setOutput (void* instance,int index, void* typePointer);


// Liefert die Lister der zuordnungen von Ausgängen zu Eingängen
// für jeden Ausgang -1(keine zuordnung) oder nr des inputs
// muss von der engine direkt vor update aufgerufen werden
// optional
void getPatchLayout(void* instance, int** out2in);

// Die eigtl. Berechung. Wenn update() von der Engine aufgerufen
// wird hat die Engine vorher schon alle Inputs mit setInput() auf
// die richtigen Werte gesetzt.
// erforderlich
void update(void* instance);


// returns 0 if the input has no fixed attribute
// optional (wenn keine fixierten attribute vorkommen)
void* getInputAttributes(int index);

#endif
