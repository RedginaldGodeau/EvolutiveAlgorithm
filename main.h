#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#define clr() system ("CLS || CLEAR");
const int POPULATION = 100;

typedef struct pop {
    char str[100];
    int purcent;
} pop;

void purge (char*) ;
int strSize (char[]);
char randomLetter ();
char *checkWord (char[], char[]);
int getScore (char*);
pop crossOver (pop f, pop s);