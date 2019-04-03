#ifndef FONCTIONLOGIQUE_H_INCLUDES
#define FONCTIONLOGIQUE_H_INCLUDES
#include "combinaison.h"
#include "string.h"
#include "math.h"
   class fonctionlogique
   {
   private:
      combinaison * listCombinaison;
      size_t length;
   public:
       int developpe(); 
       fonctionlogique();
       void sort();
       fonctionlogique(combinaison);
       fonctionlogique(const combinaison *  , int );
       int add(const combinaison *  , int);
       int add(const combinaison );
       ~fonctionlogique();
   };
   

#endif