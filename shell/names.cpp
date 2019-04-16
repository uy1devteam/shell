#include "names.hpp"

namespace names{
    base null("null",NOTYPE);
    bool operator==(base n1,base n2){
        if (n1.name.compare(n2.name.c_str()) == EQUAL){
            if(n1.TYPE.compare(n2.TYPE.c_str())){
                return true;
            }
        }
        return false;
    }
    base::base(std::string name, std::string type){
        name = name;
        TYPE = type; 
    }
    base::base(std::string name, const char * type){
        this->name = name;
        std::string tampon(type);
        TYPE = tampon; 
    }
    base::base(const char * name, const char * type){
        
        std::string tampon(type);
        TYPE = tampon;
        tampon.clear();
        tampon.append(name);
        this->name = tampon; 
    }
    std::string base::type(){
        return TYPE;
    }
    std::string base::get(){
        return name;
    }
    bool  base::is (const char * type ){
        return TYPE.compare(type) == EQUAL;
    }
    int  base::cmp(const char * n){
        return name.compare(n);
    }
    bool is_null(base n){
        return n == null;
    }

    base& base::operator= (const base & l1)
    {
        if (this != &l1){
            this->name = l1.name;
            this->TYPE = l1.TYPE;
        }


        return *this;
    }
    namesGestion::namesGestion(){

    }
    base namesGestion::getAndDelete( const char * n){
        base tampon("null",NOTYPE);
        std::vector <base>::iterator il;
        for(il = names.begin(); il != names.end(); il++){
            //std::cout << (*il).cmp(n) << "D"<< "\n";
            if((*il).cmp(n) == EQUAL){
                tampon = *il;
                names.erase(il);
                break;
            }
        }
        return tampon;
    }
    bool namesGestion::add(const char * name, const char * type){
        base tampon(name, type);
        names.push_back(tampon);
        return true;
    }
    base namesGestion::get(const char * n){
        
        std::vector <base>::iterator il;
        for(il = names.begin(); il != names.end(); il++){
            if((*il).cmp(n) == EQUAL){
                
                return *il;
                
            }
        }
        return null;
    }
    bool namesGestion::find( const char * n){
        bool  isUsed = false;
        std::vector <base>::iterator il;
        for(il = names.begin(); il != names.end(); il++){
            if((*il).cmp(n) == EQUAL){
                isUsed = true;
                break;
            }
        }
        return isUsed;
    }
    bool namesGestion::erase( const char * n){
        bool  pb = false;
        std::vector <base>::iterator il;
        for(il = names.begin(); il != names.end(); il++){
            if((*il).cmp(n) == EQUAL){
                names.erase(il);
                break;
            }
        }
        return pb;
    }
}