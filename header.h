#ifndef HEADER_H_INCLUDES
#define HEADER_H_INCLUDES
#define EQUAL 0
#define NEGATIF -1
#define TAILLE_HISTO 500
#define TAILLE_TAMPON 150
#include <string>
    using namespace std;
    typedef struct Environnement
    {
        char *nom;
        char *valeur;
        struct Environnement *next;
    } Environnement ;
  
    void ajout_environnement(char *nom_variable,char *valeur_variable, Environnement *var_environnement);
    void str_replace(char *chaine,const char* recherche,const char *remplace);
    void creation_liste_arguments(char *arguments[32],char *commande);
    void gestion_variables(char* arguments[32],char **argv, int& global_argc, Environnement *var_environnement);
    void liberation_arguments(char *arguments[32]);
    void traitement_joker(char *arguments[32]);
    char *scan_redirection_entrante(char *arguments[32]);
    void traitement_espaces_debut(char *chaine_a_traiter);
    char *scan_redirection_sortante(char *arguments[32]);
    void traitement_espaces_fin(char *chaine_a_traiter);
    void traitement_ligne(char buffer[250],char *arg_list[32],char *arg_list2[32],char* argv[],Environnement *var_environnement, FILE *fichier, int& global_argc);
    void traitement_cmd(char *commande, char *arg_list[32],char *arg_list2[32]);
#endif
    