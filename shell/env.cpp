
#include "env.hpp"

namespace environnement{
    std::string null("null");
    int error = 0;
        char *hadelerror[]={"New declaration","Not A number","Variable not declared in this scope"};

    bool is_null(std::string& b){
        return &b == &null;
    }
    int env::new_number(const char * id,const char * val){
            bool found = namesList.find(id);
            
            if(found){
                error = 1;
                return -1;
            }
            if( numbersList.new_number(id,val) == -1){
                
                error = 2;
                return -1;
            };
            
            namesList.add(id,"NUMBER");
            
            error = 0;
            return 1;
        }
        int env::delete_var(const char * id){
            names::base name = namesList.get(id);
            if(names::is_null(name)){
                error = 3;
                return -1;
            }
            if(name.is("NUMBER")){
                numbersList.del(id);
            }
        
            error = 0;
            return 1;
        }
        std::string env::get(const char * id){
            names::base name = namesList.get(id);
            std::string val;
            if(names::is_null(name)){
                error = 3;
                return null;
            }
            if(name.is("NUMBER")){
                error = 0;
                val = numbersList.get(id).c_str();
                
            }
           
            return val;
        }
        std::string env::update(const char * id,const char * value){
            names::base name = namesList.get(id);
            std::string val;
            if(names::is_null(name)){
                error = 3;
                return null;
            }
            if(name.is("NUMBER")){
                if(number::testdigite(value)){
                    error = 0;
                    val = numbersList.set(id,value).c_str();
                }else{
                    error = 2;
                    return null;
                }
                
                
            }
           
            return val;
        }
        env::env(/* args */)
        {
        }
        
        env::~env()
        {
        }
}