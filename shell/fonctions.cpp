
#include "header.hpp"
#include "commandes.hpp"

    using namespace std;
    
    extern    char *builtin_str; 

    extern    char *builtinproc_str; ;

        /*
    Builtin function implementations.
    */
    /**
     @brief Bultin command: echo history of comande line.
    @param args List of args.  args[0] is "cd".  
    */
    int history(char **args)
    {

        
        if (args[1] == NULL) {
            
            HIST_ENTRY** first  = history_list();
            int i = (HISTORY_MAX_LENGTH < history_length)?  history_length - HISTORY_MAX_LENGTH: 0 ;
            
            do{
                cout << i << "   " <<first[i]->line << endl;
                i++;
            }while( i < history_length );     
                        
        }
        else
        {
            if(args[2] ==   NULL){

            }else{
                cerr << "msh: to many arguments to \"history\"" << endl;
                return 1;
            }
            long p = unsigned_convertion(args[1]);
            if(p < 0){
                cerr << "msh: need numerique argument to \"history\"" << endl;
            }else{
                HIST_ENTRY** first  = history_list();
                int i = (p < history_length)?  history_length - p: 0 ;
                
                do{
                    cout << i << "   " <<first[i]->line << endl;
                    i++;
                }while( i < history_length );

            }

        }
        return 1;    
    }
    /**
     @brief Bultin command: change directory.
    @param args List of args.  args[0] is "cd".  args[1] is the directory.
    @return Always returns 1, to continue executing.
    */
    int cd(char **args)
    {
    if (args[1] == NULL) {
        fprintf(stderr, "msh: expected argument to \"cd\"\n");
    } else {
        if (chdir(args[1]) != 0) {
        perror("msh");
        }
        
    }
    return 1;
    }
    /**
     @brief Bultin command: ls add color and regex list.
    @param args List of args.  args[0] is "ls".  
    @return Always returns -1 on error.
    */
    int ls(char **args){
        
        vector <char *> arg_list_tmp;
        vector <char *>::iterator il;
        int position = 0;
        
        while (args[position]!=NULL)
        {
            char *tmp=strstr(args[position],"*");
            if (tmp!=NULL)
            {
                glob_t g;
                int retour_glob=glob(tmp,0,NULL,&g);
                if (retour_glob==0)
                {
                    int boucle;
                    for (boucle=0;boucle<g.gl_pathc;++boucle)
                    {
                        arg_list_tmp.push_back(strdup(g.gl_pathv[boucle]));
                    }
                    free(args[position]);
                }
            else
            {
                arg_list_tmp.push_back(args[position]);
            }
            globfree(&g);
        }
        else
        {
            arg_list_tmp.push_back(args[position]);
            
        }
            ++position;
        }
        position = 0;
        for(il = arg_list_tmp.begin(); il < arg_list_tmp.end();il++){
            args[position ++] = *il;
        }
        
        args[position++]= (char *) "--color";
        args[position] = NULL;
        return execvp(args[0],args);
    }
    /**
     @brief Bultin command: grep add color and regex search.
    @param args List of args.  args[0] is "grep".  
    @return Always returns -1 on error.
    */
    int grep(char **args){
        int position = 0;
        while(args[position] != NULL){
            position++;
        }
        args[position ++] = (char *) "--color";
        args[position ++] = (char *) "-E";
        //args[position ++] = (char *) "-L";
        args[position ] = NULL;
        return execvp(args[0],args);
    }
    /**
     @brief Builtin command: print help.
    @param args List of args.  Not examined.
    @return Always returns 1, to continue executing.
    */
    int help(char **args)
    {
        int i;
    
        printf("Type program names and arguments, and hit enter.\n");
        printf("The following are built in:\n");

        for (i = 0; i < num_builtins(); i++) {
            printf("  %s\n", builtin_str[i]);
        }

        printf("Use the man command for information on other programs.\n");
        return 1;
    }

    /**
     @brief Builtin command: exit.
    @param args List of args.  Not examined.
    @return Always returns 0, to terminate execution.
    */
    int _exit(char **args)
    {
    return 0;
    }
    long convertion(char * chaine)
    {
        unsigned i = 0;
        long nombre = 0;
        short signe = POSITIF;
        if(chaine[0] == TIRET)
        {
            signe = NEGATIF;
            i++;
        }
        while(chaine[i] != '\0'){
            if( chaine[i] > 47 && chaine[i] <  59){
                
                nombre =  nombre * 10*i +  chaine[i] - 48;
                
            }else{
                cerr <<" msh : " << chaine << " is not a number" << endl;
                exit(EXIT_FAILURE);
            }
            i++;
        }
        return nombre * signe;
    }


    long unsigned_convertion(char * chaine)
    {
        unsigned i = 0;
        long nombre = 0;
        
        while(chaine[i] != '\0'){
            if( chaine[i] > 47 && chaine[i] <  59){
                
                nombre =  nombre * 10*i +  chaine[i] - 48;
                
            }else{
                return -1;
            }
            i++;
        }
        return nombre ;
    }

    /*
        give the current directory name and username wthi some design
    */

    string directory(){
        string  path =  get_current_dir_name();
        string username = getenv("USER");
        string base = cat_many(2,"/home/",username.c_str());        
        
        if(path.compare(base) == 0  ){
            path.replace(0,base.length(),"~/");
        }else{
            if(path.compare(base) > 0){
                path.replace(0,base.length() + 1,"~/");
            }
        }
        return cat_many(8,"\e[032;1m",username.c_str(),"\e[33;0m",":","\033[34;1m",path.c_str(),"\033[47;0m","$ ");
        
    }
          
    int num_builtins() {
    return sizeof(builtin_str) / sizeof(char *);
    }
    int num_builtinprocs() {
        return sizeof(builtinproc_str) / sizeof(char *);
    }
    
    /*
    @brief cat_many cat str argument in to one string 
    @params nbCh number of char * passed 
    @return a string resulting of concatanation off all char * parsed
    */
    string cat_many(int nbCh, ...){
        va_list liste ;
        va_start (liste , nbCh) ;
        int i;
        string reslut;
        for (i=1 ; i<=nbCh ; i++)
        { 
            string tampon = va_arg (liste, char *) ;
            reslut += tampon;
            
        }
        va_end(liste);
        
        return reslut;
    }
    /*
    @brief split_commande split line to get commande separe by ;
    @params line the char * to split 
    @return all commande on line
    */
    char **split_commande(char* line){
        int bufsize = TOK_BUFSIZE, position = 0;
        char **tokens = (char **)calloc(bufsize , sizeof(char*));
        char *token, **tokens_backup;

        if (!tokens) {
            cerr << "msh: allocation error" << endl;
            exit(EXIT_FAILURE);
        }

        token = strtok(line, ";");
        while (token != NULL) {
            tokens[position] = token;
            position++;

            if (position >= bufsize) {
                bufsize += TOK_BUFSIZE;
                tokens_backup = tokens;
                tokens = (char **)realloc(tokens, bufsize * sizeof(char*));
                if (!tokens) {
                    free(tokens_backup);
                    cerr << "msh: allocation error" << endl;
                    exit(EXIT_FAILURE);
                }
            }

            token = strtok(NULL, TOK_DELIM);
        }
        tokens[position] = NULL;
        return tokens;
    }
    
    /**
     * @brief Read a line of input from stdin.
     * @return The line from stdin.
    */
    char *read_line(void)
    {
        
        char *line = NULL;
        
        line =  readline(directory().c_str());
        if (*line) add_history(line);
            append_history(1,HISTORY_NAME);
        return line;
    }
    /**
     * @brief copie the item of an array of char in to new array of char
     * @params line the array to copie item
     * @return the pointer on new array
    */
    char * copier(char * word){
        size_t length = strlen(word),i=0;
        char * copie = (char *)calloc((length+1),sizeof(char ));
        if (!copie) {
            fprintf(stderr,"msh: allocation error\n");
            exit(EXIT_FAILURE);
        }
        copie[length] = '\0';
        
        while(i < length){
            
            copie[i] = word[i];
            i++;
        }
        return copie;
    }
    /**
     @brief Loop getting input and executing it.
    */
    void loop(void)
    {
    char *line;
  
    int status;

    using_history();
    if( read_history(HISTORY_NAME)){
        write_history(HISTORY_NAME);
    };
    stifle_history(HISTORY_MAX_LENGTH);
 
    do {
        line = read_line();
        
        
        
        
       
        commandes cmds(line);
         cmds.affiche();
        status = cmds.execute_all();    
        cmds.affiche();    

        free(line);
    
    } while (status);

    }

    bool is_separator(char c){

        switch (c)
        {
            case '\n':
            case ' ':
            case '\t':
            case '\a':
            case '\r':
            case '(':
            case ')':
            case '>':
            case '<':
            case ';':      
                return true;        
            break;
            default:
                return false;
                break;
        }
    }