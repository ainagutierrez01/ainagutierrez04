//
// Created by ainagutierrez on 02/06/2023.
//

#ifndef XARXASOCIAL_XARXASOCIAL_H
#define XARXASOCIAL_XARXASOCIAL_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_LETTERS 100
#define MAX_WORDS 1000000
//estructura que representa una paraula amb contador (numero de vegades que surt una paraula al diccionari)
typedef struct Paraula {
    char paraula[MAX_LETTERS];
    int conteo;
} Paraula;
//Estructura d'un diccionari de paraules
typedef struct Diccionari {
    Paraula* paraules[MAX_WORDS];
    int num_paraules;
} Diccionari;
//Estructura linkedlist de publicacions
typedef struct Publicacio {
    char text[MAX_LETTERS];
    struct Publicacio* next;
} Publicacio;
//Estructura timeline (ordre cronològic de les publicacions)
typedef struct Timeline {
    Publicacio* primer;
} Timeline;
//Estructura usuari
typedef struct {
    char nom_usuari[MAX_LETTERS];
    char contrasenya[MAX_LETTERS];
    int edat;
    char correu[MAX_LETTERS];
    char ubicacio[MAX_LETTERS];
    char gusts[5][MAX_LETTERS];
    struct cua* solis;
    struct cua* amics;
    struct Timeline* timeline;
} Usuari;
//Estructura linkedlist
typedef struct list {
    Usuari usu;
    struct list* next;
    struct list* prev;
} List;
//Estructura Pila
typedef struct Pila {
    List* top;
} Pila;
//Estructura Cua d'usuaris
typedef struct cua {
    List* primer;
    List* ultim;
} Cua;

extern List* head;
extern List* tail;
extern Diccionari diccionaribemusic;

void inicialitzar_timeline(Usuari* usuari);
void inicialitzar_diccionari(Diccionari* diccionari);
Paraula* buscar_paraula(Diccionari* diccionari, const char* paraula);
void afegir_paraula(Diccionari* diccionari, const char* paraula);
void inicialitzar_cua(Cua* cua);
int is_cua_empty(Cua* cua);
void enqueue(Cua* cua, Usuari usuari);
Usuari dequeue(Cua* cua);
void inicialitzar_pila(Pila* pila);
int is_stack_empty(Pila* pila);
void push(Pila* pila, Usuari usuari);
Usuari pop(Pila* pila);
void afegir_usuari(Usuari usuari);
void llista_usuaris();
List* buscar_usuari(const char* nom_usuari);
Usuari omplir_nou_usuari();
void suggerencies_amistat(Usuari* selected_user);
void penjar_fitxers(const char* filename);
void mostrar_solicituds(Usuari usuari);
void mostrar_amics(Usuari* usuari);
void penjar_publicacio(Usuari* usuari, const char* text);
void imprimir_timeline(Usuari* usuari);
void publicacions_amics(Usuari* usuari);
void entrar_compte();
void swap(Paraula** a, Paraula**b);
int partition (Paraula** arr, int low, int high);
void quicksort(Paraula** arr, int low, int high);
void trendingtopic(Diccionari* diccionari);

#endif //XARXASOCIAL_XARXASOCIAL_H
