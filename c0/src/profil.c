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
    create_list();
    return ;
  }
  display_data(&data);
  create_lab_profil(profil, &data);
  display_lab_profil(profil);
  gtk_container_add(GTK_CONTAINER(window), GTK_WIDGET(profil->fixed));
  gtk_widget_show_all(window);
  return ;
}

t_data_profil *select_user(char *id, t_data_profil *data)
{
   MYSQL mysql;
   MYSQL_RES *result = NULL;
   MYSQL_ROW row;
   char request[242];

   printf("id = %s\n", id);
   sprintf(request, "SELECT (id, nom, tel_mobile, tel_fixe, adresse_entreprise, url_qrcode, prix_heure, company_name, code_post, category ,email, nb_heure_min, prix_recurrent) FROM prestataire WHERE id_prestataire = %s", id);
   mysql_init(&mysql);
   mysql_options(&mysql,MYSQL_READ_DEFAULT_GROUP,"option");
   if(!mysql_real_connect(&mysql, conf->ip_srv, conf->user_db, conf->pass_db, conf->name_db, 0, NULL, 0))
     return NULL;
   if (mysql_query(&mysql, request))
     return NULL;
   result = mysql_store_result(&mysql);
   write(1, "OK\n", 3);
   row = mysql_fetch_row(result);
   row[1] ? strcpy(data->name, row[1]) : strcpy(data->name, "Non disponible");
   row[2] ? strcpy(data->tel_mobil, row[2]) : strcpy(data->tel_mobil, "Non disponible");
   row[3] ? strcpy(data->tel_fixe, row[3]) : strcpy(data->tel_fixe, "Non disponible");
   row[4] ? strcpy(data->address, row[4]) : strcpy(data->address, "Inconnu");
   sprintf(data->path_qr, "/img/qr/%s-%s.png", id, conf->city);
   row[6] ? strcpy(data->salary, row[6]) : strcpy(data->salary, "Inconnu");
   row[9] ? strcpy(data->name_company, row[9]) : strcpy(data->name_company, "Inconnu");
   row[10] ? strcpy(data->cp, row[10]) : strcpy(data->cp, "Inconnu");
   row[11] ? strcpy(data->category, row[11]) : strcpy(data->category, "Inconnu");
   row[12] ? strcpy(data->mail ,row[12]) : strcpy(data->mail ,"Inconnu");
   row[13] ? strcpy(data->reccurent, row[13]) : strcpy(data->reccurent, "Inconnu");
   row[14] ? strcpy(data->reduce_price, row[14]) : strcpy(data->reduce_price, "Inconnu");
   mysql_free_result(result);
   mysql_close(&mysql);
   return data;
}

void  display_lab_profil(t_profil *profil)
{
/*  gtk_fixed_put(GTK_FIXED(profil->fixed), profil->id, 400, 20);
  printf("lab 0 OK\n");*/
  gtk_fixed_put(GTK_FIXED(profil->fixed), profil->title_lab, 250, 50);
  gtk_fixed_put(GTK_FIXED(profil->fixed), profil->name, 275, 70);
  gtk_fixed_put(GTK_FIXED(profil->fixed), profil->tel_mobil, 275, 90);
  gtk_fixed_put(GTK_FIXED(profil->fixed), profil->tel_fixe, 600, 70);
  gtk_fixed_put(GTK_FIXED(profil->fixed), profil->address, 600, 90);
  gtk_fixed_put(GTK_FIXED(profil->fixed), profil->cp, 275, 140);
  gtk_fixed_put(GTK_FIXED(profil->fixed), profil->img_qr, 275, 160);
  gtk_fixed_put(GTK_FIXED(profil->fixed), profil->salary, 600, 140);
  gtk_fixed_put(GTK_FIXED(profil->fixed), profil->name_company, 275, 210);
  gtk_fixed_put(GTK_FIXED(profil->fixed), profil->category, 275, 230);
  gtk_fixed_put(GTK_FIXED(profil->fixed), profil->mail, 600, 210);
  gtk_fixed_put(GTK_FIXED(profil->fixed), profil->reccurent, 600, 230);
  gtk_fixed_put(GTK_FIXED(profil->fixed), profil->reduce_price, 275, 280);
  return ;
}

void  create_lab_profil(t_profil *profil, t_data_profil *data)
{
  char str[80];

  profil->title_lab = create_lab(profil->title_lab, "Fiche prestataire", 2);
  sprintf(str, "Nom : %s", data->name);
  profil->name = create_lab(profil->name, str, 1);
  sprintf(str, "Mobile : %s", data->tel_mobil);
  profil->tel_mobil = create_lab(profil->tel_mobil, str, 1);
  sprintf(str, "fixe : %s", data->tel_fixe);
  profil->tel_fixe = create_lab(profil->tel_fixe, str, 1);
  sprintf(str, "Adresse : %s", data->address);
  profil->address = create_lab(profil->address, str, 1);
  sprintf(str, "Code postal : %s", data->cp);
  profil->cp = create_lab(profil->cp, str, 1);
  sprintf(str, "Qr code : %s", data->path_qr);
  profil->img_qr = gtk_image_new_from_file("/img/qr/26-paris.png");
  sprintf(str, "Salaire demandé : %s", data->salary);
  profil->salary = create_lab(profil->salary, str, 1);
  sprintf(str, "Entreprise : %s", data->name_company);
  profil->name_company = create_lab(profil->name_company, str, 1);
  sprintf(str, "Category : %s", data->category);
  profil->category = create_lab(profil->category, str, 1);
  sprintf(str, "Mail : %s", data->mail);
  profil->mail = create_lab(profil->mail, str, 1);
  sprintf(str, "Service récurrent : %s", data->reccurent);
  profil->reccurent = create_lab(profil->reccurent, str, 1);
  sprintf(str, "Tarif pour service \nrécurrent : %s", data->reduce_price);
  profil->reduce_price = create_lab(profil->reduce_price, str, 1);
  return ;
}

void profil_to_list(GtkButton *btn, gpointer data)
{
  t_profil *profil;

  (void)btn;
  profil = data;
  destroy_profil(profil);
  create_list();
  return ;
}

void display_data(t_data_profil * data)
{
  printf("id = %s\nname= = %s\nmobil = %s\nfixe = %s\nadd = %s\ncp = %s\nqr = %s\ncompany = %s\nmail = %s\nrecu = %s\nreduc = %s\n",\
          data->id, data->name, data->tel_mobil, data->tel_fixe, data->address, data->cp, data->path_qr, data->name_company, data->mail, data->salary, data->reduce_price);
}

void destroy_profil(t_profil *profil)
{
  gtk_widget_destroy(profil->img);
  gtk_widget_destroy(profil->name);
  gtk_widget_destroy(profil->btn_return);
  gtk_widget_destroy(profil->title_lab);
  gtk_widget_destroy(profil->tel_mobil);
  gtk_widget_destroy(profil->tel_fixe);
  gtk_widget_destroy(profil->address);
  gtk_widget_destroy(profil->cp);
  gtk_widget_destroy(profil->img_qr);
  gtk_widget_destroy(profil->salary);
  gtk_widget_destroy(profil->name_company);
  gtk_widget_destroy(profil->category);
  gtk_widget_destroy(profil->mail);
  gtk_widget_destroy(profil->reccurent);
  gtk_widget_destroy(profil->reduce_price);
  gtk_widget_destroy(profil->fixed);
  free(profil);
  return ;
}
