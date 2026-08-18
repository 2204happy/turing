#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <machine.h>

Machine* createMachine() {
    char buffer[256];
    printf("Number of states:");
    fgets(buffer,sizeof(buffer),stdin);
    int numStates;
    sscanf(buffer,"%d",&numStates);
    int machineSize = sizeof(Machine)+numStates*sizeof(State);
    Machine* machine = malloc(machineSize);
    memset(machine,0,machineSize);
    (*machine).numStates = numStates;
    printf("States are 0-%d, initial state is State 0\n",(*machine).numStates - 1);
    printf("\nList accepting states:");
    fgets(buffer,sizeof(buffer),stdin);
    int acc;
    int offset = 0;
    int size;
    while (sscanf(buffer+offset,"%d%n",&acc,&size) == 1) {
        (*machine).states[acc].accepting = true;
        offset += size;
    }
    printf("\nEnter transitions in the following format:\n[initial state] [character to read] [character to write] [tape direction (L/R)] [new state]\nUse '!' for blank character\nLeave input blank to finish\n\n");
    bool done = false;
    while (!done) {
        printf("Input transition:");
        fgets(buffer,sizeof(buffer),stdin);
        if (buffer[0] == '\n') {
            done = true;
        }
        else {
            int init;
            char read;
            char write;
            char dir;
            int next;
            sscanf(buffer,"%d %c %c %c %d",&init,&read,&write,&dir,&next);
            Direction direction = (dir == 'R' || dir == 'r') ? RIGHT : LEFT;
            read = (read == '!') ? 0 : read;
            write = (write == '!') ? 0 : write;
            Transition* transition = &((*machine).states[init].transitions[read]);
            (*transition).defined = true;
            (*transition).write = write;
            (*transition).next = next;
            (*transition).direction = direction;
        }
    }
    putchar('\n');
    return machine;
}

Machine* loadMachine(char* filename) {
    Machine tmp;
    FILE *f = fopen(filename,"rb");
    fread(&tmp,sizeof(Machine),1,f);
    Machine* machine = malloc(sizeof(Machine)+tmp.numStates*sizeof(State));
    (*machine).numStates = tmp.numStates;
    (*machine).init = tmp.init;
    fread(&((*machine).states),sizeof(State),(*machine).numStates,f);
    fclose(f);
    return machine;
}

void saveMachine(char* filename, Machine* machine) {
    FILE *f = fopen(filename,"wb");
    fwrite(machine,sizeof(Machine)+(*machine).numStates*sizeof(State),1,f);
    fclose(f);
}
