#ifndef NUMBER_H_INCLUDES
#define NUMBER_H_INCLUDES
#include <iostream>
#include <vector>
#include <string>
#include <gmpxx.h>
#define EQUAL 0

 
    namespace number{
        bool testdigite(const char * num);
        class base
        {
        private:
            mpf_class value;
            std::string name;
            bool isConst;
        public:
            base(std::string ,mpf_class );
            base(const char * ,mpf_class );
            base(std::string );
            mpf_class get();
            void set(mpf_class);
            bool cmp(const char *);
            bool cmp(std::string);
            bool is_null(void);
            void read_only(void);
            bool is_const(void);
            friend bool operator==(base n1, base n2); 
            friend base operator+(base n1, base n2);
            friend base operator*(base n1, base n2);
            friend base operator-(base n1, base n2);
            friend base operator/(base n1, base n2);
            base& operator= (const base & l1); 
        };

        
        
        class  NumbersGestion
        {
        private:
            std::vector <base> num;
        public:
            NumbersGestion(/* args */);
            
            int  new_number(std::string, std::string);
            int new_number(const char *, const char *);
            base get(const char *);
            int set(const char *, mpf_class);
            int del(const char *);
        };
        
    }
    
        
    
#endif