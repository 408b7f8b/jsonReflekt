#ifndef JSONPARSER_H
#define JSONPARSER_H

#include <string.h>
#include <json-c/json.h>

#include "Beschreibung.h"

#include "schll.h"
#include "einfl.h"

void machi(const struct Beschreibung* v[], const size_t l, void* basis, json_object* o){
    json_object_object_foreach(o, key, val){
        unsigned int c;
        for(c = 0; c < l; ++c){
            const struct Beschreibung* akt_c_beschreibung = v[c];

            if(strncmp(akt_c_beschreibung->Name, key, strlen(key)) == 0){
                switch(akt_c_beschreibung->dTyp){
                    case STRING:{
                        if(akt_c_beschreibung->sTyp == SIMPLE) {
                            if (json_object_get_type(val) == json_type_string) {
                                const char *w = json_object_get_string(val);

                                void** ziel = basis;
                                unsigned int c_s;
                                for(c_s = 0; c_s < akt_c_beschreibung->Ziel; ++c_s){
                                    ++ziel;
                                }

                                *ziel = calloc(1, 1+strlen(w));

                                strcpy(*ziel, w);
                            }
                        }
                        break;
                    }
                    case INTEGER:{
                        if(akt_c_beschreibung->sTyp == SIMPLE) {
                            if (json_object_get_type(val) == json_type_int) {
                                int i = json_object_get_int(val);
                                int* ziel = (basis + akt_c_beschreibung->Ziel);
                                *ziel = i;
                            }
                        }else if(akt_c_beschreibung->sTyp == ARRAY){
                            list_list** ziel = (basis + akt_c_beschreibung->Ziel);

                            unsigned int arr_it;
                            size_t arr_l = json_object_array_length(val);
                            for(arr_it = 0; arr_it < arr_l; ++arr_it){
                                json_object* arr_element = json_object_array_get_idx(val, arr_it);
                                if (json_object_get_type(arr_element) == json_type_int) {
                                    int i = json_object_get_int(arr_element);
                                    list_add(*ziel, &i, 1, sizeof(int));
                                }
                            }
                        }else if(akt_c_beschreibung->sTyp == MAP){
                            schll_list** ziel = (basis + akt_c_beschreibung->Ziel);

                            json_object_object_foreach(val, key_sub, val_sub){
                                if (json_object_get_type(val_sub) == json_type_int) {
                                    int i = json_object_get_int(val_sub);
                                    schll_addEntry(*ziel, key_sub, 1, &i, 1, sizeof(int));
                                }
                            }
                        }
                        break;
                    }
                    case OBJECT:{
                        if(akt_c_beschreibung->sTyp == SIMPLE){
                            void** ziel = (basis + akt_c_beschreibung->Ziel);
                            void* nv = calloc(1, akt_c_beschreibung->ObjektGroesse);
                            machi(akt_c_beschreibung->ObjektInhalte, *akt_c_beschreibung->ObjektInhalte_l, nv, val);
                            *ziel = nv;
                        }else if(akt_c_beschreibung->sTyp == ARRAY){
                            list_list** ziel = (basis + akt_c_beschreibung->Ziel);

                            unsigned int arr_it;
                            size_t arr_l = json_object_array_length(val);
                            for(arr_it = 0; arr_it < arr_l; ++arr_it){
                                json_object* arr_element = json_object_array_get_idx(val, arr_it);
                                if (json_object_get_type(arr_element) == json_type_object) {
                                    void* nv = calloc(1, akt_c_beschreibung->ObjektGroesse);
                                    list_add(*ziel, nv, 0, 0);
                                }
                            }
                        }else if(akt_c_beschreibung->sTyp == MAP){
                            schll_list** ziel = (basis + akt_c_beschreibung->Ziel);

                            json_object_object_foreach(val, key_sub, val_sub){
                                if (json_object_get_type(val_sub) == json_type_object) {
                                    void* nv = calloc(1, akt_c_beschreibung->ObjektGroesse);
                                    machi(akt_c_beschreibung->ObjektInhalte, *akt_c_beschreibung->ObjektInhalte_l, nv, val_sub);
                                    schll_addEntry(*ziel, key_sub, 1, nv, 0, 0);
                                }
                            }
                        }
                        break;
                    }
                    case NON:
                    default:
                        break;
                }
            }
        }




    }
}

#endif