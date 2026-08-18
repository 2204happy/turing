#include <stdbool.h>

#ifndef OPTIONS_DEFS
#define OPTIONS_DEFS

typedef struct Options Options;

struct Options {
    char* loadfile;
    char *savefile;
    char* readfile;
    char* writefile;
    long int timeout;
    bool loading;
    bool saving;
    bool reading;
    bool writing;
    bool exitcode;
    bool norun;
};

#endif

Options parseOptions(int argc, char* argv[]);
