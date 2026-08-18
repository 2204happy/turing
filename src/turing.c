#include <stdio.h>
#include <stdlib.h>

#include <machine.h>
#include <tape.h>
#include <options.h>

bool turing(Machine* machine,char* tape, long int timeout) {
    int tapeMask = TAPE_SIZE-1;
    unsigned int pointer = 0;
    State state = (*machine).states[(*machine).init];
    while (timeout != 0) {
        char in = *(tape+pointer);
        if (!state.transitions[in].defined) {
            return state.accepting;
        }
        Transition transition = state.transitions[in];
        *(tape+pointer) = transition.write;
        (transition.direction == RIGHT) ? pointer++ : pointer--;
        pointer &= tapeMask;
        state = (*machine).states[transition.next];
        timeout--;
    }
    printf("Machine failed to halt before timeout\n");
}


int main(int argc, char* argv[]) {
    Options options = parseOptions(argc,argv);
    if (options.norun) {
        return (int)options.exitcode;
    }
    Machine* machine;
    if (options.loading) {
        machine = loadMachine(options.loadfile);
    }
    else {
        machine = createMachine();
    }

    if (options.saving) {
        saveMachine(options.savefile,machine);
    }

    char* tape;
    if (options.reading) {
        tape = readTape(options.readfile);
    }
    else {
        tape = createTape();
    }

    bool result = turing(machine,tape,options.timeout);
    if (!options.exitcode) {
        printf("Machine halted on a%s state\n",result ? "n accepting" : " rejecting");
    }

    if (options.writing) {
        writeTape(options.writefile,tape);
    }
    else {
        printf("Final tape state:\n%s\n",tape);
    }

    free(tape);
    free(machine);

    if(!result && options.exitcode) {
        return 1;
    }
    return 0;
}
