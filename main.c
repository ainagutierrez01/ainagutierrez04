#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "xarxasocial.h"

#define MAX_LETTERS 100
#define MAX_WORDS 1000000

//Inicialitzar cua d'usuaris
List *head = NULL;
List *tail = NULL;


Diccionari diccionaribemusic;
//Funció inicialitzar timeline
void inicialitzar_timeline(Usuari* usuari){
    Timeline*timeline = (Timeline*)malloc(sizeof(Timeline));
    timeline->primer= NULL;
    usuari->timeline = timeline;

}
//Funció inicialitzar diccionari
void inicialitzar_diccionari(Diccionari* diccionari){
    diccionari->num_paraules =0;
    for(int i=0; i<MAX_WORDS; i++){
        diccionari->paraules[i]= NULL;
    }
}
//Funció buscar paraula en el diccionari
Paraula* buscar_paraula(Diccionari* diccionari, const char* paraula){
    //cerca seqüencial comparant caràcter per caràcter entre la paraula que es vol buscar i les paraules del diccionari
    // si coincideixen tots els caràcters de la paraula s'afegeix +1 al contador
    for(int i=0; i<diccionari->num_paraules; i++){
        if(strcmp(diccionari->paraules[i]->paraula, paraula)==0){
            diccionari->paraules[i]->conteo++;
            return diccionari->paraules[i];
        }
    }
    return NULL;
}
//Funció afegir paraula
void afegir_paraula(Diccionari* diccionari, const char* paraula){
    //creem espai, inicialitzem els nous camps de la paraula i afegim la paraula al contador del diccionari
    Paraula* new_paraula = (Paraula*)malloc(sizeof(Paraula));
    strcpy(new_paraula->paraula, paraula);
    new_paraula->conteo = 1;
    diccionari->paraules[diccionari->num_paraules]= new_paraula;
    diccionari->num_paraules++;
}
//Funció inicialitzar cua
void inicialitzar_cua (Cua*cua){
    cua -> primer = NULL;
    cua -> ultim = NULL;
}

int is_cua_empty (Cua*cua){
    return (cua-> primer == NULL);
}
//afegir un nou node a la cua
void enqueue(Cua*cua, Usuari usuari){
    //Crear un nou node
    List*new_node = (List*)malloc(sizeof(List));
    //Assignar l'usuari al nou node
    new_node->usu = usuari;
    //Establir el següent node com a NULL
    new_node->next = NULL;
    //verifica si la cua està buida
    if(is_cua_empty(cua)){
        //si ho està, el primer i últim node son el nou node
        cua->primer = new_node;
        cua->ultim = new_node;
    }
    else{
        //Si la cua no està buida, enllaçar el nou node al final de la cua
        cua->ultim->next = new_node;
        //Actualitzar l'últim node de la cua al nou node
        cua->ultim = new_node;
    }
}
//Funció per eleminiar i retornar el primer element d'una cua
Usuari dequeue (Cua*cua){
    //Verificar si la cua està buida
    if(is_cua_empty(cua)){
        //Si ho està, es retorna un usuari buit
        Usuari usuari_buid;
        strcpy(usuari_buid.nom_usuari, " ");
        return usuari_buid;
    }
    //Obtenir el primer node de la cua
    List*temp = cua->primer;
    //Obtenir l'usuari del primer node
    Usuari usuari = temp->usu;
    //Actualitzar el primer node de la cua al següent node
    cua->primer = temp->next;
    //Alliberar la memòria del node eliminat
    free(temp);
    //Verificar que la cua hagi quedat buida després d'eliminar el node
    if (cua->primer == NULL){
        //Si ha quedat buida s'actualitza l'últim node a NULL
        cua->ultim = NULL;
    }
    //Retornar l'usuari eliminat de la cua
    return usuari;
}
//Funció inicialitzar pila
void inicialitzar_pila(Pila *pila){
    pila -> top = NULL;
}
//Funció mirar si la pila està buida
int is_stack_empty(Pila *pila){
    return(pila -> top == NULL);
}
//Insertar un usuari a la part superior de la pila
void push(Pila *pila, Usuari usuari){
    //Crear un nou node de la llista
    List *new_list = (List*)malloc(sizeof(List));
    //Establir l'usuari en el nou node
    new_list->usu = usuari;
    //Establir el següent node del nou node al node de la part superior de la pila
    new_list->next = pila->top;
    //Actualitzar el node superior de la pila al nou node
    pila->top = new_list;

}

Usuari pop(Pila* pila){
    //Verificar si la pila está buida
    if(is_stack_empty(pila)){
        Usuari usuari_buid;
        strcpy(usuari_buid.nom_usuari, " ");
        return usuari_buid;
    }
    //Obtenir el node superior de la pila
    List *temp = pila->top;
    //Obtenir l'usuari del node superior
    Usuari pop_usuari = temp->usu;
    //Actualitzar el node superior de la pila al següent node
    pila->top = temp->next;
    //Alliberar la memòria del node extret
    free(temp);
    //retornar l'usuari extret
    return pop_usuari;
}
//Funció per afegir un usuari
void afegir_usuari(Usuari usuari){
    //afegir un nou node
    List *new_node = (List *)malloc(sizeof(List));
    //Assignar l'usuari al nou node
    new_node->usu = usuari;
    //Establir els punters previ i següent del nou node com a NULL
    new_node->prev = NULL;
    new_node->next = NULL;
    //Verificar si la llista està buida
    if (tail == NULL ){
        //Si la llista està buida, el nou node es converteix en el primer i últim node
        head = new_node;
        tail = new_node;

    }
    else{
        //Si la llista no està buida,
        //el nou node s'enllaça amb l'últim node existent
        new_node->prev = tail;
        tail->next = new_node;
        //Actualitzar el punter de la cua perquè apunti a l'últim node nou
        tail = new_node;
    }

}
//mostrar la llista d'usuaris registrats
void llista_usuaris(){
    //Verificar si la llista està buida
    if(head == NULL){
        printf("No hi ha cap usuari registrat!:(\n");
        return;
    }
    printf("Llista d'usuaris registrats:\n");
    //Inicialitzar un punter per recórrer la llista des del principi
    List *current = head;
    //Recorrer la llista i mostrar la informació de cada usuari
    while(current !=NULL){
        printf("Nom d'usuari: %s\n",current->usu.nom_usuari);
        printf("Edat: %d\n",current->usu.edat);
        printf("Correu electronic: %s\n",current->usu.correu);
        printf("Localitat: %s\n",current->usu.ubicacio);
        printf("Gustos musicals: \n");
        //mostrar els gusts musicals de l'usuari
        for (int i = 0; i<5;i++){
            printf("%s\n",current->usu.gusts[i]);
        }
        printf("\n");
        //avançar al següent node de la llista
        current = current->next;
    }

}
//funció buscar usuari a la linkedlist pel nom
List* buscar_usuari(const char *nom_usuari){
    //establim un punter current per recórrer la llista
    // començant des de l'inici head
    List *current = head;
    //bucle mentre current no sigui null (no ha arribat al final de la llista)
    while(current!=NULL){
        //Es compara el nom d'usuari actual amb el nom d'usuari buscat
        if(strcmp(current->usu.nom_usuari, nom_usuari)==0){
            //si els noms coincideixen, es retorna el node actual que conté l'usuari buscat
            return current;
        }
        //S'avança al següent node a la llista
        current = current->next;
    }
    //si no es troba l'usuari, es retorna NULL
    return NULL;
}

//funció per omplir la informació d'un nou usuari
// la informació s'afegeix a la linkedlist d'usuaris
Usuari omplir_nou_usuari() {
    Usuari usuari;
    char nom_usuari[MAX_LETTERS];
    printf("Insereix el nom d'usuari: \n");
    scanf("%s", nom_usuari);

    while (buscar_usuari(nom_usuari)!=NULL){
        printf("Aquest nom d'usuari no es troba disponible!\n");
        printf("Torna-ho a intentar :)\n");
        scanf("%s", nom_usuari);
    }
    strcpy(usuari.nom_usuari, nom_usuari);
    
    printf("Insereix la teva contrasenya: \n");
    scanf("%s", usuari.contrasenya);

    printf("Insereix la teva edat: \n");
    scanf("%d", &usuari.edat);

    printf("Insereix la teva direccio de correu electronic: \n ");
    scanf("%s", usuari.correu),

    printf("Insereix la teva localitat: \n");
    scanf("%s", usuari.ubicacio);

    printf("Insereix el teu cantant preferit: \n");
    scanf("%s", usuari.gusts[0]);

    if(buscar_paraula(&diccionaribemusic, usuari.gusts[0])==NULL){
        afegir_paraula(&diccionaribemusic, usuari.gusts[0]);
    }

    else{
        buscar_paraula(&diccionaribemusic, usuari.gusts[0]);
    }

    printf("Introdueix el teu grup preferit: \n");
    scanf("%s", usuari.gusts[1]);

    if(buscar_paraula(&diccionaribemusic, usuari.gusts[1])==NULL){
        afegir_paraula(&diccionaribemusic, usuari.gusts[1]);
    }

    else{
        buscar_paraula(&diccionaribemusic, usuari.gusts[1]);
    }

    printf("El teu lloc de festa preferit: \n");
    scanf("%s", usuari.gusts[2]);

    if(buscar_paraula(&diccionaribemusic, usuari.gusts[2])==NULL){
        afegir_paraula(&diccionaribemusic, usuari.gusts[2]);
    }

    else{
        buscar_paraula(&diccionaribemusic, usuari.gusts[2]);
    }

    printf("El teu concert somiat: \n");
    scanf("%s", usuari.gusts[3]);

    if(buscar_paraula(&diccionaribemusic, usuari.gusts[3])==NULL){
        afegir_paraula(&diccionaribemusic, usuari.gusts[3]);
    }

    else{
        buscar_paraula(&diccionaribemusic, usuari.gusts[3]);
    }

    printf("El teu genere de musica preferit: \n");
    scanf("%s", usuari.gusts[4]);

    if(buscar_paraula(&diccionaribemusic, usuari.gusts[4])==NULL){
        afegir_paraula(&diccionaribemusic, usuari.gusts[4]);
    }

    else{
        buscar_paraula(&diccionaribemusic, usuari.gusts[4]);
    }

    usuari.solis = (Cua*)malloc(sizeof(Cua));
    usuari.amics = (Cua*)malloc(sizeof(Cua));
    inicialitzar_cua(usuari.amics);
    inicialitzar_cua(usuari.solis);
    inicialitzar_timeline(&usuari);
    return usuari;
}
//genera suggerències d'amistat per un usuari seleccionat
void suggerencies_amistat(Usuari *selected_user){
    Pila suggerencies; //pila creada per emmagatzemar les suggerències
    inicialitzar_pila(&suggerencies);//inicialitzem la pila buida
    //punter per recorrer la llista d'usuaris des de l'inici
    List *current = head;
    int cont=0;//variable comptador numero de suggerències
    bool flag;//bandera per controlar la inserció de suggerències

    while(current!=NULL) { //iterem fins que no arribi al final de la llista

        Usuari current_user = current->usu;//Obtenim l'usuari del node actual
        //Verifiquem si l'usuari actual és diferent a l'usuari seleccionat
        if (strcmp(selected_user->nom_usuari, current_user.nom_usuari) != 0) {
            flag = true;
            //comparem els gusts entre els usuaris seleccionat i actual
            for (int j = 0; j < 5; j++) {
                for (int k = 0; k < 5; k++) {
                    if ((strcmp(selected_user->gusts[j], current_user.gusts[k]) == 0) && (flag == true)) {
                        //Si es troba un gust en comú i la bandera és true
                        flag=false; //Es canvia la bandera a false per evitat afegir l'usuari més d'una vegada
                        push(&suggerencies, current_user);//S'afegeix l'usuari actual a la pila de suggerències
                        cont++;//incrementem el contador
                    }
                }
            }
        }
        //avancem al següent node de la llista
        current = current->next;
    }

    printf("Les teves suggerències d'amistat: \n");
    for(int i=0; i<cont; i++){
        Usuari usuari_suggerit;
        //extraiem l'usuari de la pila
        usuari_suggerit = pop(&suggerencies);
        //Es mostra el nom de l'usuari suggerit
        printf("- %s \n", usuari_suggerit.nom_usuari);
    }
}
//funció penjar fitxers dins del codi
void penjar_fitxers(const char *filename) {
    FILE *file = fopen(filename, "r");


    if (file == NULL) {
        printf("No es pot obrir el fitxer! :(\n");
        return;
    }

    Usuari usuari;


    while (fscanf(file, "%[^,],%[^,],%d,%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^\n]\n", usuari.nom_usuari,usuari.contrasenya, &usuari.edat,
                  usuari.correu, usuari.ubicacio, usuari.gusts[0], usuari.gusts[1], usuari.gusts[2],
                  usuari.gusts[3], usuari.gusts[4]) == 10) {

        if(buscar_paraula(&diccionaribemusic, usuari.gusts[0])==NULL){
            afegir_paraula(&diccionaribemusic, usuari.gusts[0]);
        }
        else{
            buscar_paraula(&diccionaribemusic, usuari.gusts[0]);
        }

        if(buscar_paraula(&diccionaribemusic, usuari.gusts[1])==NULL){
            afegir_paraula(&diccionaribemusic, usuari.gusts[1]);
        }
        else{
            buscar_paraula(&diccionaribemusic, usuari.gusts[1]);
        }


        if(buscar_paraula(&diccionaribemusic, usuari.gusts[2])==NULL){
            afegir_paraula(&diccionaribemusic, usuari.gusts[2]);
        }
        else{
            buscar_paraula(&diccionaribemusic, usuari.gusts[2]);
        }

        if(buscar_paraula(&diccionaribemusic, usuari.gusts[3])==NULL){
            afegir_paraula(&diccionaribemusic, usuari.gusts[3]);
        }
        else{
            buscar_paraula(&diccionaribemusic, usuari.gusts[3]);
        }

        if(buscar_paraula(&diccionaribemusic, usuari.gusts[4])==NULL){
            afegir_paraula(&diccionaribemusic, usuari.gusts[4]);
        }
        else{
            buscar_paraula(&diccionaribemusic, usuari.gusts[4]);
        }

        usuari.solis = (Cua*)malloc(sizeof(Cua));
        usuari.amics = (Cua*)malloc(sizeof(Cua));
        inicialitzar_cua(usuari.amics);
        inicialitzar_cua(usuari.solis);
        inicialitzar_timeline(&usuari);
        afegir_usuari(usuari);

    }
    printf("S'ha carregat correctament el fitxer\n");
    fclose(file);

}

void mostrar_solicituds(Usuari usuari){
    if(is_cua_empty(usuari.solis)){
        printf("No tens solicituds d'amistat:(\n");
        return;
    }
    printf("Aquestes son les teves solicituds d'amistat\n");
    List*current = usuari.solis->primer;
    while(current !=NULL){
        printf("Nom d'usuari:%s\n",current->usu.nom_usuari);
        char choice[MAX_LETTERS];
        printf("Vols acceptar la solicitud?(si/no):\n");
        scanf("%s", choice);

        if(strcmp(choice,"si")==0){
            Usuari amic = dequeue(usuari.solis);
            enqueue(usuari.amics, current->usu);
            enqueue(current->usu.amics, usuari);
            printf("Has acceptat la solicitud d'amistat de %s\n", amic.nom_usuari);
        }

        if(strcmp(choice, "no")==0){
            Usuari amic = dequeue(usuari.solis);
            printf("Has rebutjat la solicitud d'amistat de %s\n", amic.nom_usuari);
        }
        current = current->next;
    }
}

void mostrar_amics(Usuari* usuari){

    if (is_cua_empty(usuari->amics)){
        printf("No tens cap amic :(\n");
        return;
    }

    List* current=usuari->amics->primer;
    
    while (current != NULL){
        printf("%s\n",current->usu.nom_usuari);
        current = current -> next;
    }
}

void penjar_publicacio(Usuari* usuari, const char* text){
    if(usuari->timeline == NULL){
        inicialitzar_timeline(usuari);
    }
    Publicacio* new_publicacio = (Publicacio*)malloc(sizeof(Publicacio));
    strcpy(new_publicacio->text,text);
    new_publicacio->next = NULL;

    if(usuari->timeline->primer ==NULL){
        usuari->timeline->primer = new_publicacio;
    }

    else{
        Publicacio* current = usuari->timeline->primer;
        while(current->next!=NULL){
            current = current->next;
        }
        current->next = new_publicacio;
    }
}

void imprimir_timeline(Usuari* usuari){
    Publicacio* current = usuari->timeline->primer;

    if(current == NULL){
        printf("No tens cap publicacio :(\n");
        return;
    }

    while(current!=NULL){
        printf("%s\n", current->text);
        current = current->next;
    }


}

void publicacions_amics(Usuari* usuari){
    List *current = usuari->amics->primer;
    while(current != NULL){
        printf("Publicacions de %s\n", current->usu.nom_usuari);
        imprimir_timeline(&current->usu);
        current = current->next;
        printf("\n");
    }
}

void entrar_compte() {
    if (head == NULL) {
        printf("No hi ha cap usuari registrat! :(\n ");
        return;
    }
    char nom_usuari[MAX_LETTERS];
    char contra[MAX_LETTERS];
    printf("Insereix el teu nom d'usuari:\n");
    scanf("%s", nom_usuari);

    printf("Insereixi la seva contrasenya: \n");
    scanf("%s", contra);


    if(buscar_usuari(nom_usuari)!=NULL) {
        List *temp1 = buscar_usuari(nom_usuari);
        if ((strcmp(temp1->usu.nom_usuari, nom_usuari) == 0)) {

            printf("Nom d'usuari correcte! :)\n");
            while(strcmp(temp1->usu.contrasenya, contra)!=0){
                printf("Contrasenya introduïda incorrecte :(\n");
                printf("Insereixi la seva contrasenya: \n");
                scanf("%s", contra);
            }
            Usuari usuari_seleccionat = temp1->usu;
            printf("Hola! %s\n", temp1->usu.nom_usuari);

            if(!is_cua_empty(usuari_seleccionat.solis)){
                printf("Tens una solicitud pendent!\n");
            }

            int choice;
            printf("Que vols fer? :)\n");
            printf("1. Enviar solicituds d'amistat\n");
            printf("2. Gestionar les solicituts pendents\n");
            printf("3. Realitzar una publicacio\n");
            printf("4. Llistar les teves publicacions\n");
            printf("5. Troba nous amics segons els teus gusts\n");
            printf("6. Llistar els teus amics\n");
            printf("7. Llistar les publicacions dels teus amics\n");
            printf("8. Buscar a un usuari\n");
            printf("9. Tornar al menu principal\n");
            scanf("%d", &choice);

            while (choice != 9) {
                if (choice == 1) {
                    char nom_usuari2[MAX_LETTERS];
                    printf("Afegeix el teu amic :)\n");
                    scanf("%s", nom_usuari2);

                    if (buscar_usuari(nom_usuari2) == NULL) {
                        printf("No s'ha trobat el nom d'usuari :(\n");

                    }
                    if (buscar_usuari(nom_usuari2) != NULL) {
                        List* temp = buscar_usuari(nom_usuari2);

                        enqueue(temp->usu.solis,usuari_seleccionat);
                        printf("S'ha enviat correctament la teva solicitud d'amistat!!!\n");
                    }

                }

                if(choice==2){
                    mostrar_solicituds(usuari_seleccionat);
                }

                if(choice ==3){
                    char text[MAX_LETTERS];
                    printf("Que vols compartir avui?\n");
                    scanf("%s",text);

                    if(buscar_paraula(&diccionaribemusic, text)==NULL){
                        afegir_paraula(&diccionaribemusic, text);
                    }

                    else{
                        buscar_paraula(&diccionaribemusic, text);
                    }

                    penjar_publicacio(&usuari_seleccionat, text);
                    printf("S'ha compartit correctament :)\n");
                }

                if(choice == 4){
                    imprimir_timeline(&usuari_seleccionat);
                }

                if(choice==5){
                    suggerencies_amistat(&usuari_seleccionat);
                }

                if(choice==6){
                    mostrar_amics(&usuari_seleccionat);
                }

                if(choice==7){
                    publicacions_amics(&usuari_seleccionat);
                }

                if(choice==8){
                    char bus_usuari[MAX_LETTERS];
                    printf("Nom d'usuari que vols buscar: \n");
                    scanf("%s", bus_usuari);

                    while (buscar_usuari(bus_usuari)==NULL){
                        printf("No existeix aquest usuari :(\n");
                        printf("Nom d'usuari que vols buscar: \n");
                        scanf("%s", bus_usuari);
                    }

                    List* temp1 = buscar_usuari(bus_usuari);
                    printf("%s: \n", temp1->usu.nom_usuari);
                    printf("Edat: %d\n", temp1->usu.edat);
                    printf("Gusts del usuari: \n");
                    for (int i =0; i<5; i++){
                        printf("-%s\n", temp1->usu.gusts[i]);
                    }
                    printf("Amics:\n");
                    mostrar_amics(&temp1->usu);
                }


                printf("Que vols fer? :)\n");
                printf("1. Enviar solicituds d'amistat\n");
                printf("2. Gestionar les solicituts pendents\n");
                printf("3. Realitzar una publicacio\n");
                printf("4. Llistar les teves publicacions\n");
                printf("5. Troba nous amics segons els teus gusts\n");
                printf("6. LListar els teus amics\n");
                printf("7. Llistar les publicacions dels teus amics\n");
                printf("8. Buscar a un usuari\n");
                printf("9. Tornar al menu principal\n");
                scanf("%d", &choice);


            }
            if(choice==9){
                return;
            }

        }

    }
    printf("No s'ha trobat l'usuari :(\n");
}

void swap(Paraula** a, Paraula**b){
    Paraula* temp= *a;
    *a=*b;
    *b= temp;
}

int partition (Paraula** arr, int low, int high){
    Paraula* pivot = arr[high];
    int i = low-1;

    for(int j=low; j<high; j++){
        if(arr[j]->conteo > pivot->conteo){
            i++;
            swap(&arr[i], &arr[j]);
        }
    }

    swap(&arr[i+1], &arr[high]);
    return i+1;
}

void quicksort(Paraula** arr, int low, int high){
    if(low<high){
        int pivot = partition (arr, low, high);
        quicksort(arr, low, pivot-1);
        quicksort(arr, pivot+1, high);
    }
}

void trendingtopic(Diccionari* diccionari){
    if(diccionari->num_paraules==0){
        printf("No hi ha trending topic de moment :(\n");
        return;
    }
    quicksort(diccionari->paraules, 0, diccionari->num_paraules-1);

    printf("Els trendingtopics son: \n");
    for(int i=0; i<diccionari->num_paraules && i<10; i++){
        printf("%s, utilitzada %d\n", diccionari->paraules[i]->paraula, diccionari->paraules[i]->conteo);
    }
}

    int main() {
        inicialitzar_diccionari(&diccionaribemusic);
        int option;
        printf("Benvingut a WEMUSIC \n");
        printf("===== Menu =====\n");
        printf("1. Insertar un nou usuari\n");
        printf("2. Llista de tots els usuaris existents\n");
        printf("3. Entrar al teu compte\n");
        printf("4. Penjar un fitxer d'usuaris\n");
        printf("5. Trending topic\n");
        printf("9. Sortir (Acabar execucio)\n");
        printf("Insereix una opcio: ");
        scanf("%d", &option);

        while (option != 9) {
            if (option == 1) {
                Usuari usu;
                usu = omplir_nou_usuari();
                afegir_usuari(usu);
            } else if (option == 2) {
                llista_usuaris();
            } else if (option == 3) {
                entrar_compte();
            } else if (option == 4) {
                char fitxer[MAX_LETTERS];
                printf("Introdueix el nom del fitxer: \n");
                scanf("%s", fitxer);
                penjar_fitxers(fitxer);
            }
            else if( option == 5){
                trendingtopic(&diccionaribemusic);

            }
            printf("\n\n===== Menu =====\n");
            printf("1. Insertar un nou usuari\n");
            printf("2. Llista de tots els usuaris existents\n");
            printf("3. Entrar al teu compte\n");
            printf("4. Penjar un fitxer d'usuaris\n");
            printf("5. Trending topic\n");
            printf("9. Sortir (Acabar execucio)\n");
            printf("Insereix una opcio: ");
            scanf("%d", &option);

        }
    }
