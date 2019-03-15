#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>
#include <glob.h>
#include <iostream>
#include <string>
#include "header.h"
#include <fstream>
#include <readline/readline.h>
#include <readline/history.h>
#include "commande.h"

    using namespace std;
      /*
    List of builtin commands, followed by their corresponding functions.
    */

   
        int (*builtin_func[]) (char **) = {
            &cd,
            &help,
            &_exit,
            &history
        };
    
    commande::commande(){
        args = NULL;
        length = 0;
    };
    commande::commande(unsigned int argc,char** argv){
        delete args;
        args = new char*[argc];   
        for(length = 0;  length < argc; length ++){
            args[length] = argv [length];
        }
        
    };
    void commande::affiche(void){
        unsigned int i = 0;
        while(i < length){
            cout << args[i] << "  ";
            i++;
        }
        
    }
    int commande::copy(unsigned int argc, const char ** argv){
        char* tampon [length];
        unsigned int i = 0;
        for( i = 0; i < length; i++){
            tampon[i] = args[i];
        }
        length += argc;
        delete args;
        args =  new char* [length]; 
        for( i = 0; i < length - argc; i++){
            args[i] = tampon[i]  ;
        }
        for(i; i < length; i++){
            args[i] = (char *)argv[i];
        }
        return 0;
    };
    int commande::append(const char*  arg){
        char * tampon [length];
        unsigned int i = 0;
        for( i = 0; i < length; i++){
            tampon[i] = args[i];
        }
        length ++;
        delete args;
        args =  new char * [length]; 
        for( i = 0; i < length - 1; i++){
            args[i] = tampon[i]  ;
        }
        
        args[i] = (char *)arg;
        
        return 0;
    };
    int commande::erase(unsigned int  position){
        char * tampon [length - 1];
        unsigned int i = 0;
        if(position < 0 || position >=length){
            return -1;
        }
        while(  i < position ){
            tampon[i] = args[i];
            i++;
        }
        i++;
        while(  i < length ){
            tampon[i - 1] = args[i - 1];
        }
        length --;
        delete args;
        args =  new char * [length]; 
        for( i = 0; i < length; i++){
            args[i] = tampon[i]  ;
        }
        
        return 0;
    };
    void commande::clear(void){
        args = NULL;
        length = 0;
    };
    void commande::reverse(void){
        char * tampon [length - 1];
        unsigned int i = 0;
        while(  i < length ){
            tampon[ i ] = args[i];
        }
        delete args;
        args =  new char * [length];
        for( i = 0; i < length; i++){
            args[length - i -1] = tampon[i]  ;
        }
    }
    int commande::replace(unsigned int st, unsigned int end,const char * arg){
        if(st > end){
            return -1;
        }
        if(st < 0 || end >=length){
            return -1;
        }
        char * tampon [ length -(end -st + 1) ];
        unsigned int i = 0;
       
        while(  i < st ){
            tampon[i] = args[i];
            i++;
        }
        i = end + 1;
        while(  i < length ){
            tampon[i] = args[i];
            i++;
        }
        delete args;
        args =  new char * [length -st -end + 2];
        i = 0;
        while(  i < st ){
            args[i] = tampon[i];
            i++;
        }
        args[i] = (char *)arg;
        i++;
        while(  i < length ){
            args[i] = tampon[i];
            i++;
        }
        return 0;
    };
    commande operator+ (commande l1, commande l2){
        char * tampon [l1.length];
        unsigned int i = 0;
        for( i = 0; i < l1.length; i++){
            tampon[i] = l1.args[i];
        }
        l1.length += l2.length;
        delete l1.args;
        l1.args =  new char * [l1.length]; 
        for( i = 0; i < l1.length - l2.length; i++){
            l1.args[i] = tampon[i]  ;
        }
        for(i; i < l1.length; i++){
            l1.args[i] = l2.args[i];
        }
        return l1;
    }

    commande& commande::operator= (const commande & l1){
        if (this != &l1){
            delete args;
            args =  new char * [l1.length];
            length = l1.length;
            unsigned int i = 0;
            for( i = 0; i < l1.length; i++){
                args[i] = l1.args[i];
            }
        }

        
        return *this;
    }
    commande operator+= (commande l1, commande l2){
        return l1 = l1 + l2;
    }



    /**
     @brief Launch a program and wait for it to terminate.
    @param args Null terminated list of arguments (including program).
    @return Always returns 1, to continue execution.
    */
    int  commande::launch()
    {
    pid_t pid;
    int status;

    pid = fork();
    if (pid == 0) {
        // Child process
        if (execvp(args[0], args) == -1) {
        perror("msh");
        }
        exit(EXIT_FAILURE);
    } else if (pid < 0) {
        // Error forking
        perror("msh");
    } else {
        // Parent process
        do {
        waitpid(pid, &status, WUNTRACED);
        } while (!WIFEXITED(status) && !WIFSIGNALED(status));
    }

    return 1;
    }

    /**
     @brief Execute shell built-in or launch program.
    @param args Null terminated list of arguments.
    @return 1 if the shell should continue running, 0 if it should terminate
    */
    int commande::execute()
    {
    int i;

    if (args[0] == NULL) {
        // An empty command was entered.
        return 1;
    }

    for (i = 0; i < num_builtins(); i++) {
        if (strcmp(args[0], (const char *)builtin_str[i]) == 0) {
        return (*builtin_func[i])(args);
        }
    }

    return launch();
    }

    



    /**
     @brief Split a line into argss (very naively).
    @param line The line.
    
    */
    commande::commande(string lines)
    {
    char * line = (char *)lines.c_str();
    
    int bufsize = TOK_BUFSIZE, position = 0;
    args = (char **)malloc(bufsize * sizeof(char*));
    char *arg, **args_backup;

    if (!args) {
        cerr << "msh: allocation error" << endl;
        exit(EXIT_FAILURE);
    }

    arg = strtok(line, TOK_DELIM);
    while (arg != NULL) {
        args[position] = arg;
        position++;
        
        if (position >= bufsize) {
        bufsize += TOK_BUFSIZE;
        args_backup = args;
        args = (char **)realloc(args, bufsize * sizeof(char*));
        if (!args) {
            free(args_backup);
            cerr << "msh: allocation error" << endl;
            exit(EXIT_FAILURE);
        }
        }

        arg = strtok(NULL, TOK_DELIM);
    }
    
    args[position] = NULL;
    length = position + 1;
    
    }
    commande::commande(char *line)
    {
    int bufsize = TOK_BUFSIZE, position = 0;
    args = (char **)malloc(bufsize * sizeof(char*));
    char *arg, **args_backup;

    if (!args) {
        cerr << "msh: allocation error" << endl;
        exit(EXIT_FAILURE);
    }

    arg = strtok(line, TOK_DELIM);
    
    while (arg != NULL) {
        args[position] = arg;
        position++;

        if (position >= bufsize) {
        bufsize += TOK_BUFSIZE;
        args_backup = args;
        args = (char **)realloc(args, bufsize * sizeof(char*));
        if (!args) {
            free(args_backup);
            cerr << "msh: allocation error" << endl;
            exit(EXIT_FAILURE);
        }
        }

        arg = strtok(NULL, TOK_DELIM);
    }
    args[position] = NULL;
    length = position + 1;
    }
