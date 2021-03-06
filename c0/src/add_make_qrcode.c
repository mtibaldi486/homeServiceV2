/* **************************************************************************************** */
/*                                                                                          */
/*                                               :::::::::: ::::::::   ::::::::  :::::::::: */
/*   add_make_qrcode.c                           :+:       :+:        :+:   :+:     :+:     */
/*                                              +:+       +:+        +:+           +:+      */
/*   By: root <root@myges.fr>                  +#++:++#  +#++:++#++ :#:           +#+       */
/*                                            +#+              +#+ +#+  +#+#     +#+        */
/*   Created: 2020/03/03 10:57:59 by root    #+#              #+# #+#    #+     #+#         */
/*   Updated: 2020/05/02 19:46:12 by root   ##########  ########  ######## ###########      */
/*                                                                                          */
/* **************************************************************************************** */

#include "../inc/hs.h"

char *recup_last_id(char *id)
{
  MYSQL *con = NULL;
  MYSQL_RES *res;
  MYSQL_ROW row;

  con = mysql_init(con);
  if (con == NULL)
  {
      fprintf(stderr, "mysql_init() failed in recup_las_id()\n");
      return NULL;
  }
  if (mysql_real_connect(con, conf->ip_srv, conf->user_db, conf->pass_db,
  conf->name_db, 0, NULL, 0) == NULL)
  {
    printf("Impossible de se connecter a la bdd");
    return (0);
  }
  if (mysql_query(con, "SELECT MAX(id_prestataire) FROM prestataire"))
    return (NULL);
  res = mysql_use_result(con);
  row = mysql_fetch_row(res);
  if (row[0])
    strcpy(id, row[0]);
  else
    return NULL;
  mysql_free_result(res);
  mysql_close(con);
  return (id);
}

void make_qr(t_input *input)
{
  char id[30];
  char path[200];
  char cmd[420];

  if (!(recup_last_id(id)))
    strcpy(id, "1");
  sprintf(path, "img/qr/%s-%s", id, conf->city);
  sprintf(cmd, "qrencode -o %s.png %s", path, path);
  system(cmd);
  input->url_qr = strdup(path);
  return ;
}
