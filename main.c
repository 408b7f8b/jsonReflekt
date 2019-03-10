#include <stdlib.h>
#include "JsonParser.h"

struct c_test_sub {
    int i;
    list_list* daszweitei;
    schll_list* dasdrittei;
};

struct Beschreibung sub_c_beschreibung1, sub_c_beschreibung2, sub_c_beschreibung3;

void mach_init_c_test_sub(){
    struct c_test_sub dummi;

    sub_c_beschreibung1 = BeschreibungErzeugen("i", INTEGER, SIMPLE, &dummi.i, &dummi, NULL, NULL, 0);
    sub_c_beschreibung2 = BeschreibungErzeugen("daszweitei", INTEGER, ARRAY, &dummi.daszweitei, &dummi, NULL, NULL, 0);
    sub_c_beschreibung3 = BeschreibungErzeugen("dasdrittei", INTEGER, MAP, &dummi.dasdrittei, &dummi, NULL, NULL, 0);
}

const struct Beschreibung* sub_inhalte[] = {&sub_c_beschreibung1, &sub_c_beschreibung2, &sub_c_beschreibung3};
const size_t sub_inhalte_l = 3;

struct c_test_objekte {
    schll_list* liste;
};

struct Beschreibung c_test_objekte_beschreibung;

void mach_init_c_test_objekte(){
    struct c_test_objekte dummi;

    c_test_objekte_beschreibung = BeschreibungErzeugen("liste", OBJECT, MAP, &dummi.liste, &dummi, sub_inhalte,
                                                       &sub_inhalte_l, sizeof(struct c_test_sub));
}

const struct Beschreibung* c_test_objekte_inhalte[] = {&c_test_objekte_beschreibung};
const size_t c_test_objekte_inhalte_l = 1;






int main() {

    mach_init_c_test_sub();
    mach_init_c_test_objekte();

    struct c_test_sub teststruktur;
    teststruktur.daszweitei = list_makeListPointer();
    teststruktur.dasdrittei = schll_MakeListPointer();

    struct c_test_objekte teststruktur2;
    teststruktur2.liste = schll_MakeListPointer();

    json_object* objekt = json_object_from_file("../objekt.json");

    machi(sub_inhalte, sub_inhalte_l, &teststruktur, json_object_object_get(objekt, "objekt3"));
    machi(c_test_objekte_inhalte, c_test_objekte_inhalte_l, &teststruktur2, json_object_object_get(objekt, "objekt4"));

    int huhu = ((struct c_test_sub*)schll_getValuePointer(teststruktur2.liste, "objekt6"))->i;

    int* a = list_getValuePointer(teststruktur.daszweitei, 0);
    int* b = list_getValuePointer(teststruktur.daszweitei, 1);

//    machi(&mk, json_object_object_get(objekt, "objekt"));
   // machi(&t, json_object_object_get(objekt, "objekt2"));


    return 0;
}