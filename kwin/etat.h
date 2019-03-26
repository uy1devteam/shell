#ifndef ETAT_H_INCLUDES
#define ETAT_H_INCLUDES
#include "symbol.h"
#include <stdlib.h>
#include <string.h>

class etat
{
private:
    symbol * ref;
    int val;
public:
    etat();
    etat(const char *);
    int set(const char *);
    int get();
    symbol * sym();
    ~etat();
    etat* getNeg();
    void neg();
    symbol* setsymbol(char );
    int setval(int);
    bool friend operator==(etat,etat);
    etat& operator= (const etat&);
};
 


#endif