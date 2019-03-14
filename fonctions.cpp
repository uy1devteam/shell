#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>
#include <glob.h>
#include "header.h"
    using namespace std;

void ajout_environnement(char *nom_variable,char *valeur_variable, Environnement *var_environnement)
{
    Environnement *liste = var_environnement;
    
    int test=0;
    if (liste!=NULL)
    {
        while (liste->next!=NULL)
        {
            if (strcmp(nom_variable,liste->nom)==0)
            {
                free(liste->valeur);
                liste->valeur=strdup(valeur_variable);
                test=1;
            }
            liste=liste->next;
        }
    }
    
    if (test==0)
    {
        Environnement *new_env = (Environnement * )malloc(sizeof(Environnement));
        new_env->nom=strdup(nom_variable);
        new_env->valeur=strdup(valeur_variable);
        new_env->next=NULL;
        liste=var_environnement;
        if (liste!=NULL)
        {
            while(liste->next!=NULL)
            {
                liste=liste->next;
            }    
            liste->next=new_env;
        }
        else
        {
            var_environnement=new_env;
        }
    }
}

void str_replace(char *chaine,const char* recherche,const char *remplace)
{
int nbre=0;

    char *p=chaine;
    char *tmp=strstr(p,recherche);
    while (tmp!=NULL)
    {
        ++nbre;
        p=tmp+strlen(recherche);
        tmp=strstr(p,recherche);
    }
    if (nbre>0)
    {
        char *chaine_copie = (char *)malloc(strlen(chaine)-(strlen(recherche)*nbre)+(strlen(remplace)*nbre)+1);
        chaine_copie[0]='\0';
        char *p=chaine;
        char *tmp=strstr(p,recherche);
        while (tmp!=NULL)
        {
            strncat(chaine_copie,p,tmp-p);
            strcat(chaine_copie,remplace);
            p=tmp+strlen(recherche);
            tmp=strstr(p,recherche);
        }
        strcat(chaine_copie,p);
        strcpy(chaine,chaine_copie);
        free(chaine_copie);
    }
}

void creation_liste_arguments(char *arguments[32],char *commande)
{
int  boucle,increment,longueur;

    for (boucle=0;boucle<32;++boucle)
    {
        arguments[boucle]=NULL;
    }
    longueur=strcspn(commande," \"");
    arguments[0]=strndup(commande,longueur);
    commande=commande+longueur;
    increment=1;
    while (strlen(commande)>0)
    {    
        if (commande[0]==' ') ++commande;
        char *separateur=" ";
        if (commande[0]=='"') separateur="\"";
        if (strcmp(separateur,"\"")==0) ++commande;
        longueur=strcspn(commande,separateur);
        arguments[increment]=strndup(commande,longueur);
        commande=commande+longueur;
        if (strcmp(separateur,"\"")==0) ++commande;
        ++increment;
    }
}

void gestion_variables(char* arguments[32],char **argv, int& global_argc, Environnement *var_environnement)
{
int increment=0;

    while (arguments[increment]!=NULL)
    {
        char *chaine_a_scanner=arguments[increment];
        if (chaine_a_scanner[0]=='$') 
        {
            int detection=0;
            char *endptr=NULL;
            int entier=strtol(arguments[increment]+1,&endptr,10);
            if (strcmp(endptr,"")!=0) entier=-1;
            if (entier!=-1)
            {
                if (entier+1<=global_argc)
                {
                    free(arguments[increment]);
                    arguments[increment]=strdup(argv[entier]);
                    detection=1;
                }
            }
            else
            {
                Environnement *liste=var_environnement;
                while (liste!=NULL)
                {
                    if (strcmp(liste->nom,chaine_a_scanner+1)==0)
                    {
                        free(arguments[increment]);
                        arguments[increment]=strdup(liste->valeur);
                        detection=1;
                    }
                    liste=liste->next;
                }
            }
            if (detection==0)
            {
                free(arguments[increment]);
                arguments[increment]=strdup("");
            }
        }
        ++increment;
    }
}

void liberation_arguments(char *arguments[32])
{
int increment=0;
    while (arguments[increment]!=NULL)
    {
        free(arguments[increment]);
        increment++;
    }
}

void traitement_joker(char *arguments[32])
{
char *arg_list_tmp[32];

    int increment=0;
    int increment_tmp=0;
    while (arguments[increment]!=NULL)
    {
        int longueur_sans_asterisque=strcspn(arguments[increment],"*");
        char *tmp=strstr(arguments[increment],"*");
        if (tmp!=NULL)
        {
            if (longueur_sans_asterisque!=0) tmp=tmp-longueur_sans_asterisque;
            glob_t g;
            int retour_glob=glob(tmp,0,NULL,&g);
            if (retour_glob==0)
            {
                unsigned int boucle;
                for (boucle=0;boucle<g.gl_pathc;++boucle)
                {
                    arg_list_tmp[increment_tmp]=strdup(g.gl_pathv[boucle]);
                    ++increment_tmp;
                }
                free(arguments[increment]);
            }
            else
            {
                arg_list_tmp[increment_tmp]=arguments[increment];
                ++increment_tmp;
            }
            globfree(&g);
        }
        else
        {
            arg_list_tmp[increment_tmp]=arguments[increment];
            ++increment_tmp;
        }
        ++increment;
    }
    arg_list_tmp[increment_tmp]=NULL;
    increment=0;
    while (arg_list_tmp[increment]!=NULL)
    {
        arguments[increment]=arg_list_tmp[increment];
        ++increment;
    }
    arguments[increment]=NULL;
}
char *scan_redirection_entrante(char *arguments[32])
{
char *redirection=NULL;
int  increment=0;

    while (arguments[increment]!=NULL)
    {
        if (strcmp(arguments[increment],"<")==0)
        {
            redirection=arguments[increment+1];
            free(arguments[increment]);        
            while (arguments[increment+2]!=NULL)
            {
                arguments[increment]=arguments[increment+2];
                ++increment;
            }
            arguments[increment]=NULL;
        }
        ++increment;
    }
    return redirection;
}

char *scan_redirection_sortante(char *arguments[32])
{
char *redirection=NULL;
int  increment=0;

    while (arguments[increment]!=NULL)
    {
        if (strcmp(arguments[increment],">")==0)
        {
            redirection = (char *) malloc(strlen(arguments[increment+1])+1);
            redirection[0]='w';
            redirection[1]='\0';
            strcat(redirection,arguments[increment+1]);
            free(arguments[increment]);    
            free(arguments[increment+1]);    
            while (arguments[increment+2]!=NULL)
            {
                arguments[increment]=arguments[increment+2];
                ++increment;
            }
            arguments[increment]=NULL;
        }
        else if (strcmp(arguments[increment],">>")==0)
        {
            redirection = ( char *) malloc(strlen(arguments[increment+1])+1);
            redirection[0]='a';
            redirection[1]='\0';
            strcat(redirection,arguments[increment+1]);
            free(arguments[increment]);    
            free(arguments[increment+1]);    
            while (arguments[increment+2]!=NULL)
            {
                arguments[increment]=arguments[increment+2];
                ++increment;
            }
            arguments[increment]=NULL;
        }
        ++increment;
    }
    return redirection;
}


void traitement_espaces_debut(char *chaine_a_traiter)
{
    char *nouvelle_chaine=chaine_a_traiter;
    while (nouvelle_chaine[0]==' ')
    {
        ++nouvelle_chaine;
    }
    memmove(chaine_a_traiter,nouvelle_chaine,strlen(nouvelle_chaine)+1);
}

void traitement_espaces_fin(char *chaine_a_traiter)
{
    while (chaine_a_traiter[strlen(chaine_a_traiter)-1]==' ')
    {
        chaine_a_traiter[strlen(chaine_a_traiter)-1]='\0';
    }
}


void traitement_ligne(char buffer[250],char *arg_list[32],char *arg_list2[32],char* argv[],Environnement *var_environnement, FILE *fichier, int& global_argc)
{
    char *cmd=strdup(buffer);
    char *tmp=strtok(cmd,";");
    while (tmp!=NULL)
    {
            if (strncmp(buffer,"if",2)==0)
        {
            char *lecture=buffer;
            int boucle=0;
            Environnement *var_if = (Environnement *) malloc(sizeof(Environnement));
            var_if->nom = (char *)malloc(4);
            sprintf(var_if->nom,"%d",boucle);
            var_if->valeur=strdup(buffer);
            var_if->next=NULL;
            if (strncmp(buffer,"if [",4)!=0)
            {
                fprintf(stderr,"%s : Erreur de syntaxe\n",buffer);
                exit(EXIT_FAILURE);
            }
            char *test_fin=strstr(buffer,"]");
            if (strcmp(test_fin,"]")!=0 && strcmp(test_fin,"] ")!=0)
            {
                fprintf(stderr,"%s : Erreur de syntaxe\n",buffer);
                exit(EXIT_FAILURE);
            }
            char *formule=strdup(buffer);
            str_replace(formule,"if [","");
            str_replace(formule,"]","");
            str_replace(formule," ","");
            str_replace(formule,"\"","");    
            int retour=strcspn(formule,"=");
            if (retour==strlen(formule))
            {
                fprintf(stderr,"%s : Erreur de syntaxe\n",buffer);
                exit(EXIT_FAILURE);            
            }
            char *arg_list_temp[32];
            arg_list_temp[0]=strndup(formule,retour);
            arg_list_temp[1]=strdup(formule+retour+1);
            arg_list_temp[2]=NULL;
            gestion_variables(arg_list_temp,argv, global_argc,var_environnement );
            int test=strcmp(arg_list_temp[0],arg_list_temp[1]);
            free(arg_list_temp[1]);
            free(arg_list_temp[0]);
            free(formule);
            Environnement *liste_var_if=var_if;
            Environnement *liste=liste_var_if;
            while (lecture!=NULL)
            {
                lecture=fgets(buffer,150,fichier);
                traitement_espaces_debut(buffer);
                if (lecture==NULL) break;
                if (buffer[strlen(buffer)-1]=='\n') buffer[strlen(buffer)-1]='\0';
                if (strncmp(buffer,"fi",2)==0)
                {
                    ++boucle;
                    var_if = (Environnement *)malloc(sizeof(Environnement));
                    var_if->nom = (char *)malloc(4);
                    sprintf(var_if->nom,"%d",boucle);
                    var_if->valeur=strdup(buffer);
                    var_if->next=NULL;
                    liste->next=var_if;
                    liste=var_if;
                    lecture=NULL;                
                }
                else
                {
                    ++boucle;
                    var_if = (Environnement *)malloc(sizeof(Environnement));
                    var_if->nom = (char *)malloc(4);
                    sprintf(var_if->nom,"%d",boucle);
                    var_if->valeur=strdup(buffer);
                    var_if->next=NULL;
                    liste->next=var_if;
                    liste=var_if;
                }
            }
            if (strcmp(liste->valeur,"fi")!=0)
            {
                fprintf(stderr,"%s : Erreur de syntaxe\n",buffer);
                exit(EXIT_FAILURE);                        
            }
            liste=liste_var_if;
            liste=liste->next;
            str_replace(liste->valeur," ","");
            if (strcmp(liste->valeur,"then")!=0)
            {
                fprintf(stderr,"*%s* : Erreur de syntaxe\n",liste->valeur);
                exit(EXIT_FAILURE);                        
            }
            liste=liste_var_if;
            liste=liste->next;
            liste=liste->next;
            int detection_else=0;
            while (liste!=NULL)
            {
                if (strcmp(liste->valeur,"else")==0)
                {
                    detection_else=1;
                }
                else if (strcmp(liste->valeur,"fi")==0)
                {
                }
                else if (liste->valeur[0]=='#')
                {
                }
                else
                {
                    if (test==0)
                    {
                        if (detection_else==0)
                        {
                            traitement_cmd(liste->valeur,argv,arg_list);
                        }
                    }
                    else
                    {
                        if (detection_else==1)
                        {
                            traitement_cmd(liste->valeur,argv,arg_list);
                        }
                    }
                }
                liste=liste->next;
            }        
        }
        traitement_cmd(tmp, arg_list, arg_list2);
        tmp=strtok(NULL,";");
    }
    free(cmd);
}


void traitement_cmd(char *commande, char *arg_list[32],char *arg_list2[32])
{
char *cmd1,*cmd2;
char *fichier_redirection_sortante,*fichier_redirection_entrante;
char *fichier_redirection_sortante2,*fichier_redirection_entrante2;
int pipefd[2];

    cmd2=NULL;
    str_replace(commande,"\n","");
    str_replace(commande," <","<");
    str_replace(commande,"< ","<");
    str_replace(commande,"<"," < ");
    str_replace(commande," >",">");
    str_replace(commande,"> ",">");
    str_replace(commande,">"," > ");
    str_replace(commande," >  > "," >> ");
    str_replace(commande,"| ","|");
    str_replace(commande," |","|");
    str_replace(commande,"|"," | ");
    char *tmp=strstr(commande," | ");
    if (tmp!=NULL)
    {
        cmd1=strndup(commande,strlen(commande)-strlen(tmp));
        cmd2=strdup(tmp+3);
    }
    else
    {
        cmd1=strdup(commande);
    }
    creation_liste_arguments(arg_list,cmd1);
    traitement_joker(arg_list);
    fichier_redirection_sortante=scan_redirection_sortante(arg_list);
    fichier_redirection_entrante=scan_redirection_entrante(arg_list);
    if (cmd2!=NULL)
    {
        creation_liste_arguments(arg_list2,cmd2);
        traitement_joker(arg_list2);
        fichier_redirection_sortante2=scan_redirection_sortante(arg_list2);
        fichier_redirection_entrante2=scan_redirection_entrante(arg_list2);
    }        
    pipe(pipefd);
    pid_t process=fork();
    if (process==0)
    {
        if (cmd2!=NULL) 
        {
            dup2(pipefd[1],STDOUT_FILENO);
        }
        if (fichier_redirection_entrante!=NULL)
        {
            long handler=(long)freopen(fichier_redirection_entrante,"r", stdin);
            if (handler==-1) 
            {
                fprintf(stderr,"%s\n",strerror(errno));
                exit(0);
            }
        }
        if (fichier_redirection_sortante!=NULL)
        {
            char* type_redirection=strndup(fichier_redirection_sortante,1);
            long handler=(long)freopen(fichier_redirection_sortante+1,type_redirection, stdout);
            if (handler==-1) 
            {
                fprintf(stderr,"%s\n",strerror(errno));
                exit(0);
            }
            free(type_redirection);
        }
        int retour=execvp(arg_list[0],arg_list);
        if (retour==-1) printf("%s\n",strerror(errno));
        exit(0);
    }
    else
    {
        wait(&process);
    }
    if (cmd2!=NULL)
    {
        pid_t process2=fork();
        if (process2==0)
        {
            dup2(pipefd[0],STDIN_FILENO);
            if (fichier_redirection_entrante2!=NULL)
            {
                long handler=(long)freopen(fichier_redirection_entrante2,"r", stdin);
                if (handler==-1) 
                {
                    fprintf(stderr,"%s\n",strerror(errno));
                    exit(0);
                }
            }
            if (fichier_redirection_sortante2!=NULL)
            {
                char* type_redirection=strndup(fichier_redirection_sortante,1);
                long handler=(long)freopen(fichier_redirection_sortante2+1,type_redirection, stdout);
                if (handler==-1) 
                {
                    fprintf(stderr,"%s\n",strerror(errno));
                    exit(0);
                }
                free(type_redirection);
            }
            int retour=execvp(arg_list2[0],arg_list2);
            if (retour==-1) printf("%s\n",strerror(errno));
            exit(0);
        }
        else
        {
            wait(&process2);
        }
    }
        
    if (cmd2!=NULL)
    {
        if (fichier_redirection_sortante2!=NULL) free(fichier_redirection_sortante2);
        if (fichier_redirection_entrante2!=NULL) free(fichier_redirection_entrante2);
        liberation_arguments(arg_list2);
        free(cmd2);
        cmd2=NULL;
    }
    if (fichier_redirection_entrante!=NULL) free(fichier_redirection_entrante);
    if (fichier_redirection_sortante!=NULL) free(fichier_redirection_sortante);
    liberation_arguments(arg_list);
    free(cmd1);
}
