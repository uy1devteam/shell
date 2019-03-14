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

    using namespace std;
            char *builtin_str[] = {
            "cd",
            "help",
            "exit",
            "history"
            };
   
        int (*builtin_func[]) (char **) = {
            &cd,
            &help,
            &_exit,
            &history
        };
    class commande{
        char ** args;
        unsigned int length;

        public:
            commande();
            commande(unsigned int ,char ** );
            int copy( unsigned int,const char **);
            int append(const char* );
            int erase(unsigned int);
            void clear(void);
            void reverse(void);
            int replace(unsigned int, unsigned int, const char *);
            friend commande operator+ (commande, commande);
            friend commande operator+= (commande, commande);
            commande operator= (commande);
            int launch();
            int execute();
    };
    
    commande::commande(){
        args = NULL;
        length = 0;
    };
    commande::commande(unsigned int argc,char** argv){
        args = new char*[argc];   
        for(length = 0;  length < argc; length ++){
            args[length] = argv [length];
        }
        
    };
    int commande::copy(unsigned int argc, const char ** argv){
        char* tampon [length];
        unsigned int i = 0;
        for( i = 0; i < length; i++){
            tampon[i] = args[i];
        }
        length += argc;
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
        l1.args =  new char * [l1.length]; 
        for( i = 0; i < l1.length - l2.length; i++){
            l1.args[i] = tampon[i]  ;
        }
        for(i; i < l1.length; i++){
            l1.args[i] = l2.args[i];
        }
        return l1;
    }

    commande commande::operator= (commande l1){
        args =  new char * [l1.length];
        length = l1.length;
        unsigned int i = 0;
        for( i = 0; i < l1.length; i++){
            args[i] = l1.args[i];
        }
        
        return *this;
    }
    commande operator+= (commande l1, commande l2){
        return l1 = l1 + l2;
    }

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
        if (strcmp(args[0], builtin_str[i]) == 0) {
        return (*builtin_func[i])(args);
        }
    }

    return launch(args);
    }

    



    /**
     @brief Split a line into tokens (very naively).
    @param line The line.
    @return Null-terminated array of tokens.
    */
    char **split_line(char *line)
    {
    int bufsize = TOK_BUFSIZE, position = 0;
    char **tokens = (char **)malloc(bufsize * sizeof(char*));
    char *token, **tokens_backup;

    if (!tokens) {
        cerr << "msh: allocation error" << endl;
        exit(EXIT_FAILURE);
    }

    token = strtok(line, TOK_DELIM);
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
