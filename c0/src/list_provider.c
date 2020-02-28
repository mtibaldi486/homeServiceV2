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
  /*
    ICI requete bdd (select * from prestatataire),
     création des box, insertion des box,
    connection btn vers page de CREATE_PROFIL_C
  */
  return ;
}

void list_to_menu(GtkButton *btn, gpointer data)
{
  t_list *list;

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
