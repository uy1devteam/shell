#ifndef HEADER_H_INCLUDES
#define HEADER_H_INCLUDES
#include <string>
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
    using namespace std;

        /*
    Function Declarations for builtin shell commands:
    */
    int cd(char **args);
    int help(char **args);
    int _exit(char **args);
    int history(char **args);


    long unsigned_convertion(char * chaine);
    int num_builtins(void); 
    long convertion(char * chaine);
    string directory(void);
    void loop(void);
    string cat_many(int nbCh, ...);
    char **split_line(char *line);
    void  init_history(void);

#endif