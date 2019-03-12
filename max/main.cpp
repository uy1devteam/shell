#include <iostream>
#include <fstream>
#include <string>
#include "header.h"

using namespace std;

int main(int argc, char**argv)
{
    bool first = true;
    long  nbOfNb(0); 
    double max = 0;
    string file;
    string  option;
    char* separator ;
    char t[] = "   ";
    separator = t;


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
                        
                    if( !active_long_option(option, i, argc, argv, file) )
                    {
                        cerr << "nax : option non reconnue  << " << option << " >>" << endl;
                        return -1;
                    }    
                }
                else
                {

                    
                    if( option.length() > 2 )
                    {
                        for(unsigned int j = 1; j<option.length(); j++ )
                        {
                            if( !active_option(option[j], i, argc, argv, file ))
                            {
                                cerr << "max : option invalide -- \'" << option[j] << '\'' << endl;
                                return -1;
                            }
                           
                        }
                    }
                    else
                    {
                        if( !active_option(option[1], i, argc, argv, file ) )
                        {
                           goto testIfNumber;
                        }
                    }
                }
            }
            else
            {
testIfNumber :  double nb = convertion( argv[i] );
                if(first)
                {
                    max = nb;
                    first = false;
                }
                else
                {
                    max = ( nb > max)? nb : max;
                }
                
                nbOfNb++;
                
            }
            
        }
    

    if(nbOfNb == 0)
    {
        
        string line;
        while(getline(cin,line))
        {
            
            unsigned int k(0);
            bool isNumber(false);
            double nombre(0);
            short signe = POSITIF;
            unsigned long deg(0), deci(1);
            bool isDecimal(false);

            while( k < line.length())
            {
                
                if(line[k] == TIRET)
                {
                    signe = NEGATIF;
                    k++;
                    isNumber = true;
                    isDecimal = 0;
                    deg = 0;
                    deci = 0;
                    continue;
                }

                if(line[k] == ' ' || line[k] == '\t')
                {
                    if(isNumber)
                    {
                        double nb = nombre * signe;
                        if(first)
                        {
                            max = nb;
                            first = false;
                        }
                        else
                        {
                            max = ( nb > max)? nb : max;
                        }
                        deg = 0;
                        isNumber = false;
                        deci = 0;
                        isDecimal = 0;
                        nombre = 0;
                    }
                    signe = POSITIF;
                    k++;
                    continue;
                }
                if(line[k] == '.' || line[k] == ','){
                    if(isNumber)
                    {
                        isDecimal = true;
                    }
                    else
                    {
                        cerr << "max : " << line[k] << " is not a number" << endl;
                        return -1;
                    }
                    
                    k++;
                    continue;
                }
                if( line[k] > 47 && line[k] <  59){
                    isNumber = true;
                    if(isDecimal){
                        nombre =  nombre  +  (double)(line[k] - 48)/( 10*deci);
                        deci ++;
                    }    
                    else
                    {
                        nombre =  nombre * 10*deg +  line[k] - 48;
                        deg ++;
                    }
                    
                    
                }
                else
                {
                    cerr << "max : " << line[k] << " is not a number" << endl;
                    return -1;
                }
                    k++;
                
            }
            if(isNumber)
            {
                    
                double nb = nombre * signe;
                if(first)
                {
                    max = nb;
                }
                else
                {
                    max = ( nb > max)? nb : max;
                }

            }
            deci = false;
            deg = 0;
            isNumber = false;
            isDecimal = false;
            signe = POSITIF;
            nombre = 0;      
            k = 0;  
        }
                
                
    }
    if(file.length() == 0)
    {
        cout << separator << max << endl;
    }
    else
    {
        ofstream output(file.c_str());
        output<< separator << max << endl;
         
    }
    
     

    return 0;
}