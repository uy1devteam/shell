#include <iostream>
#include <fstream>
#include "header.h"
#include <string>

    using namespace std;

    int main(int argc, char**argv){
        

        bool optionsActive[4] = {false}, hasOptions = false ;
        int currentState,  i(0);
        unsigned int nbWord(0), nbLetter(0), nbLigne(0), j(0), maxLingne(0), total[4]= {0}, nbFiles(0);
        string ligne, option;
        string* filesListes;
        char separator = SPACE;
        
        for( i=1; i<argc; i++ )
        {
            option = argv[i];
            if( option[0] == TIRET )
            {
                 
                if( option[1] == TIRET )
                {
                    hasOptions = true;
                    if( option.compare((string)"--help") == EQUAL){
                        help();
                        return 0;
                    }         

                    if( !active_long_option(option,optionsActive) )
                    {
                        cout << "count : option non reconnue  << " << option << " >>" << endl;
                        return -1;
                    }    
                }
                else
                {

                    if( option.length() == 1 )
                    {
                        separator = TAB;

                        /* add name of file to string array of files */        
                        {
                            string _filesListes [nbFiles + 1 ] ={(string)""};
                            for( unsigned int i = 0; i < nbFiles; i++){
                                _filesListes[i].append(filesListes[i].c_str());
                            }
                            filesListes = new string [ nbFiles + 1 ]; 
                            for( unsigned int i = 0; i < nbFiles; i++){
                                filesListes[i].append(_filesListes[i].c_str());
                            }
                            filesListes[nbFiles] = option;
                            nbFiles++;
                        }
                        continue;
                    }
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
                }
            }
            else
            {
                /* add name of file to string array of files */
                {
                    string _filesListes [nbFiles + 1 ] ={(string)""};
                    for( unsigned int i = 0; i < nbFiles; i++)
                    {
                        _filesListes[i].append(filesListes[i].c_str());
                    }
                    filesListes = new string [ nbFiles + 1 ]; 
                    for( unsigned int i = 0; i < nbFiles; i++)
                    {
                        filesListes[i].append(_filesListes[i].c_str());
                    }
                    filesListes[nbFiles] = option;
                    nbFiles++;
                }
            }
        }

        if( nbFiles > 0 )
        {
            for( unsigned int i = 0; i < nbFiles; i++ )
            {

                nbLetter = 0;
                nbLigne = 0;
                nbWord =0;
                if(filesListes[i].compare((string)"-") == EQUAL)
                {
                    
                    while ( getline(cin, ligne) ) 
                    {
                        nbLigne++;
                        count(ligne, currentState, nbWord, nbLetter, maxLingne);
                                
                    }
                       
                    nbLigne = ( nbLigne )? nbLigne - 1 : 0;
                    nbLetter += nbLigne;
                    total[0] += nbLigne;
                    total[1] += nbWord;
                    total[2] += nbLetter;
                    total[3] = ( total[3] < maxLingne )? maxLingne : total[3];

                    if( !hasOptions )
                    {
                        cout << separator  << nbLigne << separator << nbWord << separator << nbLetter << separator << filesListes[i] << endl;
                    }
                    else
                    {  
                        
                        if(optionsActive[0])
                        {
                            cout << separator << nbLigne;
                        }
                        if(optionsActive[1])
                        {
                            cout << separator << nbWord;
                        }
                        if(optionsActive[2])
                        {
                            cout << separator << nbLetter;
                        }
                        if(optionsActive[3])
                        {
                            cout << separator << maxLingne;
                        }
                            cout << separator << filesListes[i] << endl;
                    }
                }
                else
                {
                    separator = TAB;
                    ifstream file(filesListes[i].c_str());
                    if( file )
                    {
                                                    
                        
                        currentState = 2;
                        while ( getline(file, ligne) ) 
                        {
                            nbLigne++;
                            count(ligne, currentState, nbWord, nbLetter, maxLingne);
                                
                        }
                        file.close();        
                        nbLigne = ( nbLigne )? nbLigne - 1 : 0;
                        nbLetter += nbLigne;
                        total[0] += nbLigne;
                        total[1] += nbWord;
                        total[2] += nbLetter;
                        total[3] = ( total[3] < maxLingne )? maxLingne : total[3];

                        if( !hasOptions )
                        {
                            cout << separator << nbLigne << separator << nbWord << separator << nbLetter << separator << filesListes[i] << endl;
                        }
                        else
                        {
                            if(optionsActive[0])
                            {
                                cout << separator << nbLigne;
                            }
                            if(optionsActive[1])
                            {
                                cout << separator << nbWord;
                            }
                            if(optionsActive[2])
                            {
                                cout << separator << nbLetter;
                            }
                            if(optionsActive[3])
                            {
                                cout << separator << maxLingne;
                            }
                                cout << separator << filesListes[i] << endl;
                        }
                        
                    }
                    else
                    {
                        cerr << "ERREUR: Impossible d'ouvrir le fichier " << filesListes[i] << endl;
                    }
                }
                

                
                    
            }
            if( nbFiles > 1 ){
                cout << separator << total[0] << separator << total[1] << separator << total[2] << " total" << endl;
            }
        }
        else
        {
            separator = TAB;
            currentState = 2;
            while ( getline(cin, ligne) ) 
            {
                nbLigne++;
                count(ligne, currentState, nbWord, nbLetter, maxLingne);
                        
            }
                    
            nbLigne = ( nbLigne )? nbLigne - 1 : 0;
            nbLetter += nbLigne;
            
            if( !hasOptions )
            {
                cout << separator << nbLigne << separator << nbWord << separator << nbLetter << separator << filesListes[i] << endl;
            }
            else
            {
                if( optionsActive[0] )
                {
                    cout << separator << nbLigne;
                }
                if(optionsActive[1])
                {
                    cout << separator << nbWord;
                }
                if(optionsActive[2])
                {
                    cout << separator << nbLetter;
                }
                if(optionsActive[3])
                {
                    cout << separator << maxLingne;
                }
                cout << endl;
            }
        }
        
        return 0;
    }
