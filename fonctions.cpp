#include <iostream>
#include <fstream>
#include "header.h"
#include <string>
#define READ_SEPARATOR 1
#define READ_WORD 2
    using namespace std;
    
    /**
      * fonction qui teste la lettre c 
      * retourne 1 si la lettre est un separateur 
      *  0 sinon 
      * */
int is_option(unsigned char letter){
    int option = -1;
    switch (letter)
    {
        case 'l':
                option = 1;
            break;
        case 'w':
                option = 2;
            break;
        default:
            break;
    }
    return option;
}
bool active_option(unsigned char option, bool* optionsActive ){
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
            return false;
        
    }
    return true;
    
}
bool is_separator (unsigned char c){
	int status = false;
	
    if(  (c <48 && c != 38)|| (c > 57 && c < 64 )|| (c > 90 && c < 95 && c!=95)||(c > 122 && c < 128)||(c > 165 && c < 181 && c != 169)||(c > 184 && c < 198 && c != 189 )||(c > 199 && c < 208 )||(c>216 && c!=223 && c<224 ) )
	 status = true;
	return status;
}
void count(string const& ligne, int& currentState,unsigned int& nbWord, unsigned int& nbLetter, unsigned int& maxLingne){
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
