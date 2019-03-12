#ifndef HEADER_H_INCLUDES
#define HEADER_H_INCLUDES
#define EQUAL 0
#define TIRET '-'
#define SPACE ' '
#define TAB '\t'
#define POSITIF 1
#define NEGATIF -1
#include <string>
    using namespace std;

    void help( void );
    double convertion(char * chaine);
    bool active_option(unsigned char option, int& i, int argc ,char** argv, long& start, long& end, string& file );
    bool active_long_option(string option, int& i, int argc ,char** argv, long& start, long& end, string& file);

#endif