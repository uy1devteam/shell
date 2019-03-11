#include <iostream>
#include <fstream>
#include <string>
#include "header.h"

using namespace std;

int main(int argc, char**argv)
{
    bool isPipe = false;
    long start(-1),  end(-1), first(1) , seconde(2), nbOfNb(0);
    long* numbersListe, *fiboTable;
    string file;
    string  option;
    char* separator ;
    char t[] = "\t";
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
                /* add number to  array of number */
                {
                    long _numbersListe [nbOfNb + 1 ] = {0}, j;
                    for( j = 0; j < nbOfNb; j++)
                    {
                        _numbersListe[j] = numbersListe[j];
                    }
                    numbersListe = new long [ nbOfNb + 1 ]; 
                    for( j = 0; j < nbOfNb; j++)
                    {
                        numbersListe[j] = _numbersListe[j];
                    }
                    numbersListe[nbOfNb] = convertion( argv[i] );
                    if(numbersListe[nbOfNb]<0){
                        cerr << "fibo: les indices doivent etre positif " << numbersListe[nbOfNb] << endl;
                        return -1;
                    }
                    nbOfNb++;
                }
            }
            
        }
    

    if(nbOfNb > 0)
    {
        
        if(start != -1 && end != -1 )
        {
           if(end < start){
                cerr << "fibo : le debut de l'interval de valeur doit inferieur a la fin" << endl;
                return -1;
            }
            long max = maximum(numbersListe,nbOfNb,end);
            {
                long j = 2;
                fiboTable = new long [ max + 1 ];
                fiboTable[0] = first;
                fiboTable[1] = seconde;
                while(j <= max)
                {
                   
                    fiboTable[j] = fiboTable[j -1] + fiboTable[j-2];
                    j++; 
                }
                   
            }
        }
        else
        {
            long max = maximum(numbersListe,nbOfNb,end);
            {
                long j = 2;
                fiboTable = new long [ max + 1 ];
                fiboTable[0] = first;
                fiboTable[1] = seconde;
                while(j <= max)
                {
                   
                    fiboTable[j] = fiboTable[j -1] + fiboTable[j-2];
                    j++; 
                }
                   
            }
        }
    }
    else
    {
        if(start != -1 && end != -1 )
        {
            if(end < start)
            {
                cerr << "fibo : le debut de l'interval de valeur doit inferieur a la fin" << endl;
                return -1;
            }
        }
        else
        {
            isPipe = true;
            string line;
            while(getline(cin,line))
            {
                
                unsigned int k = 0;
                bool isNumber = false;
                long nombre = 0;
                short signe = POSITIF;
                unsigned deg = 0;
                while( k < line.length())
                {
                    
                    if(line[k] == TIRET)
                    {
                        signe = NEGATIF;
                        k++;
                        isNumber = true;
                        deg = 0;
                        continue;
                    }
  
                    if(line[k] == ' ' || line[k] == '\t')
                    {
                        if(isNumber)
                        {
                            /* add number to  array of number */
                            {
                                long _numbersListe [nbOfNb + 1 ] = {0}, j;
                                for( j = 0; j < nbOfNb; j++)
                                {
                                    _numbersListe[j] = numbersListe[j];
                                }
                                numbersListe = new long [ nbOfNb + 1 ]; 
                                for( j = 0; j < nbOfNb; j++)
                                {
                                    numbersListe[j] = _numbersListe[j];
                                }
                                numbersListe[nbOfNb] = nombre * signe;
                                if(numbersListe[nbOfNb]<0){
                                    cerr << "fibo: les indices doivent etre positif " << numbersListe[nbOfNb] << endl;
                                    return -1;
                                }
                                nbOfNb++;
                            }
                            cout << nombre;
                            deg = 0;
                            isNumber = false;
                            signe = POSITIF;
                            nombre = 0;
                        }
                        k++;
                        continue;
                    }
                    if( line[k] > 47 && line[k] <  59){
                        isNumber = true;    
                        nombre =  nombre * 10*deg +  line[k] - 48;
                        deg ++;
                    }
                    else
                    {
                        cerr <<" fibo : " << line[k] << " is not a number" << endl;
                        return -1;
                    }
                        k++;
                    
                }
                if(isNumber)
                    {
                        /* add number to  array of number */
                        {
                            long _numbersListe [nbOfNb + 1 ] = {0}, j;
                            for( j = 0; j < nbOfNb; j++)
                            {
                                _numbersListe[j] = numbersListe[j];
                            }
                            numbersListe = new long [ nbOfNb + 1 ]; 
                            for( j = 0; j < nbOfNb; j++)
                            {
                                numbersListe[j] = _numbersListe[j];
                            }
                            numbersListe[nbOfNb] = nombre * signe;
                            if(numbersListe[nbOfNb]<0){
                                cerr << "fibo: les indices doivent etre positif " << numbersListe[nbOfNb] << endl;
                                return -1;
                            }
                            nbOfNb++;
                        }
                       
                    }
                
                deg = 0;
                isNumber = false;
                signe = POSITIF;
                nombre = 0;      
                k = 0;  
            }
            long max = maximum(numbersListe,nbOfNb,end);
            {
                long j = 2;
                fiboTable = new long [ max + 1 ];
                fiboTable[0] = first;
                fiboTable[1] = seconde;
                while(j <= max)
                {
                   
                    fiboTable[j] = fiboTable[j -1] + fiboTable[j-2];
                    j++; 
                }
                   
            }     
        }        
    }
    if(file.length() == 0)
    {
        long i = 0;
        if(nbOfNb > 0)
        {    while( i < nbOfNb){
                cout << separator << fiboTable[numbersListe[i]];
                i++;
            }
        }
        
        if(start != -1 && end != -1)
        {    for(i = start;i<= end; i++)
            {
                cout << separator << fiboTable[i];
            }
        }

        if(!isPipe) cout << endl;
    }
    else
    {
        ofstream output(file.c_str());
                long i = 0;
        if(nbOfNb > 0)
        {    while( i < nbOfNb){
                output << separator << fiboTable[numbersListe[i]];
                i++;
            }
        }
        
        if(start != -1 && end != -1)
        {    for(i = start;i<= end; i++)
            {
                output<< separator << fiboTable[i];
            }
        }
    }
    
     

    return 0;
}