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
#include "vector"
    using namespace std;

    
    
    commandes::commandes(){

    };
    commandes::commandes(unsigned int argc,commande* argv){

        unsigned int i = 0;
        while(i < argc){
             liste.push_back(argv[i]);
        }
            
    };
    
    void commandes::affiche(void){
        vector<commande>::iterator il ;

        for (il = liste.begin() ; il != liste.end() ; il++)
        {
            il->affiche();
        }
        
    }
    int commandes::append( commande  arg){
        liste.push_back(arg);
    };
    int commandes::erase(unsigned int  position){
        
        liste.erase(liste.begin()+position);
        return 0;
    };
    void commandes::clear(void){
        liste.clear();
    };
    void commandes::reverse(void){
        vector<commande>::iterator il ;
        vector<commande> _liste;
        for (il = liste.begin() ; il != liste.end() ; il++)
        {
            _liste.push_back(*il);
        }
        liste.clear();
        for (il = _liste.begin() ; il != _liste.end() ; il++)
        {
            liste.push_back(*il);
        }
    }
    int commandes::execute_all(){
            
        vector<commande>::iterator il ;

        for (il = liste.begin() ; il != liste.end() ; il++)
        {
            il->execute();
        }
        
        return 1;
    }
    int commandes::replace(unsigned int st, unsigned int end, commande arg){
        liste.insert(liste.begin(),st-end+1,arg);
        return 0;
    };
    commandes operator+ (commandes l1, commandes l2){
        
        vector<commande>::iterator il ;
        for (il = l2.liste.begin() ; il != l2.liste.end() ; il++)
        {
            l1.liste.push_back(*il);
        }
        return l1;
    }

    commandes& commandes::operator= (const commandes & l1){
        if (this != &l1){
            liste = l1.liste;
        }
        return *this;
    }
    commandes operator+= (commandes l1, commandes l2){
        return l1 = l1 + l2;
    }
    

    bool is_meta(char c){
        switch(c){
            case '$':
            break;
            case '\"':
            break;
            case '\\':
            break;
            case ';':
            break;
            case '>':
            break;
            case '<':
            break;
            case '\'':
            break;
            case '|':
            break;
            case '(':
            break;
        }
    }
    string analyse( char * line){
        size_t i(0);
        string cmd;
        bool neutralise_some = false;
        bool neutralise_all = false;
        bool super_neutralise = false;
        while( line[i] != '\n'){
            if(line[i] == '\"'){
                if(neutralise_all){
append_cote:        cmd.append((const char *)"\"");
                    
                    super_neutralise = false;
                    goto pass;
                }

                if(neutralise_some){
                  if(super_neutralise){
                      goto append_cote;
                  } 
                  neutralise_some = false;
                  goto pass;  
                }else
                {
                    if(super_neutralise){
                      goto append_cote;
                    }
                    neutralise_all = false;
                    super_neutralise = false;
                    neutralise_some = true;
                    goto pass;
                }
                
            }

            if(line [i] == '\''){
                if(neutralise_some){
append_simple_cote: cmd.append((const char *)"'");
                    
                    super_neutralise = false;
                    goto pass;
                }

                if(neutralise_all){
                    neutralise_all = false;
                    goto pass;
                }
                else
                {
                    if(super_neutralise){
                       goto append_simple_cote;     
                    }
                    neutralise_all = true;
                    neutralise_some = false;
                    super_neutralise = false;
                    goto pass;
                }
                
            }

            if(line[i]=='\\'){
                if(neutralise_all){
                    cmd.append((const char *)"\\");
                    goto pass;
                }
                if(neutralise_some){
                    if(super_neutralise){
                        cmd.append((const char *)"\\");
                        super_neutralise = false;
                        goto pass;
                    }
                    super_neutralise = true;
                    goto pass;
                }

                if(super_neutralise){
                    cmd.append((const char *)"\\");
                    super_neutralise = false;
                    goto pass;
                }
                super_neutralise = true;
                goto pass;
            }
pass:       i++;     
        }
        return cmd;
    }
char * cover_char_tab(char c, char * r){
    r[0]=c;
    r[1]='\0';
    return r;
}
    