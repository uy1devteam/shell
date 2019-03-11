#include <iostream>
#include <fstream>
#include <string>
#include "header.h"
#include <stdlib.h>
#define ISOPTION true
#define NOTOPTION false

    using namespace std;
    
    
  

void help(void)
{
    cout << "Utilisation : fibo [OPTION value]... [FICHIER]..." << endl << endl
         << "Cacule le nieme nombre de la suite de Fibonacci n etant fournie en entré ou les nombres " << endl
         << "de la suite dans un enterval d'indice le resultat peut etre stocker dans un fichier" << endl
         << " de taille non nulle de caractères délimités par une espace." << endl << endl
         << "Les options ci-dessous permettent de sélectionner les intervalles à afficher," << endl 
         << "   -f, --first            afficher le nombre de caractères" << endl
         << "   -s, --second            afficher le nombre de sauts de lignes" << endl
         << "   -F, --file  afficher la largeur maximale d'affichage " << endl
         << "   -S, --start            afficher le nombre de mots" << endl
         << "   -E, --end            afficher le nombre de mots" << endl
         << "   --space=     pour preciser le separateur par defaut, c'est la tabulation" << endl
         << "   --help     afficher l'aide et quitter" << endl;
         
}
long maximum(long tab[], long length, long end ){
    long max(0), i(0);
    while(i<length){
        max = (max < tab[i] )? tab[i] : max;
        i++;
    }
    return (max < end )? end : max;
}
bool active_option(unsigned char option, int& i, int argc ,char** argv,long& first, long& seconde, long& start, long& end, string& file )
{
    switch (option)
    {
        case 'f':
                if( i == argc)
                {
                    cerr << "fibo : usage option value" << endl;
                    exit(EXIT_FAILURE);
                }
                else
                {
                    first = convertion(argv[++i]);   
                }
            break;
        case 's':
                if( i == argc)
                {
                    cerr << "fibo : usage option value" << endl;
                    exit(EXIT_FAILURE);
                }
                else
                {
                    seconde = convertion(argv[++i]);   
                }
            break;
        case 'F':
                if( i == argc)
                {
                    cerr << "fibo : usage option value" << endl;
                    exit(EXIT_FAILURE);
                }
                else
                {
                    file = argv[++i];   
                }
            break;
        case 'S':
                if( i == argc)
                {
                    cerr << "fibo : usage option value" << endl;
                    exit(EXIT_FAILURE);
                }
                else
                {
                    start = convertion(argv[++i]);   
                    if(start < 0)
                    {
                        cerr << "fibo : start doit avoir une valeur positive" << endl;
                        exit(-1);
                    }
                }
            break;
        case 'E':
                if( i == argc)
                {
                    cerr << "fibo : usage option value" << endl;
                    exit(EXIT_FAILURE);
                }
                else
                {
                    end = convertion(argv[++i]);
                    if(end < 0)
                    {
                        cerr << "fibo : end doit avoir une valeur positive" << endl;
                        exit(-1);
                    }   
                }
            break;
        default:
            return NOTOPTION;
        
    }
    return ISOPTION;
    
}


bool active_long_option(string option, int& i, int argc ,char** argv,long& first, long& seconde, long& start, long& end, string& file)
{
    
    if(option.compare((string)"--first") ==  EQUAL)
    {
        if( i == argc)
        {
            cerr << "fibo : usage option value" << endl;
            exit(EXIT_FAILURE);
        }
        else
        {
            first = convertion(argv[++i]);   
        }
        return ISOPTION;
    }

    if(option.compare((string)"--seconde") ==  EQUAL)
    {
        if( i == argc)
        {
            cerr << "fibo : usage option value" << endl;
            exit(EXIT_FAILURE);
        }
        else
        {
            seconde = convertion(argv[++i]);   
        }        return ISOPTION;
    }

    if(option.compare((string)"--file") ==  EQUAL)
    {
        if( i == argc)
        {
            cerr << "fibo : usage option value" << endl;
            exit(EXIT_FAILURE);
        }
        else
        {
            file = argv[++i];   
        }
        return ISOPTION;
    }

    if(option.compare((string)"--start") ==  EQUAL)
    {
        if( i == argc)
        {
            cerr << "fibo : usage option value" << endl;
            exit(-1);
        }
        else
        {
            start = convertion(argv[++i]);
            if(start < 0){
                cerr << "fibo : start doit avoir une valeur positive" << endl;
                exit(-1);
            }   
        }
        return ISOPTION;
    }

    if(option.compare((string)"--end") ==  EQUAL)
    {
        if( i == argc)
        {
            cerr << "fibo : usage option value" << endl;
            exit(EXIT_FAILURE);
        }
        else
        {
            end = convertion(argv[++i]);
            if(end < 0){
                cerr << "fibo : end doit avoir une valeur positive" << endl;
                exit(-1);
            }   
        }
        return ISOPTION;
    }

    return NOTOPTION;
}
long convertion(char * chaine)
{
    unsigned i = 0;
    long nombre = 0;
    short signe = POSITIF;
    if(chaine[0] == TIRET)
    {
        signe = NEGATIF;
        i++;
    }
    while(chaine[i] != '\0'){
        if( chaine[i] > 47 && chaine[i] <  59){
            
            nombre =  nombre * 10*i +  chaine[i] - 48;
            
        }else{
            cerr <<" fibo : " << chaine << " is not a number" << endl;
            exit(EXIT_FAILURE);
        }
        i++;
    }
    return nombre * signe;
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
