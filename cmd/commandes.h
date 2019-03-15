#ifndef COMMANDES_H_INCLUDES
#define COMMANDES_H_INCLUDES
#include <string>
#include "commande.h"
#include <vector>
    using namespace std;

    class commandes{
        vector <commande> liste;
        
        public:
            commandes();
                        commandes(unsigned int ,commande * );
            void affiche(void);
            int copy( unsigned int,const commande *);
            int append(commande );
            int erase(unsigned int);
            void clear(void);
            void reverse(void);
            int execute_all(void);
            int replace(unsigned int, unsigned int, commande);
            friend commandes operator+ (commandes, commandes);
            friend commandes operator+= (commandes, commandes);
            commandes& operator= (const commandes&);
    };
    

#endif