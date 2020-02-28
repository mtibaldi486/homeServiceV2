/* **************************************************************************************** */
/*                                                                                          */
/*                                               :::::::::: ::::::::   ::::::::  :::::::::: */
/*   main.c                                      :+:       :+:        :+:   :+:     :+:     */
/*                                              +:+       +:+        +:+           +:+      */
/*   By: root <root@myges.fr>                  +#++:++#  +#++:++#++ :#:           +#+       */
/*                                            +#+              +#+ +#+  +#+#     +#+        */
/*   Created: 2020/02/25 15:42:14 by root    #+#              #+# #+#    #+     #+#         */
/*   Updated: 2020/02/27 13:23:57 by root   ##########  ########  ######## ###########      */
/*                                                                                          */
/* **************************************************************************************** */

#include "../inc/hs.h"

int   main(int ac , char **av)
{
  if (!(conf = malloc(sizeof(t_conf))))
    return 0;
  if (!(conf = load_conf()))
  {
    printf("failed to load_conf");
    create_conf();
    free(conf);
    return 0;
  }
  display_conf();
  /* Initialisation de GTK+ */
  gtk_init(&ac, &av);
  /* Création de la fenêtre */
  window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  g_signal_connect(G_OBJECT(window), "delete-event", G_CALLBACK(gtk_main_quit), NULL);
  /* Affichage et boucle évènementielle */
  if (!create_home())
    return (0);
  gtk_main();
  free_conf(conf);
  return (1);
}

void free_conf()
{
  free(conf->city);
  free(conf->ip_srv);
  free(conf->user_db);
  free(conf->name_db);
  free(conf->pass_db);
  free(conf);
}
