#include <iostream>
#include <fstream>
#include "header.h"
#include <string>
    using namespace std;

    int main(int argc, char**argv){
        

        bool optionsActive[4] = {false},hasOptions = false ;
        int currentState, nfiles(0), i(0);
        unsigned int nbWord(0), nbLetter(0), nbLigne(0), j(0), maxLingne(0), total[4]= {0};
        string ligne, nameFile, option, filesActive[100];
        
        
        for( i=1; i<argc; i++ )
        {
            option = argv[i];
            if( option[0] == '-' )
            {
                hasOptions = true; 
                if( option.length() > 2 )
                {
                    for( j=1; j<option.length(); j++ )
                    {
                        if( !active_option(option[j], optionsActive ))
                        {
                            cout << "count : option invalide -- \'" << option[j] << '\'' << endl;
                            return -1;
                        }
                    }
                }
                else
                {
                    if( !active_option(option[1], optionsActive) )
                    {
                        cout << "count : option invalide -- \'" << option[1] << '\'' << endl;
                        return -1;
                    }
                }
            }else{
                filesActive[nfiles] = option;
                nfiles ++;
            }
        }

        if(nfiles > 0 )
        {
            for( i = 0; i < nfiles; i++ )
            {

                nbLetter = 0;
                nbLigne = 0;
                nbWord =0;
                nameFile = filesActive[i];
                ifstream file(nameFile.c_str());

                if( file )
                {
                                                
                    
                    currentState = 2;
                    while ( getline(file, ligne) ) 
                    {
                        nbLigne++;
                        count(ligne, currentState, nbWord, nbLetter, maxLingne);
                            
                    }
                        
                    nbLigne = ( nbLigne )? nbLigne-1 : 0;
                    nbLetter += nbLigne;
                    total[0] += nbLigne;
                    total[1] += nbWord;
                    total[2] += nbLetter;
                    total[3] = ( total[3] < maxLingne )? maxLingne : total[3];

                    if( !hasOptions )
                    {
                        cout << ' '<< nbLigne << ' ' << nbWord << ' ' << nbLetter << ' ' << nameFile << endl;
                    }
                    else
                    {
                        if(optionsActive[0])
                        {
                            cout << ' '<< nbLigne;
                        }
                        if(optionsActive[1])
                        {
                            cout << ' ' << nbWord;
                        }
                        if(optionsActive[2])
                        {
                            cout << ' ' << nbLetter;
                        }
                        if(optionsActive[3])
                        {
                            cout << ' ' << maxLingne;
                        }
                            cout << ' ' << nameFile << endl;
                    }
                     
                }
                else
                {
                    cerr << "ERREUR: Impossible d'ouvrir le fichier" << nameFile << endl;
                }
                    
            }
            if( nfiles > 1 ){
                cout << ' '<< total[0] << ' ' << total[1] << ' ' << total[2] << " total" << endl;
            }
        }
        else
        {
                
            currentState = 2;
            while ( getline(cin, ligne) ) 
            {
                nbLigne++;
                count(ligne, currentState, nbWord, nbLetter, maxLingne);
                        
            }
                    
            nbLigne = ( nbLigne )? nbLigne-1 : 0;
            nbLetter += nbLigne;
            
            if( !hasOptions )
            {
                cout << '\t'<< nbLigne << '\t' << nbWord << '\t' << nbLetter << '\t' << nameFile << endl;
            }
            else
            {
                if( optionsActive[0] )
                {
                    cout << '\t' << nbLigne;
                }
                if(optionsActive[1])
                {
                    cout << '\t' << nbWord;
                }
                if(optionsActive[2])
                {
                    cout << '\t' << nbLetter;
                }
                if(optionsActive[3])
                {
                    cout << '\t' << maxLingne;
                }
                cout << endl;
            }
        }
        
        return 0;
    }
