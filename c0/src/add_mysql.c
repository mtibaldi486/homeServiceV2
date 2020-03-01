/* **************************************************************************************** */
/*                                                                                          */
/*                                               :::::::::: ::::::::   ::::::::  :::::::::: */
/*   add_mysql.c                                 :+:       :+:        :+:   :+:     :+:     */
/*                                              +:+       +:+        +:+           +:+      */
/*   By: root <root@myges.fr>                  +#++:++#  +#++:++#++ :#:           +#+       */
/*                                            +#+              +#+ +#+  +#+#     +#+        */
/*   Created: 2020/02/07 14:39:51 by root    #+#              #+# #+#    #+     #+#         */
/*   Updated: 2020/03/01 19:06:55 by root   ##########  ########  ######## ###########      */
/*                                                                                          */
/* **************************************************************************************** */

#include "../inc/hs.h"

int   insert_presta_bdd(t_input *input)
{
  MYSQL *con = NULL;
  char  request[500];

  if (!(con =mysql_init(con)))
  {
    fprintf(stderr, "mysql_init() failed in insert_presta_bdd()\n");
    return 0;
  }
  if (mysql_real_connect(con, conf->ip_srv, conf->user_db, conf->pass_db,
  conf->name_db, 0, NULL, 0) == NULL)
  {
    printf("Impossible de se connecter a la bdd");
    return (0);
  }
  check_categorie(con, input);
  sprintf(request, "INSERT INTO prestataire (nom, tel_mobile, tel_fixe, adresse_entreprise, url_qrcode, prix_heure, supplement, ville, company_name, code_postal, categorie_nom, email) \
  VALUES ('%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s')" , \
  input->name, input->fixe_phone, input->mobil_phone, input->address, input->url_qr, input->tarif, input->suplement, input->city, input->company_name, input->cp, input->categorie, input->mail);
  printf("request = %s\n", request);
  if (mysql_query(con, request))
  {
    finish_with_error(con);
    return (0);
  }
  mysql_close(con);
  return (1);
}

void check_categorie(MYSQL *con, t_input *input)
{
  char request2[100];
  MYSQL_ROW row = NULL;
  MYSQL_RES *result;

  sprintf(request2, "SELECT * FROM categorie WHERE nom = '%s'", input->categorie);
  if (mysql_query(con, request2))
  {
    finish_with_error(con);
    return ;
  }
  result = mysql_store_result(con);
  if (!(row = mysql_fetch_row(result)))
  {
    printf("nom pas trouver dans categorie\n");
    sprintf(request2, "INSERT INTO categorie VALUES ('%s')", input->categorie);
    if (mysql_query(con, request2))
    {
      finish_with_error(con);
      return ;
    }
  }
  mysql_free_result(result);
}

void finish_with_error(MYSQL *con)
{
  fprintf(stderr, "%s\n", mysql_error(con));
  mysql_close(con);
  return ;
}
