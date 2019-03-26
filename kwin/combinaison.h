#ifndef COMBINAISON_H_INCLUDES
#define COMBINAISON_H_INCLUDES
#include "etat.h"
#include "string.h"

    class combinaison
    {
    private:
        etat * listEtats ;
        size_t length;
        int value;
    public:
        combinaison(const char *);
        int addEtat(etat);
        size_t getLength();
        etat & operator [] (int) ;
        int addEtat(etat *);
        bool hasEtat(etat);
        bool hasEtat(etat *);
        bool hasEtatBare(etat );
        bool hasEtatMixte(etat *);
        bool hasEtatMixte(etat );
        etat getEtat(int);
        etat * getEtatAll();
        int  simple();
        ~combinaison();
        void sort();
        void asc_sort();
        int to_int();
        combinaison & operator= (const combinaison&);

    };
    

#endif