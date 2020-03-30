/* **************************************************************************************** */
/*                                                                                          */
/*                                               :::::::::: ::::::::   ::::::::  :::::::::: */
/*   setup.c                                     :+:       :+:        :+:   :+:     :+:     */
/*                                              +:+       +:+        +:+           +:+      */
/*   By: root <root@myges.fr>                  +#++:++#  +#++:++#++ :#:           +#+       */
/*                                            +#+              +#+ +#+  +#+#     +#+        */
/*   Created: 2020/03/29 01:09:29 by root    #+#              #+# #+#    #+     #+#         */
/*   Updated: 2020/03/29 21:57:59 by root   ##########  ########  ######## ###########      */
/*                                                                                          */
/* **************************************************************************************** */

#include "../inc/fusion.h"

t_conf *load_conf(t_conf *conf)
{
  FILE          *fd;
  char          buff[1024];
  int           count = 0;

  if (!(fd = fopen("conf.ini" , "rb")))
    return NULL;
  while (fgets(buff, 1023, fd))
  {
    if (strlen(buff))
      if ((buff[strlen(buff) - 1] = '\n'))
        buff[strlen(buff) - 1] = '\0';
    if (buff[0] != '#' && strstr(buff, "ip srv"))
      conf->ip_srv = parse_line(strstr(buff, "ip srv"), &count);
    if (buff[0] != '#' && strstr(buff, "name_db"))
      conf->name_db = parse_line(strstr(buff, "name_db"), &count);
    if (buff[0] != '#' && strstr(buff, "user_db"))
      conf->user_db = parse_line(strstr(buff, "user_db"), &count);
    if (buff[0] != '#' && strstr(buff, "pass_db"))
      conf->pass_db = parse_line(strstr(buff, "pass_db"), &count);
  }
  fclose(fd);
  if (count == 4 && check_conf(conf))
    return (conf);
  else
    return NULL;
}

char *parse_line(char *str, int *counter)
{
  char *res;
  char *sep;
  int len = 0;

  sep = strchr(str, ':');
  while (*++sep == ' ')
    ;
  while (sep[len] != ' ' && sep[len] != '\n')
    len++;
  if (!(res = strndup(sep, len)))
    return NULL;
  if (res[0])
    (*counter)++;
  return res;
}

int  check_conf(t_conf *conf)
{
  if (!*(conf->name_db))
  {
    printf("la name_db est == null\n");
    return 0;
  }
  if (!*(conf->user_db))
  {
    printf("la user_db est == null\n");
    return 0;
  }
  if (!*(conf->pass_db))
  {
    printf("la pass_db est == null\n");
    return 0;
  }
  if (!*(conf->ip_srv))
  {
    printf("la ip_srv est == null\n");
    return 0;
  }
  return 1;
}

void create_conf(void)
{
  FILE *fd;

  if (!(fd = fopen("conf.ini" , "w")))
    return ;
  fprintf(fd, "##################################################\n");
  fprintf(fd, "#             Fichier de configuration           #\n");
  fprintf(fd, "#                de la db cilble                 #\n");
  fprintf(fd, "##################################################\n");
  fprintf(fd, "ip srv :\n");
  fprintf(fd, "name_db :\n");
  fprintf(fd, "user_db :\n");
  fprintf(fd, "pass_db :\n");
  fclose(fd);
  return ;
}

void free_conf(t_conf *conf)
{
  free(conf->ip_srv);
  free(conf->name_db);
  free(conf->pass_db);
  free(conf->user_db);
  free(conf);
  return ;
}

void display_conf(t_conf *conf)
{
  printf("/////CONF/////\ndb = '%s'\npass = %s\nuser = %s\n ip = %s\n", conf->name_db, conf->pass_db, conf->user_db, conf->ip_srv);
  return ;
}
