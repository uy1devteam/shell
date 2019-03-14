
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <cstdarg>
#include <string>
#include <readline/readline.h>
#include <readline/history.h>
#include "header.h"



    using namespace std;
    
    






        /**
     @brief Main entry point.
    @param argc Argument count.
    @param argv Argument vector.
    @return status code
    */
    int main(int argc, char **argv)
    {
        // Load config files, if any.
        init_history();
        
        // Run command loop.
        loop();

        // Perform any shutdown/cleanup.

        return EXIT_SUCCESS;
    }