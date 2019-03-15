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
#include "commande.h"
#include "commandes.h"

    using namespace std;
    

  
   
    
        /*
    Builtin function implementations.
    */
    /**
     @brief Bultin command: echo history of comande line.
    @param args List of args.  args[0] is "cd".  
    */
    int history(char **args)
    {

        
        if (args[1] == NULL) {
            
            HIST_ENTRY** first  = history_list();
            int i = (HISTORY_MAX_LENGTH < history_length)?  history_length - HISTORY_MAX_LENGTH: 0 ;
            
            do{
                cout << i << "   " <<first[i]->line << endl;
                i++;
            }while( i < history_length );     
                        
        }
        else
        {
            if(args[2] ==   NULL){

            }else{
                cerr << "msh: to many arguments to \"history\"" << endl;
                return 1;
            }
            long p = unsigned_convertion(args[1]);
            if(p < 0){
                cerr << "msh: need numerique argument to \"history\"" << endl;
            }else{
                HIST_ENTRY** first  = history_list();
                int i = (p < history_length)?  history_length - p: 0 ;
                
                do{
                    cout << i << "   " <<first[i]->line << endl;
                    i++;
                }while( i < history_length );

            }

        }
        return 1;    
    }
    /**
     @brief Bultin command: change directory.
    @param args List of args.  args[0] is "cd".  args[1] is the directory.
    @return Always returns 1, to continue executing.
    */
    int cd(char **args)
    {
    if (args[1] == NULL) {
        fprintf(stderr, "msh: expected argument to \"cd\"\n");
    } else {
        if (chdir(args[1]) != 0) {
        perror("msh");
        }
        
    }
    return 1;
    }

    /**
     @brief Builtin command: print help.
    @param args List of args.  Not examined.
    @return Always returns 1, to continue executing.
    */
    int help(char **args)
    {
        int i;
    
        printf("Type program names and arguments, and hit enter.\n");
        printf("The following are built in:\n");

        for (i = 0; i < num_builtins(); i++) {
            printf("  %s\n", builtin_str[i]);
        }

        printf("Use the man command for information on other programs.\n");
        return 1;
    }

    /**
     @brief Builtin command: exit.
    @param args List of args.  Not examined.
    @return Always returns 0, to terminate execution.
    */
    int _exit(char **args)
    {
    return 0;
    }
    long convertion(char * chaine)
    {
        unsigned i = 0;
        long nombre = 0;
        short signe = POSITIF;
        if(chaine[0] == TIRET)
        {
            signe = NEGATIF;
            i++;
        }
        while(chaine[i] != '\0'){
            if( chaine[i] > 47 && chaine[i] <  59){
                
                nombre =  nombre * 10*i +  chaine[i] - 48;
                
            }else{
                cerr <<" msh : " << chaine << " is not a number" << endl;
                exit(EXIT_FAILURE);
            }
            i++;
        }
        return nombre * signe;
    }


    long unsigned_convertion(char * chaine)
    {
        unsigned i = 0;
        long nombre = 0;
        
        while(chaine[i] != '\0'){
            if( chaine[i] > 47 && chaine[i] <  59){
                
                nombre =  nombre * 10*i +  chaine[i] - 48;
                
            }else{
                return -1;
            }
            i++;
        }
        return nombre ;
    }

    /*
        give the current directory name and username wthi some design
    */

    string directory(){
        string  path =  get_current_dir_name();
        string username = getenv("USER");
        string base = cat_many(2,"/home/",username.c_str());        
        
        if(path.compare(base) == 0  ){
            path.replace(0,base.length(),"~/");
        }else{
            if(path.compare(base) > 0){
                path.replace(0,base.length() + 1,"~/");
            }
        }
        return cat_many(8,"\e[032;1m",username.c_str(),"\e[33;0m",":","\033[34;1m",path.c_str(),"\033[47;0m","$ ");
        
    }
    int num_builtins() {
    return sizeof(builtin_str) / sizeof(char *);
    }

    
    /*
    @brief cat_many cat str argument in to one string 
    @params nbCh number of char * passed 
    @return a string resulting of concatanation off all char * parsed
    */
    string cat_many(int nbCh, ...){
        va_list liste ;
        va_start (liste , nbCh) ;
        int i;
        string reslut;
        for (i=1 ; i<=nbCh ; i++)
        { 
            string tampon = va_arg (liste, char *) ;
            reslut += tampon;
            
        }
        va_end(liste);
        
        return reslut;
    }
    /*
    @brief split_commande split line to get commande separe by ;
    @params line the char * to split 
    @return all commande on line
    */
    char **split_commande(char* line){
        int bufsize = TOK_BUFSIZE, position = 0;
        char **tokens = (char **)malloc(bufsize * sizeof(char*));
        char *token, **tokens_backup;

        if (!tokens) {
            cerr << "msh: allocation error" << endl;
            exit(EXIT_FAILURE);
        }

        token = strtok(line, ";");
        while (token != NULL) {
            tokens[position] = token;
            position++;

            if (position >= bufsize) {
                bufsize += TOK_BUFSIZE;
                tokens_backup = tokens;
                tokens = (char **)realloc(tokens, bufsize * sizeof(char*));
                if (!tokens) {
                    free(tokens_backup);
                    cerr << "msh: allocation error" << endl;
                    exit(EXIT_FAILURE);
                }
            }

            token = strtok(NULL, TOK_DELIM);
        }
        tokens[position] = NULL;
        return tokens;
    }
    /**
     @brief init history
    */
    void  init_history(void){
        using_history();
        if( read_history(HISTORY_NAME)){
            write_history(HISTORY_NAME);
        };
        stifle_history(HISTORY_MAX_LENGTH);
    }
        /**
     @brief Read a line of input from stdin.
    @return The line from stdin.
    */
    char *read_line(void)
    {
        
        char *line = NULL;
        
        line =  readline(directory().c_str());
        if (*line) add_history(line);
            append_history(1,HISTORY_NAME);
        return line;
    }
    /**
     @brief Loop getting input and executing it.
    */
    void loop(void)
    {
    char *line;
  
    int status;


 
    do {
        line = read_line();
        commandes cmds(line);
        status = cmds.execute_all();

        free(line);
    
    } while (status);

    }

