#ifndef SYMBOL_H_INCLUDES
#define SYMBOL_H_INCLUDES

 class symbol
 {
 private:
    char letter;
 public:
     symbol(char );
     ~symbol(void);
    char get(void);
    int set(char );
    friend int operator== (symbol,symbol);
    symbol& operator= (const symbol&);
    int cmp(char );
 };
 

#endif