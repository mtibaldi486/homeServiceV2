/* ******************************************************************************************* */
/*                                                                                             */
/*                                                  :::::::::: ::::::::   :::::::: ::::::::::: */
/*   list_provider.c                                :+:       :+:        :+:    :+:    :+:     */
/*                                                 +:+       +:+        +:+           +:+      */
/*   By: mtibaldi <mtibaldi2@myges.fr>            +#++:++#  +#++:++#++ :#:           +#+       */
/*                                               +#+              +# ++#+  +#+#     +#+        */
/*   Created: 2019/10/13 23:01:47 by mtibaldi   #+#              #+# #+#    #+     #+#         */
/*   					                                 ########## ########   ######## ###########      */
/*                                                                                             */
/* ******************************************************************************************* */
#include "../inc/hs.h"

void create_list()
{
  t_list *list;

  if (!(list = malloc(sizeof(t_list))))
    return ;
  list->fixed = gtk_fixed_new();
  list->img = gtk_image_new_from_file("img/background2.PNG");
  list->title_lab = create_lab(list->title_lab, "Tout les prestataire :", 4);
  list->btn_return = gtk_button_new_with_label("Retour");
  list->scrollWindow = gtk_scrolled_window_new(NULL, NULL);
  gtk_widget_set_size_request (list->scrollWindow, 640, 425);
  list->viewport = gtk_viewport_new(NULL, NULL);
  list->comboList = gtk_list_box_new();
  display_combo_box(list);
  g_signal_connect(G_OBJECT(list->btn_return), "clicked", G_CALLBACK(list_to_menu), list);
  gtk_container_add(GTK_CONTAINER(list->viewport), GTK_WIDGET(list->comboList));
  gtk_container_add(GTK_CONTAINER(list->fixed), GTK_WIDGET(list->img));
  gtk_container_add(GTK_CONTAINER(list->scrollWindow), GTK_WIDGET(list->viewport));
  gtk_fixed_put(GTK_FIXED(list->fixed), list->title_lab, 400, 20);
  gtk_fixed_put(GTK_FIXED(list->fixed), list->scrollWindow, 240, 90);
  gtk_fixed_put(GTK_FIXED(list->fixed), list->btn_return, 1000, 20);
  gtk_container_add(GTK_CONTAINER(window), GTK_WIDGET(list->fixed));
  gtk_widget_show_all(window);
}

void display_combo_box(t_list *list)
{
  MYSQL         *con = NULL;
  MYSQL_RES     *result = NULL;
  MYSQL_ROW     row;

  if (!(con =mysql_init(con)))
  {
    fprintf(stderr, "mysql_init() failed in display_combo_box() in list_porvider.c\n");
    return ;
  }
  if (mysql_real_connect(con, conf->ip_srv, conf->user_db, conf->pass_db,
  conf->name_db, 0, NULL, 0) == NULL)
  {
    finish_with_error(con);
    return ;
  }
  if (mysql_query(con, "SELECT * FROM prestataire"))
  {
      finish_with_error(con);
      return ;
  }
  if (!(result = mysql_store_result(con)))
  {
    finish_with_error(con);
    return ;
  }
  while ((row = mysql_fetch_row(result)))
  {
      add_provider_box(row[0], row[1], row[2], row[3], list);
  }
  mysql_free_result(result);
  mysql_close(con);
  return ;
}

void  add_provider_box(char *id, char *name, char *add, char *cp, t_list *list)
{
  GtkWidget     *new_box;
  GtkWidget     *fixed;
  GtkWidget     *lab_name = NULL;
  GtkWidget     *lab_add = NULL;
  GtkWidget     *lab_delim;
  GtkWidget     *button;
  gchar         strName[42];
  char          strAdd[142];

  new_box = gtk_list_box_row_new();
  fixed = gtk_fixed_new();

  //Creation du bouton pour voir la page du cocktail
  button = gtk_button_new_with_label("Voir");
  gtk_widget_set_name (button, id);
  g_signal_connect(button, "clicked", G_CALLBACK(display_profil), list);

  sprintf(strName, "Prestataire : %s", name);
  sprintf(strAdd, "Adresse : %s\nCode Postal : %s", add, cp);

  lab_name = create_lab(lab_name, strName, 1);
  lab_add = create_lab(lab_add, strAdd, 1);
  lab_delim = gtk_label_new("     ___________________     ");

  gtk_fixed_put(GTK_FIXED(fixed), lab_name, 10, 10);
  gtk_fixed_put(GTK_FIXED(fixed), lab_add, 10, 50);
  gtk_fixed_put(GTK_FIXED(fixed), lab_delim, 250, 75);
  gtk_fixed_put(GTK_FIXED(fixed), button, 450, 40);

  gtk_container_add(GTK_CONTAINER(new_box), fixed);

  gtk_list_box_insert(GTK_LIST_BOX(list->comboList), new_box, 0);
  return ;
}

void display_profil(GtkButton *btn, gpointer data)
{
  const gchar *id;
  t_list *list;

  list = data;
  id = gtk_widget_get_name(GTK_WIDGET(btn));
  destroy_list(list);
  create_profil((char *)id);
  return ;
}

void list_to_menu(GtkButton *btn, gpointer data)
{
  t_list *list;

  (void)btn;
  list = data;
  destroy_list(list);
  create_menu();
  return ;
}

void destroy_list(t_list *list)
{
  gtk_widget_destroy(list->btn_return);
  gtk_widget_destroy(list->title_lab);
  gtk_widget_destroy(list->comboList);
  gtk_widget_destroy(list->viewport);
  gtk_widget_destroy(list->scrollWindow);
  gtk_widget_destroy(list->img);
  gtk_widget_destroy(list->fixed);
  free(list);
}
