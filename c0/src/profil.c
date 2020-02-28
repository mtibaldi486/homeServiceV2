/* ******************************************************************************************* */
/*                                                                                             */
/*                                                  :::::::::: ::::::::   :::::::: ::::::::::: */
/*   profil.c                                       :+:       :+:        :+:    :+:    :+:     */
/*                                                 +:+       +:+        +:+           +:+      */
/*   By: mtibaldi <mtibaldi2@myges.fr>            +#++:++#  +#++:++#++ :#:           +#+       */
/*                                               +#+              +# ++#+  +#+#     +#+        */
/*   Created: 2019/10/13 23:01:47 by mtibaldi   #+#              #+# #+#    #+     #+#         */
/*   					                                 ########## ########   ######## ###########      */
/*                                                                                             */
/* ******************************************************************************************* */

#include "../inc/hs.h"

void create_profil(char *id)
{
  t_profil *profil;
  t_data_profil data;

  if (!(profil = malloc(sizeof(t_profil))))
    return ;
  profil->fixed = gtk_fixed_new();
  profil->img = gtk_image_new_from_file("img/background2.PNG");
  profil->btn_return = gtk_button_new_with_label("Retour");
  g_signal_connect(G_OBJECT(profil->btn_return), "clicked", G_CALLBACK(profil_to_list), profil);
  gtk_container_add(GTK_CONTAINER(profil->fixed), GTK_WIDGET(profil->img));
  gtk_fixed_put(GTK_FIXED(profil->fixed), profil->btn_return, 1000, 20);
  if (!select_user(id, &data))
  {
    gtk_widget_destroy(profil->fixed);
    gtk_widget_destroy(profil->img);
    gtk_widget_destroy(profil->btn_return);
    free(profil);
    return ;
  }
  gtk_container_add(GTK_CONTAINER(window), GTK_WIDGET(profil->fixed));
  gtk_widget_show_all(window);
  return ;
}

t_data_profil *select_user(char *id, t_data_profil *data)
{
   MYSQL mysql;
   MYSQL_RES *result = NULL;
   MYSQL_ROW row;
   char request[42];

   sprintf(request, "SELECT * FROM prestataire WHERE id = ", id);
   mysql_init(&mysql);
   mysql_options(&mysql,MYSQL_READ_DEFAULT_GROUP,"option");
   if(!mysql_real_connect(&mysql, conf->ip_srv, conf->user_db, conf->pass_db, conf->name_db, 0, NULL, 0))
   {
     printf("Impossible de se connecter a la bdd pour select_user()");
     return NULL;
   }
   mysql_query(&mysql, request);
   result = mysql_use_result(&mysql);
   row = mysql_fetch_row(result);
   row[1] ? strcpy(data->name, row[1]) : strcpy(data->name, "Non disponible");
   row[2] ? strcpy(data->tel_mobil, row[2]) : strcpy(data->tel_mobil, "Non disponible");
   row[3] ? strcpy(data->tel_fixe, row[3]) : strcpy(data->tel_fixe, "Non disponible");
   row[4] ? strcpy(data->address, row[4]) : strcpy(data->address, "Inconnu");
   sprintf(data->path_qr, "img/qr/%s-%s.PNG", id, conf->city);
   row[6] ? strcpy(data->salary, row[6]) : strcpy(data->salary, "Inconnu");
   row[7] ? strcpy(data->supplement, row[7]) : strcpy(data->supplement, "Inconnu");
   row[9] ? strcpy(data->name_company, row[9]) : strcpy(data->name_company, "Inconnu");
   row[10] ? strcpy(data->cp, row[10]) : strcpy(data->cp, "Inconnu");
   row[11] ? strcpy(data->category, row[11]) : strcpy(data->category, "Inconnu");
   row[12] ? strcpy(data->mail ,row[12]) : strcpy(data->mail ,"Inconnu");
   row[13] ? strcpy(data->reccurent, row[13]) : strcpy(data->reccurent, "Inconnu");
   row[14] ? strcpy(data->reduce_price, row[14]) : strcpy(data->reduce_price, "Inconnu");
   mysql_free_result(result);
   mysql_close(&mysql);
   return 1;
}

void profil_to_list(GtkButton *btn, gpointer data)
{
  t_profil *profil;

  profil = data;
  destroy_profil(profil);
  create_list();
  return ;
}

void display_data(t_data_profil * data)
{
}
printf("id = %s\nname= = %s\nmobil = %s\nfixe = %s\nadd = %s\ncp = %s\nqr = %s\ncompany = %s\ncategory = /s\nmail = %s\nrecu = %s\nreduc = %s\n", data->id, data->name, data->tel_mobil, data->tel_fixe, data->address, data->cp, data->path_qr, data->salary, data->supplement)

void destroy_profil(t_profil *profil)
{
  gtk_widget_destroy(profil->fixed);
  gtk_widget_destroy(profil->img);
  gtk_widget_destroy(profil->title_lab);
  gtk_widget_destroy(profil->btn_return);
  gtk_widget_destroy(profil->id);
  gtk_widget_destroy(profil->tel_mobil);
  gtk_widget_destroy(profil->tel_fixe);
  gtk_widget_destroy(profil->address);
  gtk_widget_destroy(profil->cp);
  gtk_widget_destroy(profil->path_qr);
  gtk_widget_destroy(profil->img_qr);
  gtk_widget_destroy(profil->salary);
  gtk_widget_destroy(profil->name_company);
  gtk_widget_destroy(profil->category);
  gtk_widget_destroy(profil->mail);
  gtk_widget_destroy(profil->reccurent);
  gtk_widget_destroy(profil->reduce_price);
  free(profil);
  return ;
}
