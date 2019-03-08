#include <string>
    using namespace std;
#ifndef HEADER_H_INCLUDES
#define HEADER_H_INCLUDES
    int is_option(unsigned char letter);
    bool is_separator (unsigned char c);
    bool active_option(unsigned char option, bool* optionsActive);
    void count(string const& ligne, int& currentState,unsigned int& nbWord, unsigned int& nbLetter, unsigned int& maxLingne);
#endif