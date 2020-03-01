/* **************************************************************************************** */
/*                                                                                          */
/*                                               :::::::::: ::::::::   ::::::::  :::::::::: */
/*   home.c                                      :+:       :+:        :+:   :+:     :+:     */
/*                                              +:+       +:+        +:+           +:+      */
/*   By: root <root@myges.fr>                  +#++:++#  +#++:++#++ :#:           +#+       */
/*                                            +#+              +#+ +#+  +#+#     +#+        */
/*   Created: 2020/02/25 16:22:39 by root    #+#              #+# #+#    #+     #+#         */
/*   Updated: 2020/02/28 16:04:13 by root   ##########  ########  ######## ###########      */
/*                                                                                          */
/* **************************************************************************************** */
#include "../inc/hs.h"

int   create_home()
{
  t_home *home;
  char   label[42];

  if (!(home = malloc(sizeof(t_home))))
    return (0);
  create_label_home(label);
  home->fixed = gtk_fixed_new();
  home->btn = gtk_button_new();
  home->img = gtk_image_new_from_file("img/background.PNG");
  home->label = create_lab(home->label, label, 3);
  g_signal_connect(G_OBJECT(home->btn), "clicked", G_CALLBACK(goto_menu), home);
  gtk_container_add(GTK_CONTAINER(home->btn), GTK_WIDGET(home->img));
  gtk_container_add(GTK_CONTAINER(home->fixed), GTK_WIDGET(home->btn));
  gtk_container_add(GTK_CONTAINER(window), GTK_WIDGET(home->fixed));
  gtk_fixed_put(GTK_FIXED(home->fixed), home->label, 450, 350);
  gtk_widget_show_all(window);
  return (1);
}

void create_label_home(char *str)
{
  strcpy(str, "Ville : ");
  strcat(str, conf->city);
  return ;
}

void  destroy_home(t_home *home)
{
  gtk_widget_destroy(home->img);
  gtk_widget_destroy(home->btn);
  gtk_widget_destroy(home->fixed);
  free(home);
  return ;
}

void goto_menu(GtkButton *btn, gpointer data)
{
  t_home *home;

  (void)btn;
  home = data;
  destroy_home(home);
  create_menu();
  return ;
}
