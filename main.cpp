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

    
 
    Environnement *var_environnement=NULL;
    int     global_argc, histocount;
    FILE *fichier,*fichier_historique;
    char *arg_list[32],*arg_list2[32];
    char buffer[250];
    ifstream file;
    int main(int argc,char *argv[],char *arge[])
    {

        global_argc=argc;
        int increment=0;
        while (arge[increment]!=NULL)
        {
            char *valeur=strstr(arge[increment],"=");
            char *nom=strndup(arge[increment],strlen(arge[increment])-strlen(valeur));
            ajout_environnement(nom,valeur+1,var_environnement);
            free(nom);
            ++increment;
        }
        if (argc>1)
        {
            
            fichier=fopen(argv[1],"r");
            if (fichier==NULL)
            {
                cerr <<argv[1]<<" "<<strerror(errno)<<endl;
                exit(EXIT_FAILURE);
            }
            
        }
        else 
        {
            fichier=stdin;
        }
        while(!feof(fichier))
        {
            if (argc==1) cout <<"Prompt : ";
            char *lecture=fgets(buffer,TAILLE_TAMPON,fichier);
            
            if (lecture==NULL)
            {
                exit(EXIT_SUCCESS);
            }
            if (buffer[strlen(buffer)-1]=='\n') buffer[strlen(buffer)-1]='\0';
            traitement_ligne(buffer, arg_list, arg_list2, argv, var_environnement, fichier, global_argc);
            
        }
        return 0;
    }