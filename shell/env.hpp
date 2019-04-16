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
            int new_number(const char *, const char *);
            int delete_var(const char *);
            std::string get(const char *);
            std::string update(const char *,const char *);
        };
         
        
    }
    
    
#endif