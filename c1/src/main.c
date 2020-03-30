/* **************************************************************************************** */
/*                                                                                          */
/*                                               :::::::::: ::::::::   ::::::::  :::::::::: */
/*   main.c                                      :+:       :+:        :+:   :+:     :+:     */
/*                                              +:+       +:+        +:+           +:+      */
/*   By: root <root@myges.fr>                  +#++:++#  +#++:++#++ :#:           +#+       */
/*                                            +#+              +#+ +#+  +#+#     +#+        */
/*   Created: 2020/03/03 20:53:40 by root    #+#              #+# #+#    #+     #+#         */
/*   Updated: 2020/03/29 21:50:38 by root   ##########  ########  ######## ###########      */
/*                                                                                          */
/* **************************************************************************************** */
#include "../inc/fusion.h"

int main(void)
{
  char pdir_backup[142];
  t_dir *start = NULL;
  t_conf *conf;

  if (!(conf = malloc(sizeof(t_conf))))
    return 0;
  if (!(conf = load_conf(conf)))
  {
    printf("load fail\n");
    create_conf();
    free(conf);
    return 0;
  }
  printf("/*        Fusion       *\\\nDeveloped by Tibaldi x Malecot\nLe 03/03/2020\n\\*                     */\n");
  printf("Veuillez entrer le chemin du repertoire: backup/\nou Ctrl + c pour quitter\nchemin>");
  get_input(pdir_backup, 142);
  while (!open_dir(pdir_backup, &start))
  {
    printf("Impossible d'ouvrir le repertoire !\n");
    printf("Veuillez entrer un nouveau chemin.\n");
    printf("chemin>");
    get_input(pdir_backup, 142);
  }
  select_dir(&start);
  printf("Un merge de tout les fichier .sql present va etre effectuer vers la base central y/n :");
  merge(start, pdir_backup, conf);
  free_conf(conf);
  dellist(&start);
  return 1;
}

/* Fonction de recuperation de tout les fichier .sql
  Permet de supprimer de la list tout les fichier sans l'extension .sql */
int  select_dir(t_dir **start)
{
  t_dir   *lst = *start;

  while (lst)
  {
    if (!(strstr(lst->path, ".sql") && *(strstr(lst->path, ".sql") + 4) == '\0') && *(lst->path))
    {
      lst = lstdelone(lst, start);
      continue ;
    }
    lst = lst->next;
  }
  return 1;
}

/* Fonction qui permet d'ouvrrir un reptoire et créer une liste de tous ce qu'il contient */
int   open_dir(char *path, t_dir **start)
{
  DIR *pdir = NULL;           //pointeur vers un dossier, il vaut mieux l'initialiser
  struct dirent *pent = NULL;
  t_dir *new;

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
     new = lst_new(pent->d_name);
     lstadd_back(start, new);
     printf("File : %s\n", new->path);   //le nom du fichier
   }
  closedir(pdir);
  return 1;
}
