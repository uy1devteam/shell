#include <iostream>
#include <fstream>
#include <string>
#include "header.h"

using namespace std;

int main(int argc, char**argv)
{
    
    long start(-1),  end(-1), nbOfNb(0); 
    double prod = 1;
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
                    if(option.compare((string)"--space") >  EQUAL)
                    {
                        string spacer = argv[i];
                        if( spacer.length() <= 7)
                        {
                            cerr << "prod : usage option --space=value" << endl;
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
                    if( !active_long_option(option, i, argc, argv, start, end, file) )
                    {
                        cerr << "prod : option non reconnue  << " << option << " >>" << endl;
                        return -1;
                    }    
                }
                else
                {

                    
                    if( option.length() > 2 )
                    {
                        for(unsigned int j = 1; j<option.length(); j++ )
                        {
                            if( !active_option(option[j], i, argc, argv, start, end, file ))
                            {
                                goto testIfNumber;
                            }
                           
                        }
                    }
                    else
                    {
                        if( !active_option(option[1], i, argc, argv, start, end, file ) )
                        {
                            goto testIfNumber;
                        }
                    }
                }
            }
            else
            {
testIfNumber:    
                prod *= convertion( argv[i] );
                nbOfNb++;
                
            }
            
        }
    

    if(nbOfNb > 0)
    {
        
        if(start != -1 && end != -1 )
        {
           if(end < start){
                cerr << "prod : le debut de l'interval de valeur doit inferieur a la fin" << endl;
                return -1;
            }
            
        
            long j = 0;
                

            j = start; 
            while(j <= end)
            {
                    
                prod *= j;
                j++; 
            }
            
        }
        
    }
    else
    {
        if(start != -1 && end != -1 )
        {
            if(end < start)
            {
                cerr << "prod : le debut de l'interval de valeur doit inferieur a la fin" << endl;
                return -1;
            }
            long j = start; 
            while(j <= end)
            {        
                prod *= j;
                j++; 
            }
            goto suite;
        }
        else
        {
            
suite:      string line;
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
                            prod *= nombre * signe;
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
                            cerr << "prod : " << line[k] << " is not a number" << endl;
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
                        cerr << "prod : " << line[k] << " is not a number" << endl;
                        return -1;
                    }
                        k++;
                    
                }
                if(isNumber)
                {
                        
                    prod *= nombre * signe;

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
    }
    if(file.length() == 0)
    {
        cout << separator << prod << endl;
    }
    else
    {
        ofstream output(file.c_str());
        output<< separator << prod << endl;
         
    }
    
     

    return 0;
}