#include <iostream>
#include <fstream>
#include "header.h"
#include <string>
    using namespace std;

    int main(int argc, char**argv){
        

    
    int currentState;
    unsigned int nbWord(0);
    unsigned int nbLetter(0);
    unsigned int nbLigne(0);
    string ligne;
    string nameFile;

    if (argc >2)
    { 
        cerr << "usage : count nomdefichier" << endl;
        return -1;
	}
    if(argc == 2)
    {
        nameFile = argv[1];
        ifstream file(nameFile.c_str());
        if(file)
        {
                	 	                 
            
	 	    currentState = 2;
	 	    while (getline(file, ligne)) 
            {
                nbLigne++;
                count(ligne, currentState, nbWord, nbLetter);
                    
            }
                
            nbLigne = (nbLigne)?nbLigne-1:0;
            nbLetter += nbLigne;
            cout << ' '<< nbLigne << ' ' << nbWord << ' ' << nbLetter << ' ' << nameFile << endl; 
        }
        else
        {
            cerr << "ERREUR: Impossible d'ouvrir le fichier" << nameFile << endl;
            return -1;
        }
            

	    }
        else{
            
	 	    currentState = 2;
	 	    while (getline(cin, ligne)) 
            {
                nbLigne++;
                count(ligne, currentState, nbWord, nbLetter);
                    
            }
                
            nbLigne = (nbLigne)?nbLigne-1:0;
            nbLetter += nbLigne;
            cout << ' '<< nbLigne << ' ' << nbWord << ' ' << nbLetter << ' ' << nameFile << endl;
        }
        return 0;
    }
