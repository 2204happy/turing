#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include <tape.h>

void cleanTape(char* tape) {
    for (int i = 0; tape[i] != 0; i++) {
        tape[i] = (tape[i] == '!' || tape[i] == '\n') ? 0 : tape[i];
    }
}

char* createTape() {
    char* tape = malloc(TAPE_SIZE);
    memset(tape,0,TAPE_SIZE);
    printf("Tape input (use '!' for blank character):");
    fgets(tape,TAPE_SIZE,stdin);
    cleanTape(tape);
    putchar('\n');
    return tape;
}

char* readTape(char* filename) {
    char* tape = malloc(TAPE_SIZE);
    FILE *f = fopen(filename,"rb");
    fread(tape,sizeof(char),TAPE_SIZE,f);
    cleanTape(tape);
    fclose(f);
    return tape;
}

void writeTape(char* filename, char* tape) {
    FILE *f = fopen(filename,"wb");
    int highestIndex = 0;
    int lowestIndex = 0;
    for (int i = 0; i<TAPE_SIZE; i++) {
        if (tape[i] == 0) {
            tape[i] = '!';
        }
        else {
            if (i<TAPE_SIZE/2) {
                highestIndex = i;
            }
            else if (lowestIndex == 0){
                lowestIndex = i;
            }
        }
    }
    if (lowestIndex != 0) {
        fwrite(tape+lowestIndex,sizeof(char),TAPE_SIZE-lowestIndex,f);
    }
    fwrite(tape,sizeof(char),highestIndex+1,f);
    fclose(f);
}

