#ifndef NAMES_H_INCLUDES
#define NAMES_H_INCLUDES
#include <iostream>
#include <string>
#include <vector>
#define EQUAL 0
#define NOTYPE ""
namespace names{ 
            
            class base
            {
                private:
                std::string name;
                std::string TYPE;
                public:
                base(std::string , std::string );
                base(std::string , const char * );
                base(const char *, const char * );
                std::string type(void);
                int cmp(const char *);
                std::string get(void); 
                bool is(const char *);
                friend bool operator==(base,base);
                base& operator= (const base & );   
            };
            bool is_null(base);

             
            
            
            class namesGestion{
                private:
                std::vector<base> names;
                public:
                namesGestion();
                bool find(const char *);
                bool erase(const char *);
                bool add(const char *, const char *);
                base get(const char *);
                base getAndDelete(const char *);
                base& operator= (const base & l1);
            };
            
        };
#endif