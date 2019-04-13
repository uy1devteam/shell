#ifndef HEADER_H_INCLUDES
#define HEADER_H_INCLUDES
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sys/types.h>
#include <sys/wait.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <cstdarg>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <glob.h>
#include <errno.h>


#define EQUAL 0
#define TIRET '-'
#define SPACE ' '
#define TAB '\t'
#define POSITIF 1
#define NEGATIF -1
#define HISTORY_NAME ".msh_history"
#define HISTORY_MAX_LENGTH 2000
#define TOK_BUFSIZE 64
#define TOK_DELIM " \t\r\n\a"
#define RL_BUFSIZE 1024

        /*
    Function Declarations for builtin shell commands:
    */
    int cd(char **);
    int help(char **);
    int _exit(char **);
    int history(char **);
    int ls(char **);
    int grep(char **);
    int rm(char **);

    long unsigned_convertion(char *); 
    long convertion(char *);
    std::string directory(void);
    void loop(void);
    std::string cat_many(int , ...);
    char **split_line(char *);
    char * copier(char * );   
    bool is_separator(char );
    int num_in(char ** );
      
          /*
    List of builtin commands, followed by their corresponding functions.

    */

       
       
     
         
#endif