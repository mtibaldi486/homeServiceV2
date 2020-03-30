/* **************************************************************************************** */
/*                                                                                          */
/*                                               :::::::::: ::::::::   ::::::::  :::::::::: */
/*   merge.c                                     :+:       :+:        :+:   :+:     :+:     */
/*                                              +:+       +:+        +:+           +:+      */
/*   By: root <root@myges.fr>                  +#++:++#  +#++:++#++ :#:           +#+       */
/*                                            +#+              +#+ +#+  +#+#     +#+        */
/*   Created: 2020/03/28 17:33:23 by root    #+#              #+# #+#    #+     #+#         */
/*   Updated: 2020/03/29 21:50:12 by root   ##########  ########  ######## ###########      */
/*                                                                                          */
/* **************************************************************************************** */

#include "../inc/fusion.h"

void merge(t_dir *start,  char *path, t_conf *conf)
{
  char path_dump[255];
  char path_log[255];

  create_path_log(path_log, path);
  printf("path log = '%s'\n", path_log);
  while (start)
  {
    strcpy(path_dump, path);
    strcat(path_dump, start->path);
    printf("path dump = '%s'\n", path_dump);
    import_dump(path_dump, path_log, conf);
    start = start->next;
  }
  check_errors(path_log);
}

int import_dump(char *path_dump, char *path_log, t_conf *conf)
{
  char cmd[1024];

  printf("DEBUT IMPORT_DUMP ||||||||||||\n");
  sprintf(cmd, "MYSQL_PWD=%s mysql -u %s -h %s %s < %s 2>> %s",\
  conf->pass_db, conf->user_db, conf->ip_srv, conf->name_db, path_dump, path_log);
  system(cmd);
  return 1;
}

void create_path_log(char *path_log, char *path)
{
  char        date[42];
  time_t      now;
  struct tm   *local;

  // Renvoie l'heure actuelle
  time(&now);
  local = localtime(&now);
  sprintf(date, "%d-%d-%d-%d:%d", local->tm_year + 1900, local->tm_mon + 1, local->tm_mday, local->tm_hour, local->tm_min);
  strcpy(path_log, path);
  strcat(path_log, "logFile-");
  strcat(path_log, date);
  strcat(path_log, ".log");
  return ;
}

void check_errors(char *path_log)
{
  FILE *f;

  printf("%s\n", path_log);
  if (!(f = fopen(path_log, "r")))
    return ;
  fseek(f, 0, SEEK_END);
  if (!ftell(f))
    printf("\nLe merge des bdd c'est dérouler sans erreur !\n");
  else
    printf("\nUne erreur c'est produite veuillez consulter le fichier de log %s\net corriger les erreurs avant de recommencer la fusion\n", path_log);
  fclose(f);
}
