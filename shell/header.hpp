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
    int cd(char **args);
    int help(char **args);
    int _exit(char **args);
    int history(char **args);
    int ls(char **args);
    int grep(char **args);


    long unsigned_convertion(char * chaine);
    int num_builtins(void); 
    long convertion(char * chaine);
    std::string directory(void);
    void loop(void);
    std::string cat_many(int nbCh, ...);
    char **split_line(char *line);
    char * copier(char * word);   
    bool is_separator(char c);
    int num_builtinprocs();
      
          /*
    List of builtin commands, followed by their corresponding functions.

    */

       
       
     
         
#endif