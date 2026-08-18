#ifndef TAPE_DEFS
#define TAPE_DEFS

#define TAPE_SIZE 65536

#endif

char* createTape();

char* readTape(char* filename);

void writeTape(char* filename, char* tape);
