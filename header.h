#include <string>
    using namespace std;
#ifndef HEADER_H_INCLUDES
#define HEADER_H_INCLUDES
#define EQUAL 0
#define TIRET '-'
#define SPACE ' '
#define TAB '\t'

    void help(void);
    bool is_separator (unsigned char c);
    bool active_option(unsigned char option, bool* optionsActive);
    bool active_long_option(string option, bool* optionsActive);
    void count(string const& ligne, int& currentState,unsigned int& nbWord, unsigned int& nbLetter, unsigned int& maxLingne);
#endif