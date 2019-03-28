#ifndef COMMANDE_H_INCLUDES
#define COMMANDE_H_INCLUDES
#define APPEND "a"
#define CREATE "w"
#define SHELL 0
#define FILLE 2

    class commande{
        char *** args;
        char ** listePipe;
        bool has_pipe = false; 
        int input;
        pid_t pid;
        int command_pipe[2];
        bool has_error = false;
        std::string erro_message;
  
        std::string out_put;
        std::string out_put_mod;
        std::string in_put;
        int in_put_mod;
        streambuf *coutbuf;
        streambuf *cinbuf;
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
            int traitement_etoille();
    };
    

#endif