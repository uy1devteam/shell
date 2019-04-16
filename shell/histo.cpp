#include "histo.hpp"


namespace listes{
    template <class T> int base<T>::set( T val){
        value = val;
        return 1;
    }
    template <class T> int base<T>::next( base<T>* n){
        nex = n;
        return 1;
    }
    template <class T> int base<T>::previous( base<T>* p){
        prev = p;
        return 1;
    }
    template <class T> T base<T>::get(){
        return value;
    }
    template <class T> base<T> * base<T>::get_next(){
        return nex;
    }
    template <class T> base<T> * base<T>::get_prev(){
        return prev;
    }

    template <class T> base<T>::base()
    {
        prev = nex = NULL;
    }
    template <class T> base<T>::base(T val)
    {
        prev = nex = NULL;
        value = val;
    }
    template <class T> base<T>::~base()
    {
    }

     bool histo::empty(){
        return length == 0;
    }

    void histo::push(std::string a){
        
        last->next(new base<std::string>);
        last->get_next()->set(a);
        last->get_next()->previous(last);
        last = last->get_next();
        length ++;
        if(maxLength !=0){
            if(length > maxLength){
                length --;
                first = first->get_next();
            }
        }
        
    }
     std::string histo::pop(){
        std::string current;
        if(length > 0){
            current = last->get();
            length --;
            last = last->get_prev();
            //free next
            delete last->get_next();
            last->next(NULL);
        }

        return current;
    }
    std::string histo::pop(long p){
        std::string current;
        while(p-->0){
            if(length > 0){
                current = last->get();
                length --;
                last = last->get_prev();
                //free next
                delete last->get_next();
                last->next(NULL);
            }
            else
            {
                break;
            }
            
        };
        
        return current;
    }
     histo::histo()
    {
        first =  new base<std::string>;
        last = first;
        length = 0;
        maxLength = 0;
    }
    
    

    //string
    
}