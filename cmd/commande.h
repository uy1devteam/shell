#ifndef COMMANDE_H_INCLUDES
#define COMMANDE_H_INCLUDES
#include <string>

    using namespace std;

    class commande{
        char ** args;
        

        public:
            unsigned int length;
            commande();
            commande( char *);
            commande(string );
            commande(unsigned int ,char ** );
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