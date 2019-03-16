#ifndef COMMANDE_H_INCLUDES
#define COMMANDE_H_INCLUDES
#include <string>

    using namespace std;

    class commande{
        char *** args;
        char ** listePipe;
        bool has_pipe = false; 
        int input;
        pid_t pid;
        int command_pipe[2];
        public:
            
            unsigned int length;
            commande();
            
            commande(string );
            commande(unsigned int ,char ** );
            commande(char * );
            void cleanup(int );
            int command(int  , bool , bool );
            int calcule_args( );
            void affiche(void);
            int copy( unsigned int,const char **);
            int append(const char* );
            int erase(unsigned int);
            void clear(void);
            void reverse(void);
            int replace(unsigned int, unsigned int, const char *);
            friend commande operator+ (commande, commande);
            friend commande operator+= (commande, commande);
            commande& operator= ( const commande &);
            int launch();
            int execute();
    };
          /*
    List of builtin commands, followed by their corresponding functions.
    */
        static char *builtin_str[] = {
            "cd",
            "help",
            "exit",
            "history"
            };

#endif