#include "combinaison.h"
combinaison::combinaison(const char * combi)
{
    size_t taille = strlen(combi),i=0,bufzise = 64;
    etat* _listEtats;
    listEtats = (etat *)calloc(bufzise,sizeof(etat));
    length = value = 0;
    while(i < taille){
        if(combi[i] == '!'){
            
            
            listEtats[length].setval(0);
            listEtats[length].setsymbol(combi[++i]); 
        }else
        { 
            listEtats[length].setval(1);
            listEtats[length].setsymbol(combi[i]);
        }
        
        length ++;
        if(length > bufzise){
            bufzise *= 2;
            _listEtats = listEtats;
            listEtats = (etat*) realloc(listEtats,bufzise*sizeof(etat));
            if(listEtats == NULL){
                cfree(_listEtats);
            }
        }
        i++;
    }
    
}
size_t combinaison::getLength(){
    return length;
}
etat combinaison::getEtat(int i ){
    if(i<0 || i >= length){
        return NULL;
    }
    return listEtats[i];
}
etat * combinaison::getEtatAll(){
    return listEtats;
}
etat& combinaison::operator[] (int i){
    return listEtats[i];
}
combinaison & combinaison::operator= (const combinaison& cmb){
    if(this != &cmb){
        if(listEtats){
            cfree(listEtats);
        }
        length = cmb.length;
        listEtats = (etat *)calloc(length,sizeof(etat));
        for(size_t i = 0; i < length; i++){
            listEtats[i] = cmb.listEtats[i];
        }
    }
    return *this;
}
int combinaison::addEtat(etat t){
    if(hasEtat(t)){
        return 1;
    }
    etat * _listEtats = listEtats;
    listEtats = (etat *) realloc(listEtats, ++length * sizeof(etat));
    if(listEtats == NULL){
        listEtats = _listEtats;
        return -1;
    } 
    listEtats[length -1] = t;
    return 1;

}

bool combinaison::hasEtat(etat t){
    for(size_t i = 0; i < length; i++){
        if(listEtats[i] == t){
            return true;
        }
    }
    return false;
}


bool combinaison::hasEtatBare(etat t){
    for(size_t i = 0; i < length; i++){
        if(listEtats[i].sym() == t.sym()){
            if(listEtats[i].get() != t.get())
            return true;
        }
    }
    return false;
}
bool combinaison::hasEtat(etat * t){
    for(size_t i = 0; i < length; i++){
        if(listEtats[i] == *t){
            return true;
        }
    }
    return false;
}
bool combinaison::hasEtatMixte(etat *t){
    for(size_t i = 0; i < length; i++){
        if(*(listEtats[i].sym()) == *((*t).sym())){
            return true;
        }
    }
    return false;
}
bool combinaison::hasEtatMixte(etat t){
    for(size_t i = 0; i < length; i++){
        if(*(listEtats[i].sym()) == *(t.sym())){
            return true;
        }
    }
    return false;
}
combinaison::~combinaison()
{
    //if(listEtats)
    //cfree(listEtats);
}
void combinaison::sort(){
    etat * reslut = (etat *) calloc(length,sizeof(etat))  ;
    size_t j = 0 ,i = 0,position = 0 , k = 0;
    symbol *  ref ;
    char MAX;
    while(i < length){
        MAX =  (*listEtats [0].sym()).get();
        position = 0;
        for(size_t j = 1; j < length ; i++)
        {
            if( (*listEtats[j].sym()).cmp(MAX) > 0){
                position = j;
                MAX = (*listEtats[j].sym()).get();
            }
            
        }
        length --;
        reslut[k] = listEtats[position];
        k++;
        cfree(listEtats + position);
    }
    length = k;
    listEtats = (etat *) calloc(length,sizeof(etat));
    i = 0;
    while(i < k){
        listEtats[i] = reslut [i];
        i++;
    }
    
}
void combinaison::asc_sort(){
    etat * reslut = (etat *) calloc(length,sizeof(etat))  ;
    size_t j = 0 ,i = 0,position = 0 , k = 0;
    
    char min;
    while(i < length){
        min =  (*listEtats [0].sym()).get();
        position = 0;
        for(size_t j = 1; j < length ; i++)
        {
            if( (*listEtats[j].sym()).cmp(min) < 0){
                position = j;
                min = (*listEtats[j].sym()).get();
            }
            
        }
        length --;
        reslut[k] = listEtats[position];
        k++;
        cfree(listEtats + position);
    }
    length = k;
    listEtats = (etat *) calloc(length,sizeof(etat));
    i = 0;
    while(i < k){
        listEtats[i] = reslut [i];
        i++;
    }
    
}
int combinaison::to_int(){
    int i = length - 1;
    value = 0;
    
    while( i >= 0){
        if(hasEtatBare(listEtats[i])){
            value = 0;
            break;
        }
        value = value * 2 + listEtats[i].get() ;
        i--;
    }
    return value;
}