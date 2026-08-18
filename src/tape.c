#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include <tape.h>


void fromString(char* tape) {
    for (int i = 0; tape[i] != 0; i++) {
        tape[i] = (tape[i] == '!' || tape[i] == '\n') ? 0 : tape[i];
    }
}

int toString(char* tape, char* buffer) {
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
    int offset = 0;
    if (lowestIndex != 0) {
        memcpy(buffer,tape+lowestIndex,TAPE_SIZE-lowestIndex);
        offset = TAPE_SIZE-lowestIndex;
    }
    memcpy(buffer+offset,tape,highestIndex+1);
    offset += highestIndex+1;
    *(buffer+offset) = '\n';
    offset++;
    return offset;
}

char* createTape() {
    char* tape = malloc(TAPE_SIZE);
    memset(tape,0,TAPE_SIZE);
    printf("Tape input (use '!' for blank character):");
    fgets(tape,TAPE_SIZE,stdin);
    fromString(tape);
    putchar('\n');
    return tape;
}

char* readTape(char* filename) {
    char* tape = malloc(TAPE_SIZE);
    FILE *f = fopen(filename,"rb");
    fread(tape,sizeof(char),TAPE_SIZE,f);
    fromString(tape);
    fclose(f);
    return tape;
}

void writeTape(char* filename, char* tape) {
    char* buffer = malloc(TAPE_SIZE);
    int size = toString(tape,buffer);
    FILE *f = fopen(filename,"wb");
    fwrite(buffer,size,1,f);
    fclose(f);
    free(buffer);
}

void printTape(char* tape) {
    char* buffer = malloc(TAPE_SIZE);
    toString(tape,buffer);
    printf(buffer);
    free(buffer);
}
