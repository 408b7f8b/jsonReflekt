#ifndef BESCHREIBUNG_H
#define BESCHREIBUNG_H

#include <string.h>

enum Datentyp {
    NON, STRING, INTEGER, OBJECT
};

enum Strukturtyp {
    SIMPLE, ARRAY, MAP
};

struct Beschreibung {
    char* Name;

    enum Datentyp dTyp;
    enum Strukturtyp sTyp;
    unsigned long Ziel;

    void* ObjektInhalte;
    const size_t* ObjektInhalte_l;
    size_t ObjektGroesse;
};

struct Beschreibung
BeschreibungErzeugen(char* bName, enum Datentyp bDatentyp, enum Strukturtyp bStrukturtyp, void* Zieladresse,
                     void* Bezugsadresse, void* bObjektInhalte, const size_t* bObjektInhalte_l,
                     const size_t bObjektGroesse) {
    struct Beschreibung ret;
    ret.Name = calloc(1, sizeof(char) * (strlen(bName) + 1));
    strcpy(ret.Name, bName);
    ret.Ziel = Zieladresse - Bezugsadresse;
    ret.sTyp = bStrukturtyp;
    ret.dTyp = bDatentyp;
    ret.ObjektInhalte = bObjektInhalte;
    ret.ObjektInhalte_l = bObjektInhalte_l;
    ret.ObjektGroesse = bObjektGroesse;
    return ret;
}

void BeschreibungAufloesen(struct Beschreibung* beschreibung){
    free(beschreibung->Name);
}

#endif