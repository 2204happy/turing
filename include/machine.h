#include <stdbool.h>

#ifndef MACHINE_DEFS
#define MACHINE_DEFS

typedef enum Direction Direction;
typedef struct Transition Transition;
typedef struct State State;
typedef struct Machine Machine;

enum Direction {
    LEFT,
    RIGHT
};

struct Transition {
    bool defined;
    char write;
    int next;
    Direction direction;
};

struct State {
    Transition transitions[256];
    bool accepting;
};

struct Machine {
    int numStates;
    int init;
    State states[];
};

#endif

Machine* createMachine();

Machine* loadMachine(char* filename);

void saveMachine(char* filename, Machine* machine);
