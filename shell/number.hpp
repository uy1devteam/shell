#ifndef NUMBER_H_INCLUDES
#define NUMBER_H_INCLUDES
#include <iostream>
#include <vector>
#include <gmpxx.h>
    namespace number{

        class base
        {
        private:

        public:
            base(/* args */);
            ~base();
        };
    
        base::base(/* args */)
        {
        }
    
        base::~base()
        {
        }
    }
    class  GessttionNumber
    {
    private:
        std::vector <number::base> num;
    public:
         GessttionNumber(/* args */);
        ~GessttionNumber();
    };
    
     GessttionNumber:: GessttionNumber(/* args */)
    {
    }
    
     GessttionNumber::~GessttionNumber()
    {
    }
        
    
#endif