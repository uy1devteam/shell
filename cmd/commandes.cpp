#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>
#include <glob.h>
#include <iostream>
#include <string>
#include "header.h"
#include <fstream>

    using namespace std;

    class commandes{
        string * liste;
        unsigned int length;

        public:
            commandes();
            commandes(unsigned int ,string * );
            int copy( unsigned int,const string *);
            int append(const string );
            int erase(unsigned int);
            void clear(void);
            void reverse(void);
            int replace(unsigned int, unsigned int, string);
            friend commandes operator+ (commandes, commandes);
            friend commandes operator+= (commandes, commandes);
            commandes operator= (commandes);
    };
    
    commandes::commandes(){
        liste = NULL;
        length = 0;
    };
    commandes::commandes(unsigned int argc,string* argv){
        liste = new string[argc];   
        for(length = 0;  length < argc; length ++){
            liste[length] = argv [length];
        }
        
    };
    int commandes::copy(unsigned int argc, const string * argv){
        string tampon [length];
        unsigned int i = 0;
        for( i = 0; i < length; i++){
            tampon[i] = liste[i];
        }
        length += argc;
        liste =  new string [length]; 
        for( i = 0; i < length - argc; i++){
            liste[i] = tampon[i]  ;
        }
        for(i; i < length; i++){
            liste[i] = argv[i];
        }
        return 0;
    };
    int commandes::append(const string  arg){
        string tampon [length];
        unsigned int i = 0;
        for( i = 0; i < length; i++){
            tampon[i] = liste[i];
        }
        length ++;
        liste =  new string [length]; 
        for( i = 0; i < length - 1; i++){
            liste[i] = tampon[i]  ;
        }
        
        liste[i] = arg;
        
        return 0;
    };
    int commandes::erase(unsigned int  position){
        string tampon [length - 1];
        unsigned int i = 0;
        if(position < 0 || position >=length){
            return -1;
        }
        while(  i < position ){
            tampon[i] = liste[i];
            i++;
        }
        i++;
        while(  i < length ){
            tampon[i - 1] = liste[i - 1];
        }
        length --;
        liste =  new string [length]; 
        for( i = 0; i < length; i++){
            liste[i] = tampon[i]  ;
        }
        
        return 0;
    };
    void commandes::clear(void){
        liste = NULL;
        length = 0;
    };
    void commandes::reverse(void){
        string tampon [length - 1];
        unsigned int i = 0;
        while(  i < length ){
            tampon[ i ] = liste[i];
        }
        liste =  new string [length];
        for( i = 0; i < length; i++){
            liste[length - i -1] = tampon[i]  ;
        }
    }
    int commandes::replace(unsigned int st, unsigned int end, string arg){
        if(st > end){
            return -1;
        }
        if(st < 0 || end >=length){
            return -1;
        }
        string tampon [ length -(end -st + 1) ];
        unsigned int i = 0;
       
        while(  i < st ){
            tampon[i] = liste[i];
            i++;
        }
        i = end + 1;
        while(  i < length ){
            tampon[i] = liste[i];
            i++;
        }
        liste =  new string [length -st -end + 2];
        i = 0;
        while(  i < st ){
            liste[i] = tampon[i];
            i++;
        }
        liste[i] = arg;
        i++;
        while(  i < length ){
            liste[i] = tampon[i];
            i++;
        }
        return 0;
    };
    commandes operator+ (commandes l1, commandes l2){
        string tampon [l1.length];
        unsigned int i = 0;
        for( i = 0; i < l1.length; i++){
            tampon[i] = l1.liste[i];
        }
        l1.length += l2.length;
        l1.liste =  new string [l1.length]; 
        for( i = 0; i < l1.length - l2.length; i++){
            l1.liste[i] = tampon[i]  ;
        }
        for(i; i < l1.length; i++){
            l1.liste[i] = l2.liste[i];
        }
        return l1;
    }

    commandes commandes::operator= (commandes l1){
        liste =  new string [l1.length];
        length = l1.length;
        unsigned int i = 0;
        for( i = 0; i < l1.length; i++){
            liste[i] = l1.liste[i];
        }
        
        return *this;
    }
    commandes operator+= (commandes l1, commandes l2){
        return l1 = l1 + l2;
    }