
#include <iostream>
#include "header.h"

#include "commande.h"

    using namespace std;

    /* The array below will hold the arguments: args[0] is the command. */
    

 
    #define READ  0
    #define WRITE 1   
      /*
    List of builtin commands, followed by their corresponding functions.
    */

   
        int (*builtin_func[]) (char **) = {
            &cd,
            &help,
            &_exit,
            &history
        };
    
    commande::commande(){
        length = 0;
        has_pipe = false;
    };
    commande::commande(unsigned int argc,char** argv){
        
        listePipe = new char*[argc];   
        for(length = 0;  length < argc; length ++){
            listePipe[length] = argv [length];
        }
        this->calcule_args( );
    };
    void commande::affiche(void){
        unsigned int i = 0;
        while(i < length){
            cout << args[i] << "  ";
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
        for(i; i < length; i++){
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
        if(position < 0 || position >=length){
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
        has_pipe = false;
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
        if(st < 0 || end >=length){
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
        delete l1.args,l1.listePipe;
        l1.listePipe =  new char * [l1.length]; 
        for( i = 0; i < l1.length - l2.length; i++){
            l1.listePipe[i] = tampon[i]  ;
        }
        for(i; i < l1.length; i++){
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
        if (execvp(args[0][0], args[0]) == -1) {
        perror("msh");
        }
        exit(EXIT_FAILURE);
    } else if (pid < 0) {
        // Error forking
        perror("msh");
    } else {
        // Parent process
        do {
        waitpid(pid, &status, WUNTRACED);
        } while (!WIFEXITED(status) && !WIFSIGNALED(status));
    }

    return 1;
    }

    /**
     @brief Execute shell built-in or launch program.
    @param args Null terminated list of arguments.
    @return 1 if the shell should continue running, 0 if it should terminate
    */
    int commande::execute()
    {
    size_t i,j;

    if (listePipe[0] == NULL) {
        // An empty command was entered.
        return 1;
    }
    


    if(has_pipe){
        
        input = 0;
		bool first = true;
        i = 0;
        
        while (i < length -1) {
			

			input = this->command(i, first, false);
 
			first = false;
            i++;
		}
		input = command(i, first, true);
		cleanup(length);
        return 1;
    }else
    {
       
       
        for (j = 0; j < num_builtins(); j++) {
            if (strcmp(args[0][0], (const char *)builtin_str[j]) == 0) {
                    return (*builtin_func[j])(args[0]);
            }
        }        
        
        return launch();    
    
    }
    
    }

    



    /**
     @brief Split a line into argss (very naively).
    @param line The line.
    
    */
    
    int commande::calcule_args()
    {
    int bufsize = 512, position = 0;
    args = (char ***)malloc(bufsize * sizeof(char***));
    char *arg, ***args_backup;
    size_t i = 0;
    
    if (!args) {
        cerr << "msh: allocation error" << endl;
        exit(EXIT_FAILURE);
    }

    while(i < length){
        args[i] = (char **)malloc(bufsize * sizeof(char**));
        position = 0;
        arg = strtok(listePipe[i], TOK_DELIM);

    while (arg != NULL) {
        args[i][position] = arg;
        position++;

        if (position >= bufsize) {
        bufsize += TOK_BUFSIZE;
        args_backup = args;
        args = (char ***)realloc(args, bufsize * sizeof(char***));
        if (!args) {
            free(args_backup);
            cerr << "msh: allocation error" << endl;
            exit(EXIT_FAILURE);
        }
        }

        arg = strtok(NULL, TOK_DELIM);
    }
        args[i][position] = NULL;
        i++;
    }
    
    
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
        
        
        for (size_t j = 0; j < num_builtins(); j++) {
            if (strcmp(args[cmd][0], (const char *)builtin_str[j]) == 0) {
                    return (*builtin_func[j])(args[cmd]);
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
commande::commande(char * line){
        size_t i(0),j(0),max = strlen(line);
        listePipe = (char **)malloc(512 * sizeof(char**));
        char  cmd [1024] = {'\0'};
        char * v;
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

save_commande:              cout << line << endl;
                            line[i] ='\0';
                            listePipe[length] = line;
                            line = line + i + 1;
                            length++;                          
                            
                            j=0;
                            goto pass;
                        }
                    }
                }
            }

           
            cmd[j]= line[i];    
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
    if(length > 1)has_pipe=true;
     
    this->calcule_args();
}