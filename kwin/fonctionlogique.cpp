#include "fonctionlogique.h"

#include <vector>
    using namespace std;
    fonctionlogique::fonctionlogique()
   {
       listCombinaison = NULL;
       length = 0;
   }
   void fonctionlogique::sort(){
       for(size_t i =0; i < length; i++){
           listCombinaison[i].sort();
       }
   }
   int fonctionlogique::developpe(){
       size_t max = 0, i, position =0;
       vector <combinaison> V, W ;
       if(length <2 ){
           return 1;
       }
       for(i =0; i< length;i++){
           if(listCombinaison[i].getLength() > max){
               max = listCombinaison[i].getLength();
               position = i; 
           }
       }
       W.push_back(listCombinaison[position]);
       for(i = 0; i < length;i++){
           if(i != position ){
               size_t k = listCombinaison[position].getLength() - listCombinaison[i].getLength();
               if(k ==0){
                   W.push_back(listCombinaison[i]);
                   continue;
               };
               k = (size_t)pow(2,k);
               combinaison* combinaisonToAdd = (combinaison *)calloc(k,sizeof(combinaison));
               
               for(size_t j = 0; j < k ; j++){
                   combinaisonToAdd[j] = listCombinaison[i];
               }
               
                for(size_t j = 0; j < max ; j++){
                    
                   if( ! combinaisonToAdd[0].hasEtatMixte(listCombinaison[position][j]) ){
                       for(size_t c = 0,mil = (k/2); c < mil; c++)
                       {
                           
                         combinaisonToAdd[c].addEtat(listCombinaison[position][j]);
                         combinaisonToAdd[mil + c].addEtat(*(listCombinaison[position][j].getNeg())); 
                         
                       }
                       
                   };
               }
                 
               for(size_t j =0; j < k; j++){
                   V.push_back(combinaisonToAdd[j]);
               }
                            
           }

       }
                
           vector <combinaison>::iterator il;
           listCombinaison = (combinaison *)realloc(listCombinaison,(W.size() + V.size() )*sizeof(combinaison));
           length = 0;
           for(il = V.begin();il < V.end(); il++){
                listCombinaison[length++] =  *il;
           }
            for(il = W.begin();il < W.end(); il++){
               listCombinaison[length++] =  *il;
           }
   }

   
    fonctionlogique::fonctionlogique(combinaison t){
        combinaison * _listCombinaison;
        _listCombinaison = listCombinaison;
        listCombinaison = (combinaison *) realloc(listCombinaison,(length + 1)*sizeof(combinaison));
        if(listCombinaison == NULL){
            cfree(_listCombinaison);
        }
        else
        {
            listCombinaison[length++] = t;
        }
    }

    int fonctionlogique::add(combinaison t){
        length = (length)?length : 0;
        combinaison * _listCombinaison;
        _listCombinaison = listCombinaison;
         
        listCombinaison = (combinaison *) realloc(listCombinaison,(length + 1)*sizeof(combinaison));
        if(listCombinaison == NULL){
            listCombinaison =  _listCombinaison;
            
            return -1;
        }
        else
        {
            
            listCombinaison[length++] = t;
        }
        
        return 1;
    }    
    int fonctionlogique::add(const combinaison * t , int taille){
        combinaison * _listCombinaison;
        _listCombinaison = listCombinaison;
        listCombinaison = (combinaison *) realloc(listCombinaison,(length + taille)*sizeof(combinaison));
        if(listCombinaison == NULL){
            listCombinaison = listCombinaison;
            return -1;
        }
        else
        {
            size_t i = length + taille;
            while( length < i){
               listCombinaison[length] = t[ i-length - taille];
               length ++;
            }
            
        }
        return 1;
    }
    fonctionlogique::fonctionlogique(const combinaison * t , int taille){
        combinaison * _listCombinaison;
        _listCombinaison = listCombinaison;
        listCombinaison = (combinaison *) realloc(listCombinaison,length + taille);
        if(listCombinaison == NULL){
            cfree(_listCombinaison);
        }
        else
        {
            size_t i = length + taille;
            while( length < i){
               listCombinaison[length] = t[ i-length - taille];
               length ++;
            }
            
        }
    }

   fonctionlogique::~fonctionlogique()
   {
       cfree(listCombinaison);
   }