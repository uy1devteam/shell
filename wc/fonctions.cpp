#include <iostream>
#include <fstream>
#include "header.h"
#include <string>
#define READ_SEPARATOR 1
#define READ_WORD 2
#define ISOPTION true
#define NOTOPTION false
    using namespace std;
    


void help(void)
{
    cout << "Utilisation : wc [OPTION]... [FICHIER]..." << endl << endl
         << "Afficher le nombre de sauts de ligne, de mots et d'octets pour chaque FICHIER " << endl
         << "et une ligne totale si plus d'un fichier est spécifié. Un mot est une séquence" << endl
         << " de taille non nulle de caractères délimités par une espace." << endl << endl
         << "Sans FICHIER ou quand FICHIER est -, lire l'entrée standard." << endl
         << "Les options ci-dessous permettent de sélectionner les compteurs à afficher," << endl
         << " qui sont toujours utilisés dans l'ordre suivant : saut de ligne, mot, caractère, octet, longueur de ligne maximale." << endl 
         << "   -m, --chars            afficher le nombre de caractères" << endl
         << "   -l, --lines            afficher le nombre de sauts de lignes" << endl
         << "   -L, --max-line-length  afficher la largeur maximale d'affichage " << endl
         << "   -w, --words            afficher le nombre de mots" << endl
         << "   --help     afficher l'aide et quitter" << endl;
         
}
bool active_option(unsigned char option, bool* optionsActive )
{
    switch (option)
    {
        case 'l':
                optionsActive[0]= true;
            break;
        case 'w':
                optionsActive[1]= true;
            break;
        case 'm':
                optionsActive[2] = true;
            break;
        case 'L':
                optionsActive[3] = true;
            break;
        default:
            return NOTOPTION;
        
    }
    return ISOPTION;
    
}


bool active_long_option(string option, bool* optionsActive)
{
    
    if(option.compare((string)"--lines") ==  EQUAL)
    {
        optionsActive[0] = true;
        return ISOPTION;
    }

    if(option.compare((string)"--words") ==  EQUAL)
    {
        optionsActive[1] = true;
        return ISOPTION;
    }

    if(option.compare((string)"--chars") ==  EQUAL)
    {
        optionsActive[2] = true;
        return ISOPTION;
    }

    if(option.compare((string)"--max-line-length") ==  EQUAL)
    {
        optionsActive[3] = true;
        return ISOPTION;
    }

    return NOTOPTION;
}

    /**
      * fonction qui teste la lettre c 
      * retourne 1 si la lettre est un separateur 
      *  0 sinon 
      * */
bool is_separator (unsigned char c)
{
	int status = false;
	
    if(  (c <48 && c != 38)|| (c > 57 && c < 64 )|| (c > 90 && c < 95 && c!=95)||(c > 122 && c < 128)||(c > 165 && c < 181 && c != 169)||(c > 184 && c < 198 && c != 189 )||(c > 199 && c < 208 )||(c>216 && c!=223 && c<224 ) )
	 status = true;
	return status;
}
void count(string const& ligne, int& currentState,unsigned int& nbWord, unsigned int& nbLetter, unsigned int& maxLingne)
{
    unsigned int i(0);
    nbLetter += ligne.length(); 
    maxLingne = (maxLingne < ligne.length())? ligne.length() : maxLingne;
    for (i=0;i<ligne.length();i++){
        
        if (is_separator(ligne[i])) 
        { /* *lecture est un séparateur */
	 	    if (currentState == READ_SEPARATOR ) currentState = READ_WORD;	
        }
	    else 
        { /* *lecture est une lettre */
            
	        if (currentState == READ_WORD) {currentState = READ_SEPARATOR; nbWord++;}
        }
    }
	 	        

}
