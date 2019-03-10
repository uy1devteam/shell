#include <iostream>
#include <fstream>
#include "header.h"

    using namespace std;
    
    
    /**
      * fonction qui teste la lettre c 
      * retourne 1 si la lettre est un separateur 
      *  0 sinon 
      * */

void help(void)
{
    cout << "Utilisation : fibo [OPTION]... [FICHIER]..." << endl << endl
         << "Cacule le nieme nombre de la suite de Fibonacci n etant fournie en entré ou les nombres " << endl
         << "de la suite dans un enterval d'indice le resultat peut etre stocker dans un fichier" << endl
         << " de taille non nulle de caractères délimités par une espace." << endl << endl
         << "Les options ci-dessous permettent de sélectionner les intervalles à afficher," << endl 
         << "   -f, --first            afficher le nombre de caractères" << endl
         << "   -s, --second            afficher le nombre de sauts de lignes" << endl
         << "   -F, --file  afficher la largeur maximale d'affichage " << endl
         << "   -w, --words            afficher le nombre de mots" << endl
         << "   --help     afficher l'aide et quitter" << endl;
         
}
long conver(char * chaine){
    unsigned i = 0;
    long nombre = 0;
    while(chaine[i] != '\0'){
        if(chaine[i]>48 && chaine[i] <  59){
            
            nombre =  nombre * 10*i +  chaine[i] - 48;
            
        }else{
            return -1;
        }
        i++;
    }
     return nombre;
}
long fibo(long n, long first , long seconde ){
    long U[]={first,seconde,0};
    while( n > 1 ){
        U[2] = U[0] + U[1];
        U[0] = U[1];
        U[1] = U[2];
        n--;
    }
    return U[n];
}
