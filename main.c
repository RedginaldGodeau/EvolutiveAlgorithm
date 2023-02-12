#include "main.h"

int main(int argc, char const *argv[]) {
    srand(time(NULL));
    
    char phrase[100];
    int phraseSize;

    pop populations[POPULATION];
    int counter = 0;

    fgets(phrase, 100, stdin);
    purge (phrase);
    phraseSize = strSize(phrase)-1;

    for(int i = 0; i < POPULATION; i++) {
        int i2;
        for (i2 = 0; i2 < phraseSize+2; i2++) populations[i].str[i2] = randomLetter ();
        populations[i].str[i2] = '\0';
    }
    
    while (strstr(phrase,populations[0].str) == NULL) {
        clr();
        printf("Population Gen %d\n", counter++);

        for(int i = 0; i < POPULATION; i++) {
            for (int i2 = 0; i2 < phraseSize+2; i2++) {
                if(populations[i].str[i2] == '_')
                    populations[i].str[i2] = randomLetter ();
            }
        }

        int mo = 0;
        for (int i = 0; i < POPULATION; i++) {
            checkWord(phrase,populations[i].str);
            populations[i].purcent = getScore (populations[i].str);
            mo += populations[i].purcent;
        }
        float moyenne = (float)mo / (float)POPULATION;
        
        int place = 0;
        pop bestPopulation[100];
        for (int i = 0; i < POPULATION; i++) if(populations[i].purcent > (int) moyenne) bestPopulation[place++] = populations[i];

        int i2;
        pop tmp;
        for (int i = 1 ; i <= place-1; i++) {
            i2 = i;
            while (i2 > 0 && bestPopulation[i2-1].purcent < bestPopulation[i2].purcent) {
                tmp = bestPopulation[i2];
                bestPopulation[i2] = bestPopulation[i2-1];
                bestPopulation[i2-1] = tmp;
                i2--;
            }
        }

        populations[0] = bestPopulation[0];
        for (int i = 1; i < POPULATION; i++) 
            populations[i] = crossOver (bestPopulation[0], bestPopulation[1]);
    }
    clr();
    printf("Population Gen %d\n", counter++);
    printf("La phrase : \n%s", populations[0].str);    
    return 0;
}


void purge (char *str) {
    int i;
    for (i = 0; str[i] != '\n'; i++); str[i] = '\0';
}

int strSize (char str[]) {
    int i;
    for (i = 0; str[i] != '\0'; i++);
    return i-1;
}

char randomLetter () {
    const char letters[] = " abcdefghijklmnopqrstuwxyzvABCDEFGHIJQLMNOPQRSTUWXYZV-!?.,;1234567890:+-/";
    int r = rand() % strlen(letters);
    return letters[r];
}

char *checkWord (char phrase[], char check[]) {
    char *newWord = check;
    int i;
    for (i = 0; phrase[i] != '\0'; i++) {
        if(phrase[i] != check[i]) {newWord[i] = '_';}
    }
    newWord[i] = '\0';
    return newWord;
}
int getScore (char *str) {
    int i,err = 0;
    for (i = 0; str[i] != '\0'; i++) {
        if(str[i] == '_') err++;
    }

    float purcent = (((float)i - (float)err)/i)*100;
    return (int)purcent;
}

pop crossOver (pop first, pop second) {
    int i;
    pop cross;

    for (i = 0; first.str[i] != '\0'; i++) {
        if(first.str[i] == '_' && second.str[i] != '_') cross.str[i] = second.str[i];
        else if(second.str[i] == '_' && first.str[i] != '_') cross.str[i] = first.str[i];
        else cross.str[i] = '_';
    }
    cross.str[i] = '\0';
    return cross;
}