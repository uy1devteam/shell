#include <iostream>
#include <fstream>
#include <string>
#include "header.h"
#include "fonctionlogique.h"

using namespace std;

int main(int argc, char**argv)
{
    
    long start(-1),  end(-1), first(1) , seconde(2), nbOfNb(0);
    long* numbersListe, *fiboTable;
    string file;
    string  option;
    char* separator ;
    char t[] = "   ";
    separator = t;
    fonctionlogique F;

    for(int i = 1; i<argc; i++ )
        {
            option = argv[i];
            if( option[0] == TIRET )
            {
                 
                if( option[1] == TIRET )
                {
                    
                    if( option.compare((string)"--help") == EQUAL)
                    {
                        help();
                        return 0;
                    }         
                    if(option.compare((string)"--space") >  EQUAL)
                    {
                        string spacer = argv[i];
                        if( spacer.length() <= 7)
                        {
                            cerr << "fibo : usage option --space=value" << endl;
                            return -1;
                        }
                        else
                        {
                            int length = spacer.length() - 7;
                            separator = new char [ length + 1];
                            for(int l = 0; l < length; l++)
                            {
                                separator[l] = spacer[l + 8];
                            }
                        
                        }
                        continue;
                    }    
                    if( !active_long_option(option, i, argc, argv, first, seconde, start, end, file) )
                    {
                        cerr << "fibo : option non reconnue  << " << option << " >>" << endl;
                        return -1;
                    }    
                }
                else
                {

                    
                    if( option.length() > 2 )
                    {
                        for(unsigned int j = 1; j<option.length(); j++ )
                        {
                            if( !active_option(option[j], i, argc, argv, first, seconde, start, end, file ))
                            {
                                cerr << "fibo : option invalide -- \'" << option[j] << '\'' << endl;
                                return -1;
                            }
                           
                        }
                    }
                    else
                    {
                        if( !active_option(option[1], i, argc, argv, first, seconde, start, end, file ) )
                        {
                            cerr << "fibo : option invalide -- \'" << option[1] << '\'' << endl;
                            return -1;
                        }
                    }
                }
            }
            else
            {
                std::cout << "fdf" << endl;
                combinaison t (option.c_str());
                std::cout << "fdf" << endl;
                F.add(t);
                std::cout << "fddsdsf" << endl;
                F.developpe();
                std::cout << "fdsdsdf" << endl;
                cout << t.to_int() << endl;
            }
            
        }
    

    
    return 0;
}