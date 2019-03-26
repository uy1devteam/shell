#include "symbol.h"

 symbol::symbol(char c)
 {
     letter = c;
 }
 char symbol::get(){
     return letter;
 }
 int symbol::set(char c){
     letter = c;
     return 1;
 }
 symbol::~symbol()
 {
 }
 int operator== (symbol s1, symbol s2){
     return s1.letter == s2.letter;
 }
symbol& symbol::operator= (const symbol & s1){
        if (this != &s1){
            letter = s1.letter;
        }

        
        return *this;
}
int symbol::cmp(char c){
    return c - letter;
}