/* **************************************************************************************** */
/*                                                                                          */
/*                                               :::::::::: ::::::::   ::::::::  :::::::::: */
/*   main.c                                      :+:       :+:        :+:   :+:     :+:     */
/*                                              +:+       +:+        +:+           +:+      */
/*   By: root <root@myges.fr>                  +#++:++#  +#++:++#++ :#:           +#+       */
/*                                            +#+              +#+ +#+  +#+#     +#+        */
/*   Created: 2020/03/03 20:53:40 by root    #+#              #+# #+#    #+     #+#         */
/*   Updated: 2020/03/06 13:59:45 by root   ##########  ########  ######## ###########      */
/*                                                                                          */
/* **************************************************************************************** */

#include "../inc/fusion.h"

int main(void)
{
  char pdir_backup[142];

  printf("/*        Fusion       *\\\nDeveloped by Tibaldi x Malecot\nLe 03/03/2020\n\\*                     */\n");
  printf("Veuillez entrer le chemin du repertoire: backup/\nou Ctrl + c pour quitter\nchemin>");
  get_input(pdir_backup, 142);
  while (!show_dir(pdir_backup))
  {
    printf("Impossible d'ouvrir le repertoire !\n");
    printf("Veuillez entrer un nouveau chemin.\n");
    printf("chemin>");
    get_input(pdir_backup, 142);
  }
  select_dir(dir_backup);
  return 1;
}



int   show_dir(char *path)
{
  DIR *pdir = NULL;           //pointeur vers un dossier, il vaut mieux l'initialiser
  struct dirent *pent = NULL;
  t_dir *start = NULL;
  t_dir *new;           //structure nécessaire a la lecture de
  int i;

  i = 0;
  if (!(pdir = opendir (path)))   //si il y a eu un problème pour l'ouverture du répertoire
  {
    printf("Erreur lors de l'ouverture du dossier de backup!\n");
    return 0;
   }
   printf("######## Contenu du dossier : %s ########\n", path);
   while ((pent = readdir(pdir)))
   {
     if (pent == NULL)
      return 0;
     new = lst_new(pent->d_name, i);
     lstadd_back(&start, new);
     printf("Dossier %d : %s\n", i, new->path);
     i++;                                                     //le nom du fichier
   }
  display_list(start);
  closedir(pdir);
  return 1;
}

/*char *choice_pdir_backup(void)
{
  return NULL;
}

int opendir(void)
{
  DIR *pdir = NULL;           //pointeur vers un dossier, il vaut mieux l'initialiser
  struct dirent *pent = NULL;           //structure nécessaire a la lecture de
     //répertoire, elle contiendra le nom
     //du/des fichier
  pdir = opendir (".");                  // "." veut dire "le répertoire dans
  //lequel est contenu le dossier"
  if (pdir == NULL)                      //si il y a eu un problème pour l'ouverture du répertoire
  {
    printf("Erreur lors de l'ouverture !\n"); //on avertit l'utilisateur
    return 0;               //on quitte en renvoyant un resultat d'erreur
   }
   printf("Le dossier est ouvert\n");
   while (pent = readdir (pdir))          //tant qu'il reste quelque chose qu'on a pas lister
   {
       if (pent == NULL)                  //si il y a eu un probleme dans
       {                                  //l'ouverture d'un fichier du repertoire
          printf("Impossible de lire le fichier\n");
          return 0;       //on quitte
       }
       printf("Dossier : %s\n", pent->d_name); //si il n'y a pas eu d'erreur on écrit                                                          //le nom du fichier
   }
  closedir (pdir); //on libère des ressources
   return 1;
}*/
