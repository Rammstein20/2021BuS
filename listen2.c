#include <stddef.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct stud_type {
    int matnum;
    char vorname[20];
    char nachname[20];
    struct stud_type *next;
} stud_type;


/* Ist die Datenbank leer?      */
bool is_empty(stud_type const* liste) {
    return !liste;
}


/* Einfuegen eines Elementes
 * 
 * Bekommt einen Zeiger auf einen Zeiger der auf das 1. Element der Liste zeigt
 * Bekommt MatNr, Vorname und Nachname des Studenten der eingefügt werden soll
 *
 * Gibt true für Erfolg zurück
 * Gibt false für einen Fehler zurück
 */
bool enqueue(stud_type** studenten_liste, int matnum, char const vorname[20], char const nachname[20]) {
    /* Hole dynamischen Speicher für den neuen Listen Eintrag */
    struct stud_type* neuerEintrag = (struct stud_type*) malloc(100 * sizeof(char));
    
    /* Befülle den Speicher (vorsicht vor buffer overflows!) */
    neuerEintrag->matnum    = matnum;
    strcpy(neuerEintrag->vorname,   vorname);
    strcpy(neuerEintrag->nachname,  nachname);
    
    /* Füge den neuen Eintrag in die Wilde Liste ein */
        /* Ist die Liste leer ? */
        if(is_empty(*studenten_liste)){
            *studenten_liste = neuerEintrag;
            neuerEintrag->next = NULL;
            return 0;
        /* Sortier den Studenten aufsteigend nach Matrikelnummer ein (matrikelnummern sind einzigartig) */
        }else{
            stud_type *curr = (*studenten_liste);

            while (curr != NULL && curr->next->matnum < neuerEintrag->matnum) {
                curr = curr->next;
           }
           if(curr->next->matnum == matnum){
            printf("Matrikelnummer %4i ist bereits in der liste", matnum);
            return 0;
           }else{
               *(neuerEintrag->next) = *(curr->next->next);
               *(curr->next) = *(neuerEintrag);
           return 0;
           }
    }

}


/* Löschen eines Elementes. 
 * 
 * Bekommt einen Zeiger auf einen Zeiger der auf das 1. Element der Liste zeigt
 * Bekommt die MatNr des Studenten der zu löschen ist
 *
 * Gibt true für Erfolg zurück
 * Gibt false für einen Fehler zurück
 */
bool dequeue(stud_type** studenten_liste, int matnum) {
    /* Prüfe Randbedingungen */
    if(is_empty(*studenten_liste)){
        return 1;
    }
    /* Finde den Studenten */
     stud_type *curr = *(studenten_liste);
    while (curr->next->matnum != matnum || curr->next != NULL){
        curr    = curr->next;
    }
    if(curr->next->matnum == matnum){

    /* Lösche den Studenten und gibt den Speicher frei */
    free(curr->next); 
    curr->next = curr->next->next;
    
     

    }else if(curr->matnum == matnum){
        /* Was muss passieren wenn das 1. Element gelöscht wird? */
        curr->next = *(studenten_liste);
        /* Lösche den Studenten und gibt den Speicher frei */
        free(curr);
    
    }else{
        /* Was ist wenn es nicht in der Liste ist? */
        printf("%i ist bereits nicht mehr in der studenten_liste enthalten ", matnum);
    }

    /* Lösche den Studenten und gibt den Speicher frei */
    
    
    
    
    /* ... */
    
}

/* Auslesen eines Elementes 
 *
 * Bekommt pointer auf den Listenstart
 * Bekommt MatNr des Studenten der ausgelesen werden soll
 *
 * Schreibt Vorname und Nachname in vorname und nachname
 */
bool get_student(stud_type const* studenten_liste, int matnum, char vorname[20], char nachname[20]) {
    /* Durchsuchen der DB */
    stud_type const* curr = studenten_liste;
    while (curr && curr->matnum < matnum) {
        curr = curr->next;
    }

    if (!curr || curr->matnum != matnum) {
        /* Rückgabewert: Fehler */
        return false;
    } else {
        strncpy(vorname, curr->vorname, 19);
        vorname[19] = '\0';
        strncpy(nachname, curr->nachname, 19);
        nachname[19] = '\0';
        /* Rückgabewert: OK */
        return true;
    }
}

static void test_empty(stud_type const* liste) {
    printf(">>> Test ob die Studentenliste leer ist ...\n");

    if(is_empty(liste)) {
        printf("    Die Studentenliste ist leer \n");
    } else {
        printf("    Die Studentenliste ist nicht leer \n");
    }
}

static void test_get(stud_type const* liste, int matnum) {
    printf(">>> Test, ob die Matrikelnummer %4i bereits erfasst wurde ...\n", matnum);

    char vorname[20];
    char nachname[20];
    if(get_student(liste, matnum, vorname, nachname)) {
        printf("    Matrikelnummer %4i: %s %s\n", matnum, vorname, nachname);
    } else {
        printf("    Matrikelnummer %4i ist unbekannt\n", matnum);
    }
}

static void test_enqueue(stud_type** liste, int matnum, char const* vorname, char const* nachname) {
    printf(">>> Fuege neuen Studenten in die Liste ein: %s %s [%4i] ...\n", vorname, nachname, matnum);
    if(enqueue(liste, matnum, vorname, nachname)) {
        printf("    Matrikelnummer %4i eingefügt\n", matnum);
    } else {
        printf("    Matrikelnummer %4i konnte nicht eingefügt werden\n", matnum);
    }
}

static void test_dequeue(stud_type** liste, int matnum) {
    printf(">>> Loesche die Matrikelnummer %4i ...\n", matnum);

    if(dequeue(liste, matnum)) {
        printf("    Matrikelnummer %4i geloescht\n", matnum);
    } else {
        printf("    Matrikelnummer %4i war nicht erfasst\n", matnum);
    }
}

static void test_dump(stud_type const* liste) {
    printf(">>> Gebe alle erfassten Studenten aus ...\n");
    for(stud_type const* curr = liste; curr; curr = curr->next) {
        printf("    Matrikelnummer %4i: %s %s\n", curr->matnum, curr->vorname, curr->nachname);
    }
}

/* Test der Listenfunktionen  */
int main(void) {
    /* Initialisierung der Datenbank */
    stud_type* studenten_liste = NULL;

    test_empty(studenten_liste);
    test_enqueue(&studenten_liste, 1234, "Eddard", "Stark");
    test_get(studenten_liste, 1234);
    test_enqueue(&studenten_liste, 5678, "Jon", "Snow");
    test_get(studenten_liste, 1234);
    test_enqueue(&studenten_liste, 9999, "Tyrion", "Lannister");
    test_get(studenten_liste, 1235);
    test_enqueue(&studenten_liste, 1289, "Daenerys", "Targaryen");
    test_dequeue(&studenten_liste, 1234);
    test_empty(studenten_liste);
    test_get(studenten_liste, 5678);
    test_dequeue(&studenten_liste, 9998);
    test_enqueue(&studenten_liste, 1289, "Viserys", "Targaryen");
    test_dequeue(&studenten_liste, 5678);
    test_enqueue(&studenten_liste, 1, "Tywin", "Lannister");
    test_dump(studenten_liste);


    test_enqueue(&studenten_liste, 666, "Satan", "Mama");
    test_get(studenten_liste, 666);
    
    /*
    enqueue(&studenten_liste, 1234, "Eddard", "Stark");
    get_student(studenten_liste, 1234);
    enqueue(&studenten_liste, 5678, "Jon", "Snow");
    get_student(studenten_liste, 1234);
    enqueue(&studenten_liste, 9999, "Tyrion", "Lannister");
    get_student(studenten_liste, 1235);
    enqueue(&studenten_liste, 0666, "Satan", "Mama");
    get_student(studenten_liste, 0666);
    */

    
    
    {
        /* Erzeuge sortierte Liste nach Vorname */
        /* Gebe Liste aus */
        /* Räume erzeugte Liste auf */
    }

    {
        /* Erzeuge sortierte Liste nach Nachname */
        /* Gebe Liste aus */
        /* Räume erzeugte Liste auf */
    }

    /* Räume studenten_liste auf */

    return 0;
}
