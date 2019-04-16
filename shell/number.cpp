#include "number.hpp"


namespace  number{
    base operator+(base n1 , base n2){
        base tampon("tampon", n1.value + n2.value);
        return tampon;
    }
    base operator*(base n1 , base n2){
        base tampon("tampon", n1.value * n2.value);
        return tampon;
    }
    base operator/(base n1 , base n2){
        base tampon("tampon", n1.value / n2.value);
        return tampon;
    }
    base operator-(base n1 , base n2){
        base tampon("tampon", n1.value - n2.value);
        return tampon;
    }
    std::string base::get_name(void){
        return name;
    }
    void base::read_only(){
        isConst = true;
    }
    bool base::is_const(){
        return isConst;
    }
    base& base::operator= (const base & l1){
    if (this != &l1){
        this->value = l1.value;
    }


    return *this;
    }
    bool operator==(base n1, base n2){
        return n1.value == n2.value;
    }
    base null("null");
    bool base::is_null(){
        return this->value == 0;
    }

    bool base::cmp(const char * ref){
        return name.compare(ref);
    }
    bool base::cmp(std::string ref){
        return name.compare(ref.c_str());
    }
    base::base(std::string nom ,mpf_class v)
    {
        value = v;
        name = nom;
        isConst = false; 
    }

    base::base(const char * n,mpf_class v){
        value = v;
        name.clear();
        name.append(n);
        isConst = false;
    }
    base::base(std::string nom)
    {
        name = nom;
        value = 0;
        isConst = false;
    }
    mpf_class base::get(){
        return value;
    }
    void base::set(mpf_class v){
        value = v;
    }

    bool testdigite(const char * num){
        bool isNum = true;
        size_t l = strlen(num), i = 0;
        while( i < l){
            if(! isdigit(num[i])){
                isNum = false;
                break;
            }
            i++;
        }
        return isNum;
    }

    int NumbersGestion::new_number(std::string id, std::string value){
            return new_number(id.c_str(),value.c_str());
        };  
        int  NumbersGestion::new_number(const char * id, const char * value){
            
            if(!number::testdigite(value)){
                return -1;
            };
            mpf_class n(value);
            
            std::string name(id);
            number::base b(name, n);
            num.push_back(b);
            return 1;
        };
        base NumbersGestion::get(const char * n){
            std::vector <base>::iterator il;
            
            for(il = num.begin(); il != num.end(); il++){
                
                if( (*il).cmp(n) == EQUAL){
                    return *il;
                };
            };
            return null;
        };
        base NumbersGestion::set(const char * n, mpf_class v){
            std::vector <base>::iterator il;
            for(il = num.begin(); il != num.end(); il++){
                if( (*il).cmp(n) == EQUAL){
                    (*il).set(v);
                    return (*il);
                }
            }
            return null;
        }
        base NumbersGestion::set(const char * n, const char * val){
          mpf_class v(val);
          return this->set(n,v);
        }
        int NumbersGestion::del(const char * n){
            std::vector <base>::iterator il;
            for(il = num.begin(); il != num.end(); il++){
                if( (*il).cmp(n) == EQUAL){
                    num.erase(il);
                    return 0;
                }
            }
            return 0;
        }
        NumbersGestion:: NumbersGestion(/* args */)
        {
        }
        std::string base::c_str(){
            mp_exp_t e = 10;
           
           return value.get_str(e);
        }
        
        
}


