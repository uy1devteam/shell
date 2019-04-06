#include "commande.hpp"

    using namespace std;

    /* The array below will hold the arguments: args[0] is the command. */
    
    char *builtin_str[] = {
            "cd",
            "ls",
            "grep",
            "help",
            "exit",
            "history"
            };

    char *builtinproc_str[] = {"cd"};
 
    #define READ  0
    #define WRITE 1

    
      /*
    List of builtin commands, followed by their corresponding functions.
    */


        int (*builtin_func[]) (char **) = {
            &cd,
            &ls,
            &grep,
            &help,
            &_exit,
            &history
        };
        int (*builtinproc_func[]) (char **) = {
            &cd,
        };
    commande::commande(){
        length = 0;
        hasPipe = false;
        hasError = false;
    };
    commande::commande(unsigned int argc,char** argv){
        hasPipe = false;
        hasError = false;
        listePipe = new char*[argc];   
        for(length = 0;  length < argc; length ++){
            listePipe[length] = argv [length];
        }
        this->calcule_args( );
    };
    void commande::affiche(void){
        unsigned int i = 0;
        while(i < length){
            cout << args[i][0] << "  " << endl;
            i++;
        }
        
    }
    int commande::copy(unsigned int argc, const char ** argv){
        char* tampon [length];
        unsigned int i = 0;
        for( i = 0; i < length; i++){
            tampon[i] = listePipe[i];
        }
        length += argc;
        delete args;
        listePipe =  new char* [length]; 
        for( i = 0; i < length - argc; i++){
            listePipe[i] = tampon[i]  ;
        }
        for(i = 0; i < length; i++){
            listePipe[i] = (char *)argv[i];
        }
        this->calcule_args( );
        return 0;
    };
    int commande::append(const char*  arg){
        char * tampon [length];
        unsigned int i = 0;
        for( i = 0; i < length; i++){
            tampon[i] = listePipe[i];
        }
        length ++;
        
        listePipe =  new char * [length]; 
        for( i = 0; i < length - 1; i++){
            listePipe[i] = tampon[i]  ;
        }
        
        listePipe[i] = (char *)arg;
        this->calcule_args( );
        return 0;
    };
    int commande::erase(unsigned int  position){
        char * tampon [length - 1];
        unsigned int i = 0;
        if( position >=length){
            return -1;
        }
        while(  i < position ){
            tampon[i] = listePipe[i];
            i++;
        }
        i++;
        while(  i < length ){
            tampon[i - 1] = listePipe[i - 1];
        }
        length --;
        
        listePipe =  new char * [length]; 
        for( i = 0; i < length; i++){
            listePipe[i] = tampon[i]  ;
        }
        this->calcule_args( );
        return 0;
    };
    void commande::clear(void){
        args = NULL;
        listePipe = NULL;
        hasPipe = false;
        length = 0;
    };
    void commande::reverse(void){
        char * tampon [length - 1];
        unsigned int i = 0;
        while(  i < length ){
            tampon[ i ] = listePipe[i];
        }
        delete args;
        listePipe =  new char * [length];
        for( i = 0; i < length; i++){
            listePipe[length - i -1] = tampon[i]  ;
        }
        this->calcule_args( );
    }
    int commande::replace(unsigned int st, unsigned int end,const char * arg){
        if(st > end){
            return -1;
        }
        if( end >=length){
            return -1;
        }
        char * tampon [ length -(end -st + 1) ];
        unsigned int i = 0;
       
        while(  i < st ){
            tampon[i] = listePipe[i];
            i++;
        }
        i = end + 1;
        while(  i < length ){
            tampon[i] = listePipe[i];
            i++;
        }
        
        listePipe =  new char * [length -st -end + 2];
        i = 0;
        while(  i < st ){
            listePipe[i] = tampon[i];
            i++;
        }
        listePipe[i] = (char *)arg;
        i++;
        while(  i < length ){
            listePipe[i] = tampon[i];
            i++;
        }
        this->calcule_args( );
        return 0;
    };
    commande operator+ (commande l1, commande l2){
        char * tampon [l1.length];
        unsigned int i = 0;
        for( i = 0; i < l1.length; i++){
            tampon[i] = l1.listePipe[i];
        }
        l1.length += l2.length;
        delete l1.args,delete l1.listePipe;
        l1.listePipe =  new char * [l1.length]; 
        for( i = 0; i < l1.length - l2.length; i++){
            l1.listePipe[i] = tampon[i]  ;
        }
        for(i = 0; i < l1.length; i++){
            l1.listePipe[i] = l2.listePipe[i];
        }
        l1.calcule_args();
        return l1;
    }

    commande& commande::operator= (const commande & l1){
        if (this != &l1){
            delete listePipe;
            listePipe =  new char * [l1.length];
            length = l1.length;
            unsigned int i = 0;
            for( i = 0; i < l1.length; i++){
                listePipe[i] = l1.listePipe[i];
            }
            this->calcule_args( );
        }

        
        return *this;
    }
    commande operator+= (commande l1, commande l2){
        return l1 = l1 + l2;
    }



    /**
     @brief Launch a program and wait for it to terminate.
    @param args Null terminated list of arguments (including program).
    @return Always returns 1, to continue execution.
    */
    int  commande::launch()
    {
    pid_t pid;
    int status;

    pid = fork();
    if (pid == 0) {
        // Child process
        if(!out_put.empty()){
            
            if( (long)freopen(out_put.c_str(),out_put_mod.c_str(),stdout) == -1){
                _exit(EXIT_FAILURE);
            }
            out_put.clear();
        }
        if(!in_put.empty()){
            if(in_put_mod == FILLE){
                if( (long)freopen(in_put.c_str(),"r",stdin) == -1){
                    _exit(EXIT_FAILURE);
                }else{
                    //interactive saisie
                }    
                in_put.clear();
            }
            
        }
        for (int j = 0; j < num_builtins(); j++) {
            if (strcmp(args[0][0], (const char *)builtin_str[j]) == 0) {

                int status =    (*builtin_func[j])(args[0]);
                if(status == -1){
                    perror("msh");
                }
                _exit(status);                   
            }
        }                
        if (execvp(args[0][0], args[0]) == -1) {
        perror("msh");
        _exit(EXIT_FAILURE);
        }
        
        _exit(EXIT_SUCCESS);
    } else if (pid < 0) {
        // Error forking
        perror("msh");
    } else {
        // Parent process
        do {
        waitpid(pid, &status, WUNTRACED);
        } while (!WIFEXITED(status) && !WIFSIGNALED(status));
        //recupe status of previous execution here
    }

    return 1;
    }
    bool commande::has_liste_Pipe(){
        if (listePipe[0] == NULL) {
            // An empty command was entered.
            return false;
        }
        return true;
    }
    bool commande::has_error(){
       if(hasError){
            //repport the error
            cout << erro_message.c_str(); 
            return true;
        }
        return false;
    }
    bool commande::execute_pipe(){
        
         if(hasPipe){
            
            input = 0;
            bool first = true;
            size_t    i = 0;
            
            while (i < (length -1)) {
                

                input = this->command(i, first, false);
    
                first = false;
                i++;
            }
            input = command(i, first, true);
            cleanup(length);
            return true;
        }
        return false;
    }
    bool commande::scan_redirection(){
        size_t k = 0;
            
            while(args[0][k] != NULL)
            {
                
                if(strcmp(args[0][k],"<") == EQUAL || strcmp(args[0][k],"<<") == EQUAL)
                {
                    
                    if(!args[0][k+1])
                    {
                        hasError = true;
                        erro_message.append( "msh : error on ");
                        erro_message.append( args[0][k] );                    
                        erro_message.push_back('\n');
                        return false;
    
                    }else
                    {
                        in_put.clear();
                        in_put.append(args[0][k+1]);
                        if(strcmp(args[0][k],"<") == EQUAL)
                        {
                            in_put_mod = FILLE;
                        }else
                        {
                            in_put_mod = SHELL;
                        } 
                        cfree(args[0][k + 1]);
                        while(args[0][k+2] != NULL)
                        {
                            args[0][k] = args[0][k+2];
                            k++;
                        }
                    
                        
                    }
                    
                    
                    
                
                    //free(args[0][k]);
                    args[0][k] = NULL;
                    break;
                }
                k++;
            }
            k = 0;
            
            out_put.clear();
            while(args[0][k])
            {
                
                if(strcmp(args[0][k],">") == EQUAL || strcmp(args[0][k],">>") == EQUAL)
                {
                    
                    if(!args[0][k+1]){
                                //repport the error
                    
                        if(!in_put.empty()){
                            out_put = in_put;
                            args[0][k]  = NULL;
                            break;
                        }
                        else{
                            hasError = true;
                            erro_message.append( "msh : error on ");
                            erro_message.append( args[0][k] );                    
                            erro_message.push_back('\n');
                            return false;

                        }
                            
                    }
                    
                    

                    out_put.append(args[0][k+1]);
                    if(strcmp(args[0][k],">") == EQUAL){
                        out_put_mod.append(CREATE);
                    }else{
                        out_put_mod.append(APPEND);
                    }
                
                    //free(args[0][k]);
                    cfree(args[0][k + 1]);
                    while(args[0][k+2] != NULL){
                        args[0][k] = args[0][k+2];
                        k++;
                    }
                
                    args[0][k] = NULL;
                    break;
                }
                k++;
            }
            k=0;
            if(out_put.empty())
            {
                while(args[0][k]){
                    
                    if(strcmp(args[0][k],">") == EQUAL || strcmp(args[0][k],">>") == EQUAL){
                    
                        if(!args[0][k+1]){
                                    //repport the error
                            hasError = true;
                            erro_message.append( "msh : error on ");
                            erro_message.append( args[0][k] );                    
                            erro_message.push_back('\n');
                            return false;
       
                        }
                        
                        out_put.clear();
                        out_put.append(args[0][k+1]);
                        if(strcmp(args[0][k],">") == EQUAL){
                            out_put_mod.append(CREATE);
                        }else{

                            out_put_mod.append(APPEND);
                        }
                    
                        //free(args[0][k]);
                        cfree(args[0][k + 1]);
                        while(args[0][k+2] != NULL){
                            args[0][k] = args[0][k+2];
                            k++;
                        }
                    
                        args[0][k] = NULL;
                        break;
                    }
                    k++;
                }
            }
        return true;
    }
    /**
     @brief Execute shell built-in or launch program.
    @param args Null terminated list of arguments.
    @return 1 if the shell should continue running, 0 if it should terminate
    */
    int commande::execute()
    {
            
            if( has_error()) return 1;
            
            if(!has_liste_Pipe()) return 1;
            cout << args[0][0] <<endl;    
            if( execute_pipe()) return 1;
            
            scan_redirection();
            
            if( has_error()) return 1;
            for (int j = 0; j < num_builtinprocs(); j++) 
            {
                if (strcmp(args[0][0], (const char *)builtinproc_str[j]) == 0) 
                {

                    (*builtinproc_func[j])(args[0]);
                return  1;                       
                }
            }
            
            return launch();
              
    }
    

    

  

    /**
     @brief Split a line into argss (very naively).
    @param line The line.
    
    */
    
    int commande::calcule_args()
    {
        int bufsize = 512, position = 0;
        args = (char ***)calloc(bufsize , sizeof(char**));
        char  ***args_backup;
        size_t i = 0;
        
        if (!args) {
            cerr << "msh: allocation error" << endl;
            exit(EXIT_FAILURE);
        }

        while(i < length){
            args[i] = (char **)calloc(bufsize , sizeof(char*));
            position = 0;
            
            size_t j(0), max = strlen(listePipe[i]);
            std::string cmd,b("\\"),c("\""),sc("'");

            bool neutralise_some = false;
            bool neutralise_all = false;
            bool super_neutralise = false;
            bool in_redirection = false;
            bool in_console_redirection = false;
            bool out_write_redirection = false;
            bool out_append_redirection = false;
            
            bool etat1 = false;//argument
            bool etat2 = true; //separator
            
            while (j < max) {
                if( is_separator(listePipe[i][j])){
                    //analyse separator

                   if(listePipe[i][j] == ' '){
                       if(neutralise_all || neutralise_some){
                            //append
                            cmd.push_back(' ');
                        }
                        else
                        {
                         super_neutralise = false;   
                        }
                   }
                   if(listePipe[i][j] == '<'){
                        if(neutralise_all || neutralise_some){
                            //append
                            cmd.push_back('<');
                        }
                        else
                        {
                            if(super_neutralise){
                                //append
                                cmd.push_back('<');
                                super_neutralise =  false;
                                
                            }
                            else
                            {
                                if(in_redirection){
                                    if(in_console_redirection){
                                        hasError = true;
                                        erro_message.append("msh: syntaxe error on  '<'");
                                        return -1;
                                        //exit(EXIT_FAILURE);
                                    }
                                    in_console_redirection = true;
                                    in_redirection = false;
                                    in_redirection = true;
                                    etat1 = false;
                                    etat2 = true;
                                    //append argument
                                    
                                    if(!cmd.empty()){             
                                        args[i][position] = strdup(cmd.c_str());
                                        position++;
                                        cmd.clear();
                                        cout << "msh : syntax error\n";
                                        return 1;
                                    }
                                    if(listePipe[i][j-1] != '<'){
                                        cout << "msh : syntax error\n";
                                        return 1;
                                    }
                                    if (position >= bufsize) {
                                    bufsize += TOK_BUFSIZE;
                                    args_backup = args;
                                    args = (char ***)realloc(args, bufsize * sizeof(char***));
                                    if (!args) {
                                        cfree(args_backup);
                                        cerr << "msh: allocation error" << endl;
                                        exit(EXIT_FAILURE);
                                                }
                                    }
                                    args[i][position -1] = strdup("<<");
                                    position++;
                                    goto pass;
                                }
                                else{
                                   
                                    in_redirection = true;
                                    if(cmd.empty()){
                                        args[i][position] = strdup("<");           
                                        args[i][position][0] = '<';
                                        args[i][position][1] = '\0'; 
                                        position ++;
                                        goto pass;
                                    }
                                    etat1 = false;
                                    etat2 = true;
                                    //append argument
                                                 
                                    args[i][position] = strdup(cmd.c_str());
                                    position++;
                                    cmd.clear();
                                    if (position >= bufsize) {
                                    bufsize += TOK_BUFSIZE;
                                    args_backup = args;
                                    args = (char ***)realloc(args, bufsize * sizeof(char***));
                                    if (!args) {
                                        cfree(args_backup);
                                        cerr << "msh: allocation error" << endl;
                                        exit(EXIT_FAILURE);
                                    }
                                    }
                                    
                                    args[i][position] = strdup("<<"); 
                                    position ++;
                                    goto pass;
                                      
                                }
                                
                            }
                        }
                        
                    } 
                    if(listePipe[i][j] == '>'){
                        if(neutralise_all || neutralise_some){
                            //append
                            cmd.push_back('>');
                        }
                        else
                        {
                            if(super_neutralise){
                                //append
                                cmd.push_back('>');
                                super_neutralise =  false;
                                
                            }
                            else
                            {
                                if(out_write_redirection){
                                    if(out_append_redirection){
                                        hasError = true;
                                        erro_message.append("msh: syntaxe error on  '>'");
                                        return -1;
                                        //exit(EXIT_FAILURE);
                                    }
                                    
                                    out_append_redirection = true;
                                    out_write_redirection = false;
                                    out_write_redirection = true;
                                    etat1 = false;
                                    etat2 = true;
                                    //append argument
                                    
                                    
                                    if(!cmd.empty()){
                                        args[i][position ] = strdup(cmd.c_str());
                                        position++;
                                        cmd.clear();
                                        cout << "msh : syntaxe error" << endl;
                                        return 1;
                                    }             
                                    
                                    if(listePipe[i][j-1] != '>'){
                                        cout << "msh : syntaxe error" << endl;
                                        return 1;
                                    }
                                    
                                    if (position >= bufsize) {
                                    bufsize += TOK_BUFSIZE;
                                    args_backup = args;
                                    args = (char ***)realloc(args, bufsize * sizeof(char***));
                                    if (!args) {
                                        cfree(args_backup);
                                        cerr << "msh: allocation error" << endl;
                                        exit(EXIT_FAILURE);
                                                }
                                    }
                                    args[i][position -1] = strdup(">>");
                                    //position;
                                    goto pass;
                                }
                                else{
                                   
                                    out_write_redirection = true;
                                    if(cmd.empty()){
                                        args[i][position] = strdup(">");                                         
                                        position ++;
                                        goto pass;
                                    }
                                    etat1 = false;
                                    etat2 = true;
                                    //append argument
                                                 
                                    args[i][position] = strdup(cmd.c_str());
                                    position++;
                                    cmd.clear();
                                    if (position >= bufsize) {
                                    bufsize += TOK_BUFSIZE;
                                    args_backup = args;
                                    args = (char ***)realloc(args, bufsize * sizeof(char***));
                                    if (!args) {
                                        cfree(args_backup);
                                        cerr << "msh: allocation error" << endl;
                                        exit(EXIT_FAILURE);
                                    }
                                    }
                                    args[i][position] = strdup(">"); 
                                    position ++;
                                    goto pass;
                                      
                                }
                                
                            }
                        }
                        
                    }
                    if(listePipe[i][j] == '\"'){
                        if(neutralise_all){
        append_cote:        cmd+= c;
                            
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

                    if(listePipe [i][j] == '\''){
                        if(neutralise_some){
        append_simple_cote: cmd+=sc;
                            
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

                    if(listePipe[i][j]=='\\'){
                        if(neutralise_all){
                            cmd+=b;
                            goto pass;
                        }
                        if(neutralise_some){
                            if(super_neutralise){
                                cmd+=b;
                                super_neutralise = false;
                                goto pass;
                            }
                            super_neutralise = true;
                            goto pass;
                        }

                        if(super_neutralise){
                            cmd.push_back('\\');
                            super_neutralise = false;
                            goto pass;
                        }
                        super_neutralise = true;
                        goto pass;
                    }


                    if(etat1){
                        etat1 = false;
                        etat2 = true;
                        //append argument
                                     
                        args[i][position] = strdup(cmd.c_str());
                        position++;
                        cmd.clear();
                        if (position >= bufsize) {
                        bufsize += TOK_BUFSIZE;
                        args_backup = args;
                        args = (char ***)realloc(args, bufsize * sizeof(char***));
                        if (!args) {
                            cfree(args_backup);
                            cerr << "msh: allocation error" << endl;
                            exit(EXIT_FAILURE);
                        }
                    }

                
                    }
                    else
                    {

                    }
                }
                else
                {
                    if(etat2){
                        etat2 = false;
                        etat1 = true;
                    }
                    else
                    {
                        
                    }
                    cmd.push_back(listePipe[i][j]);
                }

               
                    
        pass:       j++;     
                

                
            }
     
        if(cmd.length()!=0){
             
            args[i][position] = strdup(cmd.c_str());
                        position++;
                        cmd.clear();
                        if (position >= bufsize) {
                        bufsize += TOK_BUFSIZE;
                        args_backup = args;
                        args = (char ***)realloc(args, bufsize * sizeof(char***));
                        if (!args) {
                            cfree(args_backup);
                            cerr << "msh: allocation error" << endl;
                            exit(EXIT_FAILURE);
                        }
                    }
        }
        i++;    
    }
    
            
          
    return 1;
    }


/*
 * Handle commands separatly
 * input: return value from previous command (useful for pipe file descriptor)
 * first: 1 if first command in pipe-sequence (no input from previous pipe)
 * last: 1 if last command in pipe-sequence (no input from previous pipe)
 *
 * EXAMPLE: If you type "ls | grep shell | wc" in your shell:
 *    fd1 = command(0, 1, 0), with args[0] = "ls"
 *    fd2 = command(fd1, 0, 0), with args[0] = "grep" and args[1] = "shell"
 *    fd3 = command(fd2, 0, 1), with args[0] = "wc"
 *
 * So if 'command' returns a file descriptor, the next 'command' has this
 * descriptor as its 'input'.
 */
 int commande::command(int cmd , bool first, bool last)
{
	int pipettes[2];
 
	/* Invoke pipe */
	pipe( pipettes );	
	pid = fork();
 
	/*
	 SCHEME:
	 	STDIN --> O --> O --> O --> STDOUT
	*/
 
	if (pid == 0) {
		if (first && !last && input == 0) {
			// First command
			dup2( pipettes[WRITE], STDOUT_FILENO );
		} else if (!first && !last && input != 0) {
			// Middle command
			dup2(input, STDIN_FILENO);
			dup2(pipettes[WRITE], STDOUT_FILENO);
		} else {
			// Last command
			dup2( input, STDIN_FILENO );
		}
        
        
        for (int j = 0; j < num_builtins(); j++) {
            if (strcmp(args[cmd][0], (const char *)builtin_str[j]) == 0) {
                (*builtin_func[j])(args[cmd]);
                exit(EXIT_SUCCESS);
                goto ours_commandes;
            }
        } 
		if (execvp( args[cmd][0], args[cmd]) == -1){
            perror("msh");
			exit(EXIT_FAILURE); // If child fails
        }
	}
ours_commandes: 
	if (input != 0) 
		close(input);
 
	// Nothing more needs to be written
	close(pipettes[WRITE]);
 
	// If it's the last command, nothing more needs to be read
	if (last )
		close(pipettes[READ]);
 
	return pipettes[READ];
}
 void commande::cleanup(int n)
{
	int i;
	for (i = 0; i < n; ++i) 
		wait(NULL); 
}
commande::commande(const char * l){
        size_t i(0),j(0), max = strlen(l);
        listePipe = (char **)malloc(512 * sizeof(char**));
        char * line = strdup(l),* f = line;
        hasPipe = false;
        hasError = false;
        bool neutralise_some = false;
        bool neutralise_all = false;
        bool super_neutralise = false;  
        length = 0;
                  
        while(i < max){
            
            if(line[i] == '|'){
                if(!neutralise_all){
                    if(!neutralise_some){
                        if(super_neutralise){
                            super_neutralise = false;
                        }
                        else
                        {   

save_commande:              
                            line[i] ='\0';
                            listePipe[length] = strdup(line);
                            line = line + i + 1;
                            length++;                          
                            
                            j=0;
                            goto pass;
                        }
                    }
                }
            }

           
               
            j++;
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
     
    if(j != 0)goto save_commande;
    listePipe[length] = NULL;
    if(length > 1)hasPipe=true;
    free(f);
    this->calcule_args();
}
