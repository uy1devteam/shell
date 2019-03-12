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
    cout << "Utilisation : harmo [OPTION value]... " << endl << endl
         << "Cacule le nieme nombre de la suite Harmonique n etant fournie en entré ou les nombres " << endl
         << "de la suite dans un enterval d'indice, le plus petit indice etant 0, le resultat peut etre stocker dans un fichier" << endl
         << " de taille non nulle de caractères délimités par une espace." << endl << endl
         << "Les options sont : " << endl 
         << "   -F, --file  specifie le fichier de sortie (mode d'ouverture ecriture) " << endl
         << "   -S, --start      permet de determiner le debut de l'interval de valeur a calculer " << endl
         << "   -E, --end      permet de determiner la fin de l'interval de valeur a calculer" << endl
         << "   --space=     pour preciser le separateur par defaut, c'est la tabulation" << endl
         << "   --help     afficher l'aide et quitter" << endl;
         
}

bool active_option(unsigned char option, int& i, int argc ,char** argv, long& start, long& end, string& file )
{
    switch (option)
    {
        case 'F':
                if( i == argc)
                {
                    cerr << "prod : usage option value" << endl;
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
                    cerr << "prod : usage option value" << endl;
                    exit(EXIT_FAILURE);
                }
                else
                {
                    start = convertion(argv[++i]);   
                    if(start < 0)
                    {
                        cerr << "prod : start doit avoir une valeur positive" << endl;
                        exit(-1);
                    }
                }
            break;
        case 'E':
                if( i == argc)
                {
                    cerr << "prod : usage option value" << endl;
                    exit(EXIT_FAILURE);
                }
                else
                {
                    end = convertion(argv[++i]);
                    if(end < 0)
                    {
                        cerr << "prod : end doit avoir une valeur positive" << endl;
                        exit(-1);
                    }   
                }
            break;
        default:
            return NOTOPTION;
        
    }
    return ISOPTION;
    
}


bool active_long_option(string option, int& i, int argc ,char** argv, long& start, long& end, string& file)
{
    

    if(option.compare((string)"--file") ==  EQUAL)
    {
        if( i == argc)
        {
            cerr << "prod : usage option value" << endl;
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
            cerr << "prod : usage option value" << endl;
            exit(-1);
        }
        else
        {
            start = convertion(argv[++i]);
            if(start < 0){
                cerr << "prod : start doit avoir une valeur positive" << endl;
                exit(-1);
            }   
        }
        return ISOPTION;
    }

    if(option.compare((string)"--end") ==  EQUAL)
    {
        if( i == argc)
        {
            cerr << "prod : usage option value" << endl;
            exit(EXIT_FAILURE);
        }
        else
        {
            end = convertion(argv[++i]);
            if(end < 0){
                cerr << "prod : end doit avoir une valeur positive" << endl;
                exit(-1);
            }   
        }
        return ISOPTION;
    }

    return NOTOPTION;
}
double convertion(char * chaine)
{
    unsigned long i(0), j(1);
    double nombre = 0;
    short signe = POSITIF;
    bool isDecimal = false;
    if(chaine[0] == TIRET)
    {
        signe = NEGATIF;
        i++;
    }
    while(chaine[i] != '\0'){
        if(chaine[i] == '.' || chaine[i] == ','){
            isDecimal = true;
            i++;
            break;
        }
        if( chaine[i] > 47 && chaine[i] <  59){
            
            nombre =  nombre * 10*i +  chaine[i] - 48;
            
        }else{
            cerr <<" prod : " << chaine << " nombre invalide" << endl;
            exit(EXIT_FAILURE);
        }
        i++;
    }
    if(isDecimal){
        while(chaine[i] != '\0'){
            if( chaine[i] > 47 && chaine[i] <  59){
                
                nombre =  nombre  +  (double)(chaine[i] - 48)/( 10*j);
                
                
            }else{
                cerr <<"prod : " << chaine << " is not a number" << endl;
                exit(EXIT_FAILURE);
            }
            i++;
            j++;
        }
        
    }
    return nombre * signe;
}

