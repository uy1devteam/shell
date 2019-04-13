#ifndef ENV_H_INCLUDES
#define ENV_H_INCLUDES
#include "number.hpp"
#include "names.hpp"

    namespace environnement{
        
        class env
        {
        private:
           names::namesGestion namesList;
           number::NumbersGestion numbersList;
        public:
            env(/* args */);
            ~env();
        };
        
        env::env(/* args */)
        {
        }
        
        env::~env()
        {
        }
    }
    
    
#endif