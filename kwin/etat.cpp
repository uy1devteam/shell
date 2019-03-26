#include "etat.h"
#include <vector>
#define EQUAL 0

symbol* listSymbol = (symbol *)calloc(26,sizeof(symbol)),*_listSymbol;
size_t length = 0;
symbol * test( char c){
  
    for(size_t i = 0; i < length; i++)
    {
        if(listSymbol[i].cmp(c) == EQUAL){
            return listSymbol + i;
        }
    }
    return NULL;
}
bool operator==(etat a , etat b){
    if(a.val != b.val){
        return false;
    }
    return a.ref == b.ref;       
}
etat& etat::operator=( const  etat& t){
    if(this != &t){
        ref = t.ref;
        val = t.val;
    }
    return *this;
}
symbol * add(char c){
    if(length >= 26){
       _listSymbol = listSymbol;
       listSymbol = (symbol *) realloc(listSymbol,length + 1);
       if(listSymbol == NULL){
           cfree(_listSymbol);
           return NULL;
       }
       
    }
    listSymbol[length].set(c);
    return listSymbol + length++; 
}
etat* etat::getNeg(){
    etat * p = (etat *)malloc(sizeof(etat));
    *p = *this;
    (*p).neg();
    return p;
}
void etat::neg(){
    val = (val + 1)%2;
}
etat::etat()
{
     ref = NULL;
     val = -1;
}
etat::etat(const char * et){
    int taille = strlen(et);
    switch (taille)
    {
        case 1:
            ref = test(et[0]);
            if ( ref == NULL){
                ref = add(et[0]);
            }
            
            val = 1;
            break;
        case 2:
            ref = test(et[0]);
            if ( ref == NULL){
                ref = add(et[0]);
            }
            val = 0;
            break;      
        default:
            break;
    }
}

etat::~etat()
{
    //if(ref)
    //delete ref;
}
int etat::set(const char * et){
        int taille = strlen(et);
    switch (taille)
    {
        case 1:
            ref = test(et[0]);
            if ( ref == NULL){
                ref = add(et[0]);
            }
            val = 1;
            return 1;
        case 2:
            ref = test(et[0]);
            if ( ref == NULL){
                ref = add(et[0]);
            }
            val = 0;
            return 0;      
        default:
            return -1;
    }
}
symbol * etat::setsymbol(char c){
    ref = test(c);
    if ( ref == NULL){
        ref = add(c);
    }
    return ref;
}
int etat::setval(int v){
    if(v < 0 || v > 1){
        return -1;
    }
    val = v;
    return 1;
}
int etat::get(){
    return val;
}
symbol * etat::sym(){
    return ref;
}