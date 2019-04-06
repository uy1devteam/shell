

#include "commandes.hpp"

   

    
    
    
    commandes::commandes(const char * enter){
        char * line = strdup(enter), *debut =line;
        size_t i(0),k=0,max=strlen(line);
        std::string  cmd;
        
        bool neutralise_some = false;
        bool neutralise_all = false;
        bool super_neutralise = false;  
                  
        while(i < max){
           
            if(line[i] == ';'){
                if(!neutralise_all){
                    if(!neutralise_some){
                        if(super_neutralise){
                            super_neutralise = false;
                        }
                        else
                        {   

save_commande:             
                            int j = cmd.length() - 1;
                            while(!cmd.empty() && j >= 0){
                                if(cmd[j] == ' ')
                                {
                                    cmd.erase(j);
                                }
                                
                                else
                                {
                                    break;
                                }
                                j--;
                            }
                            
                            if(cmd.empty())goto pass;
                            commande t(cmd.c_str());
                            liste.push_back(t);
                            cmd.clear();
                            k++;                          
                            
                            
                           
                            goto pass;
                        }
                    }
                }
            }

           
          
           
            cmd.push_back(line[i]);
            if(line[i] == '\"'){

                if(neutralise_all){
append_cote:        
                    
                    super_neutralise = false;
                    goto pass;
                }

                if(neutralise_some){
                  if(super_neutralise){
                      goto append_cote;
                  } 
                  neutralise_some = false;
                  goto pass;  
                }else
                {
                    if(super_neutralise){
                      goto append_cote;
                    }
                    neutralise_all = false;
                    super_neutralise = false;
                    neutralise_some = true;
                    goto pass;
                }
                
            }

            if(line [i] == '\''){
                if(neutralise_some){
append_simple_cote: 
                    
                    super_neutralise = false;
                    goto pass;
                }

                if(neutralise_all){
                    neutralise_all = false;
                    goto pass;
                }
                else
                {
                    if(super_neutralise){
                       goto append_simple_cote;     
                    }
                    neutralise_all = true;
                    neutralise_some = false;
                    super_neutralise = false;
                    goto pass;
                }
                
            }

            if(line[i]=='\\'){
                if(neutralise_all){
                    
                    goto pass;
                }
                if(neutralise_some){
                    if(super_neutralise){
                        
                        super_neutralise = false;
                        goto pass;
                    }
                    super_neutralise = true;
                    goto pass;
                }

                if(super_neutralise){
                    
                    super_neutralise = false;
                    goto pass;
                }
                super_neutralise = true;
                goto pass;
            }
            
pass:       i++; 
        }
     
    if(!cmd.empty())goto save_commande;
    
    free(debut);  
}
    commandes::commandes(unsigned int argc,commande* argv){

        unsigned int i = 0;
        while(i < argc){
             liste.push_back(argv[i]);
        }
            
    };
    
    void commandes::affiche(void){
        vector<commande>::iterator il ;

        for (il = liste.begin() ; il != liste.end() ; il++)
        {
            il->affiche();
        }
        
    }
    int commandes::append( commande  arg){
        liste.push_back(arg);
        return 0;
    };
    int commandes::erase(unsigned int  position){
        
        liste.erase(liste.begin()+position);
        return 0;
    };
    void commandes::clear(void){
        liste.clear();
    };
    void commandes::reverse(void){
        vector<commande>::iterator il ;
        vector<commande> _liste;
        for (il = liste.begin() ; il != liste.end() ; il++)
        {
            _liste.push_back(*il);
        }
        liste.clear();
        for (il = _liste.begin() ; il != _liste.end() ; il++)
        {
            liste.push_back(*il);
        }
    }
    int commandes::execute_all(){
            
        vector<commande>::iterator il ;
        int status = 1;
        for (il = liste.begin() ; il != liste.end() ; il++)
        {
            status =  il->execute();
            if(!status)break;
        }
        
        return status;
    }
    int commandes::replace(unsigned int st, unsigned int end, commande arg){
        liste.insert(liste.begin(),st-end+1,arg);
        return 0;
    };
    commandes operator+ (commandes l1, commandes l2){
        
        vector<commande>::iterator il ;
        for (il = l2.liste.begin() ; il != l2.liste.end() ; il++)
        {
            l1.liste.push_back(*il);
        }
        return l1;
    }

    commandes& commandes::operator= (const commandes & l1){
        if (this != &l1){
            liste = l1.liste;
        }
        return *this;
    }
    commandes operator+= (commandes l1, commandes l2){
        return l1 = l1 + l2;
    }
    

    

    