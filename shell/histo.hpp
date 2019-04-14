#ifndef HISTO_H_INCLUDES
#define HISTO_H_INCLUDES
#include <iostream>
#include <string>
namespace listes{
    
    template <class T> class base{
    private:
        T value;
        base<T>  * prev, *nex;
    public:
        int previous( base<T> *);
        int next( base<T> *);
        int set(T);
        T get();
        base<T>* get_prev();
        base<T>* get_next();
        base();
        base(T);
        ~base();
    };
    
    
    /* template <class T> class histo{
    private:
        base<T> * first;
        base<T> * last;
        size_t maxLength;
        size_t length; 
    public:
        histo();
       
        bool empty();
        void push(T);
        T pop(void);
    };*/
    class histo{
    private:
        base<std::string> * first;
        base<std::string> * last;
        size_t maxLength;
        size_t length; 
    public:
        histo(/* args */);
       
        bool empty();
        void push(std::string);
        std::string pop(void);
    };
    
        
}

#endif