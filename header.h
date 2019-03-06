#include <string>
    using namespace std;
#ifndef HEADER_H_INCLUDES
#define HEADER_H_INCLUDES

    bool is_separator (unsigned char c);
    void count(string const& ligne, int& currentState,unsigned int& nbWord, unsigned int& nbLetter);
#endif