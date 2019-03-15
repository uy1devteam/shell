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
#include "commande.h"
#include "commandes.h"

    using namespace std;

    
    
    commandes::commandes(){
        liste = NULL;
        length = 0;
    };
    commandes::commandes(unsigned int argc,commande* argv){
        liste = new commande[argc];   
        for(length = 0;  length < argc; length ++){
            liste[length] = argv [length];
        }
        
    };
    int commandes::copy(unsigned int argc, const commande * argv){
        commande tampon [length];
        unsigned int i = 0;
        for( i = 0; i < length; i++){
            tampon[i] = liste[i];
        }
        length += argc;
        delete liste;
        liste =  new commande [length]; 
        for( i = 0; i < length - argc; i++){
            liste[i] = tampon[i]  ;
        }
        for(i; i < length; i++){
            liste[i] = argv[i];
        }
        return 0;
    };
    int commandes::append(const commande  arg){
        commande tampon [length];
        unsigned int i = 0;
        for( i = 0; i < length; i++){
            tampon[i] = liste[i];
        }
        length ++;
        delete liste;
        liste =  new commande [length]; 
        for( i = 0; i < length - 1; i++){
            liste[i] = tampon[i]  ;
        }
        
        liste[i] = arg;
        
        return 0;
    };
    int commandes::erase(unsigned int  position){
        commande tampon [length - 1];
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
        delete liste;
        liste =  new commande [length]; 
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
        commande tampon [length - 1];
        unsigned int i = 0;
        while(  i < length ){
            tampon[ i ] = liste[i];
        }
        delete liste;
        liste =  new commande [length];
        for( i = 0; i < length; i++){
            liste[length - i -1] = tampon[i]  ;
        }
    }
    int commandes::execute_all(){
            
        unsigned int i(0);
        while(i<length){
            liste[i].execute();
            i++;
        }
        
        return 1;
    }
    int commandes::replace(unsigned int st, unsigned int end, commande arg){
        if(st > end){
            return -1;
        }
        if(st < 0 || end >=length){
            return -1;
        }
        commande tampon [ length -(end -st + 1) ];
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
        delete liste;
        liste =  new commande [length -st -end + 2];
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
        commande tampon [l1.length];
        unsigned int i = 0;
        for( i = 0; i < l1.length; i++){
            tampon[i] = l1.liste[i];
        }
        l1.length += l2.length;
        delete l1.liste;
        l1.liste =  new commande [l1.length]; 
        for( i = 0; i < l1.length - l2.length; i++){
            l1.liste[i] = tampon[i]  ;
        }
        for(i; i < l1.length; i++){
            l1.liste[i] = l2.liste[i];
        }
        return l1;
    }

    commandes& commandes::operator= (const commandes & l1){
        if (this != &l1){
            delete liste;
            liste =  new commande [l1.length];
            length = l1.length;
            unsigned int i = 0;
            for( i = 0; i < l1.length; i++){
                liste[i] = l1.liste[i];
            }
        }
        return *this;
    }
    commandes operator+= (commandes l1, commandes l2){
        return l1 = l1 + l2;
    }
    commandes::commandes(char * line){
                int bufsize = TOK_BUFSIZE, position = 0;
        char **tokens = (char **)malloc(bufsize * sizeof(char*));
        char *token, **tokens_backup;

        if (!tokens) {
            cerr << "msh: allocation error" << endl;
            exit(EXIT_FAILURE);
        }

        token = strtok(line, ";");
        while (token != NULL) {
            tokens[position] = token;
            position++;

            if (position >= bufsize) {
                bufsize += TOK_BUFSIZE;
                tokens_backup = tokens;
                tokens = (char **)realloc(tokens, bufsize * sizeof(char*));
                if (!tokens) {
                    free(tokens_backup);
                    cerr << "msh: allocation error" << endl;
                    exit(EXIT_FAILURE);
                }
            }

            token = strtok(NULL, TOK_DELIM);
        }
        int i(0);
        liste = new commande [position];
        while(i < position ){
            liste[i] = commande (tokens[i]);
            i++;
        }
        length = position ;
    }