/* **************************************************************************************** */
/*                                                                                          */
/*                                               :::::::::: ::::::::   ::::::::  :::::::::: */
/*   menu.c                                      :+:       :+:        :+:   :+:     :+:     */
/*                                              +:+       +:+        +:+           +:+      */
/*   By: root <root@myges.fr>                  +#++:++#  +#++:++#++ :#:           +#+       */
/*                                            +#+              +#+ +#+  +#+#     +#+        */
/*   Created: 2020/02/25 16:22:03 by root    #+#              #+# #+#    #+     #+#         */
/*   Updated: 2020/02/28 16:31:48 by root   ##########  ########  ######## ###########      */
/*                                                                                          */
/* **************************************************************************************** */
#include "../inc/hs.h"

void create_menu()
{
  t_menu *menu;

  if (!(menu = malloc(sizeof(t_menu))))
    return ;
  menu->fixed = gtk_fixed_new();
  menu->btn_add = gtk_button_new_with_label ("Ajouter un prestataire.");
  menu->btn_list = gtk_button_new_with_label ("Voir les prestataires.");
  menu->img = gtk_image_new_from_file("img/background.PNG");
  g_signal_connect(G_OBJECT(menu->btn_add), "clicked", G_CALLBACK(goto_add), menu);
  g_signal_connect(G_OBJECT(menu->btn_list), "clicked", G_CALLBACK(goto_list), menu);
  gtk_widget_set_size_request (menu->btn_add, 470, 75);
  gtk_widget_set_size_request (menu->btn_list, 470, 75);
  gtk_container_add(GTK_CONTAINER(menu->fixed), GTK_WIDGET(menu->img));
  gtk_fixed_put(GTK_FIXED(menu->fixed), menu->btn_add, 280, 360);
  gtk_fixed_put(GTK_FIXED(menu->fixed), menu->btn_list, 280, 260);
  gtk_container_add(GTK_CONTAINER(window), GTK_WIDGET(menu->fixed));
  gtk_widget_show_all(window);
  return ;
}

void  destroy_menu(t_menu *menu)
{
  gtk_widget_destroy(menu->btn_list);
  gtk_widget_destroy(menu->btn_add);
  gtk_widget_destroy(menu->img);
  gtk_widget_destroy(menu->fixed);
  free(menu);
  return ;
}

void goto_add(GtkButton *btn, gpointer data)
{
  t_menu *menu;

  (void)btn;
  menu = data;
  destroy_menu(menu);
  create_add();
  return ;
}

void goto_list(GtkButton *btn, gpointer data)
{
  t_menu *menu;

  (void)btn;
  menu = data;
  destroy_menu(menu);
  create_list();
  return ;
}
