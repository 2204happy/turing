#include <string.h>
#include <stdio.h>

#include <options.h>

Options parseOptions(int argc, char* argv[]) {
    Options options = {0};
    options.timeout = -1;
    int i = 1;
    while(i<argc) {
        if(strcmp(argv[i],"-l") == 0) {
            options.loading = true;
            options.loadfile = argv[i+1];
            i += 2;
        }
        else if(strcmp(argv[i],"-s") == 0) {
            options.saving = true;
            options.savefile = argv[i+1];
            i += 2;
        }
        else if(strcmp(argv[i],"-r") == 0) {
            options.reading = true;
            options.readfile = argv[i+1];
            i += 2;
        }
        else if(strcmp(argv[i],"-w") == 0) {
            options.writing = true;
            options.writefile = argv[i+1];
            i += 2;
        }
        else if (strcmp(argv[i],"-t") == 0) {
            sscanf(argv[i+1],"%ld",&(options.timeout));
            i++;
        }
        else if (strcmp(argv[i],"-e") == 0) {
            options.exitcode = true;
            i++;
        }
        else if(strcmp(argv[i],"-h") == 0) {
            printf("Command line arguments:\n -l [file]: load machine from file\n -s [file]: save machine to file\n -r [file]: read tape input from file\n -w [file]: write tape out to file\n -t [number of steps] timeout simulation after number of steps\n -e return error status code if machine does not end in an accepting state\n");
            options.exitcode = false;
            options.norun = true;
            i = argc;
        }
        else {
            printf("Error: invalid argument %s\nRun ./turing -h for help\n",argv[i]);
            options.norun = true;
            options.exitcode = true;
            i = argc;
        }
    }
    return options;
}
