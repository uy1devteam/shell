

#include <unistd.h>
#include <stdlib.h>
#include <iostream>
#include <cstdarg>

#include "header.hpp"



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
    
        
        // Run command loop.
        loop();

        // Perform any shutdown/cleanup.

        return EXIT_SUCCESS;
    }