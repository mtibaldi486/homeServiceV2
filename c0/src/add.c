/* ******************************************************************************************* */
/*                                                                                             */
/*                                                  :::::::::: ::::::::   :::::::: ::::::::::: */
/*   add.c                                          :+:       :+:        :+:    :+:    :+:     */
/*                                                 +:+       +:+        +:+           +:+      */
/*   By: mtibaldi <mtibaldi2@myges.fr>            +#++:++#  +#++:++#++ :#:           +#+       */
/*                                               +#+              +# ++#+  +#+#     +#+        */
/*   Created: 2019/10/13 23:01:47 by mtibaldi   #+#              #+# #+#    #+     #+#         */
/*   					                                 ########## ########   ######## ###########      */
/*                                                                                             */
/* ******************************************************************************************* */

#include "../inc/hs.h"

void create_add()
{
  t_add *add;

  if (!(add = malloc(sizeof(t_add))))
    return ;
  add->lab_error = NULL;
  create_widget_add(add);
  create_combo_box(add);
  g_signal_connect(G_OBJECT(add->btn_return), "clicked", G_CALLBACK(add_to_menu), add);
  g_signal_connect(G_OBJECT(add->btn_register), "clicked", G_CALLBACK(register_provider), add);
  put_widget_add(add);
  gtk_widget_show_all(window);
  return ;
}

void register_provider(GtkButton *btn, gpointer data)
{
  t_add *add;
  t_input *input;

  (void)btn;
  add = data;
  if (!(input = collect_input(add)))
    return ;
  insert_presta_bdd(input);
  make_qr(input);
  add_to_profil(add);
  free((void *)input->url_qr);
  free((void *)input->unit_min);
  free(input);
  return ;
}

GtkWidget *create_combo_box()
{
  GtkWidget *comboBox;
  MYSQL mysql;
  MYSQL_RES *result = NULL;
  MYSQL_ROW row;

  comboBox = gtk_combo_box_text_new_with_entry();
  mysql_init(&mysql);
  if (mysql_real_connect(&mysql, conf->ip_srv, conf->user_db, conf->pass_db,
  conf->name_db, 0, NULL, 0))
  {
    mysql_query(&mysql, "SELECT (nom) FROM categorie");
    result = mysql_use_result(&mysql);
    while ((row = mysql_fetch_row(result)))
    gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(comboBox), NULL, row[0]);
    mysql_free_result(result);
    mysql_close(&mysql);
  }
  else
  printf("Impossible de se connecter a la DB dans Create_combo_box()");
  return comboBox;
}

void add_to_profil(t_add *add)
{
  char id[5];

  recup_last_id(id);
  destroy_add(add);
  create_profil(id);
  return ;
}

void add_to_menu(GtkButton *btn, gpointer data)
{
  t_add *add;

  (void)btn;
  add = data;
  destroy_add(add);
  create_menu();
  return ;
}

void  create_widget_add(t_add *add)
{
  add->fixed = gtk_fixed_new();
  add->img = gtk_image_new_from_file("img/background2.PNG");
  add->btn_return = gtk_button_new_with_label("Retour");
  add->btn_register = gtk_button_new_with_label("Enregistrer le prestataire");
  add->name_entry = gtk_entry_new();
  add->phone_entry = gtk_entry_new();
  add->mphone_entry = gtk_entry_new();
  add->address_entry = gtk_entry_new();
  add->tarif_entry = gtk_entry_new();
  add->suplement_entry = gtk_entry_new();
  add->nameCompany_entry = gtk_entry_new();
  add->cp_entry = gtk_entry_new();
  add->categorie_entry = create_combo_box();
  add->mail_entry = gtk_entry_new();
  add->reccur_entry = gtk_entry_new();
  add->min_entry = gtk_entry_new();
  add->title_lab = create_lab(add->title_lab, "Ajout d'un prestataire", 4);
  add->name_lab = create_lab(add->name_lab, "Nom du prestataire", 1);
  add->phone_lab = create_lab(add->phone_lab, "Numéro de fixe", 1);
  add->mphone_lab = create_lab(add->mphone_lab, "Numéro de mobile", 1);
  add->address_lab = create_lab(add->address_lab, "Adresse", 1);
  add->tarif_lab = create_lab(add->tarif_lab, "Rémunération par unité", 1);
  add->suplement_lab = create_lab(add->suplement_lab, "Préciser tout facturation suplémentaire", 1);
  add->nameCompany_lab = create_lab(add->nameCompany_lab, "Nom de la société", 1);
  add->cp_lab = create_lab(add->cp_lab, "Code postal", 1);
  add->categorie_lab = create_lab(add->categorie_lab, "Secteur", 1);
  add->mail_lab = create_lab(add->mail_lab, "Email", 1);
  add->reccur_lab = create_lab(add->reccur_lab, "Prix reccurent par unité", 1);
  add->min_lab = create_lab(add->reccur_lab, "Nb unit minimum", 1);
}

void put_widget_add(t_add *add)
{
  gtk_container_add(GTK_CONTAINER(add->fixed), GTK_WIDGET(add->img));
  gtk_fixed_put(GTK_FIXED(add->fixed), add->title_lab, 400, 20);
  gtk_fixed_put(GTK_FIXED(add->fixed), add->btn_return, 1000, 20);
  gtk_fixed_put(GTK_FIXED(add->fixed), add->btn_register, 600, 480);
  gtk_fixed_put(GTK_FIXED(add->fixed), add->name_lab, 275, 70);
  gtk_fixed_put(GTK_FIXED(add->fixed), add->name_entry, 275, 90);
  gtk_fixed_put(GTK_FIXED(add->fixed), add->nameCompany_lab, 600, 70);
  gtk_fixed_put(GTK_FIXED(add->fixed), add->nameCompany_entry, 600, 90);
  gtk_fixed_put(GTK_FIXED(add->fixed), add->address_lab, 275, 140);
  gtk_fixed_put(GTK_FIXED(add->fixed), add->address_entry, 275, 160);
  gtk_fixed_put(GTK_FIXED(add->fixed), add->cp_lab, 600, 140);
  gtk_fixed_put(GTK_FIXED(add->fixed), add->cp_entry, 600, 160);
  gtk_fixed_put(GTK_FIXED(add->fixed), add->phone_lab, 275, 210);
  gtk_fixed_put(GTK_FIXED(add->fixed), add->phone_entry, 275, 230);
  gtk_fixed_put(GTK_FIXED(add->fixed), add->mphone_lab, 600, 210);
  gtk_fixed_put(GTK_FIXED(add->fixed), add->mphone_entry, 600, 230);
  gtk_fixed_put(GTK_FIXED(add->fixed), add->categorie_lab, 275, 280);
  gtk_fixed_put(GTK_FIXED(add->fixed), add->categorie_entry, 275, 300);
  gtk_fixed_put(GTK_FIXED(add->fixed), add->mail_lab, 600, 280);
  gtk_fixed_put(GTK_FIXED(add->fixed), add->mail_entry, 600, 300);
  gtk_fixed_put(GTK_FIXED(add->fixed), add->tarif_lab, 275, 350);
  gtk_fixed_put(GTK_FIXED(add->fixed), add->tarif_entry, 275, 370);
  gtk_fixed_put(GTK_FIXED(add->fixed), add->suplement_lab, 275, 420);
  gtk_fixed_put(GTK_FIXED(add->fixed), add->suplement_entry, 275, 440);
  gtk_fixed_put(GTK_FIXED(add->fixed), add->reccur_lab, 600, 350);
  gtk_fixed_put(GTK_FIXED(add->fixed), add->reccur_entry, 600, 370);
  gtk_fixed_put(GTK_FIXED(add->fixed), add->min_lab, 600, 420);
  gtk_fixed_put(GTK_FIXED(add->fixed), add->min_entry, 600, 440);
  gtk_container_add(GTK_CONTAINER(window), GTK_WIDGET(add->fixed));
}

void destroy_add(t_add *add)
{
  gtk_widget_destroy(add->min_lab);
  gtk_widget_destroy(add->min_entry);
  gtk_widget_destroy(add->reccur_lab);
  gtk_widget_destroy(add->reccur_entry);
  gtk_widget_destroy(add->mail_lab);
  gtk_widget_destroy(add->categorie_lab);
  gtk_widget_destroy(add->cp_lab);
  gtk_widget_destroy(add->nameCompany_lab);
  gtk_widget_destroy(add->suplement_lab);
  gtk_widget_destroy(add->tarif_lab);
  gtk_widget_destroy(add->address_lab);
  gtk_widget_destroy(add->mphone_lab);
  gtk_widget_destroy(add->phone_lab);
  gtk_widget_destroy(add->name_lab);
  gtk_widget_destroy(add->mail_entry);
  gtk_widget_destroy(add->categorie_entry);
  gtk_widget_destroy(add->cp_entry);
  gtk_widget_destroy(add->nameCompany_entry);
  gtk_widget_destroy(add->suplement_entry);
  gtk_widget_destroy(add->tarif_entry);
  gtk_widget_destroy(add->address_entry);
  gtk_widget_destroy(add->mphone_entry);
  gtk_widget_destroy(add->phone_entry);
  gtk_widget_destroy(add->name_entry);
  gtk_widget_destroy(add->btn_register);
  gtk_widget_destroy(add->btn_return);
  gtk_widget_destroy(add->title_lab);
  gtk_widget_destroy(add->img);
  gtk_widget_destroy(add->fixed);
  free(add);
  return ;
}
