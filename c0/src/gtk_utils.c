/* **************************************************************************************** */
/*                                                                                          */
/*                                               :::::::::: ::::::::   ::::::::  :::::::::: */
/*   gtk_utils.c                                 :+:       :+:        :+:   :+:     :+:     */
/*                                              +:+       +:+        +:+           +:+      */
/*   By: root <root@myges.fr>                  +#++:++#  +#++:++#++ :#:           +#+       */
/*                                            +#+              +#+ +#+  +#+#     +#+        */
/*   Created: 2020/02/25 16:22:35 by root    #+#              #+# #+#    #+     #+#         */
/*   Updated: 2020/03/01 23:40:53 by root   ##########  ########  ######## ###########      */
/*                                                                                          */
/* **************************************************************************************** */
#include "../inc/hs.h"

GtkWidget *create_lab(GtkWidget *lab, char *str, int size)
{
  gchar tmp[300];
  gchar *res;

  if (size < 1 && size > 4 && !str)
    return (NULL);
  if (size == 1)
    sprintf(tmp, "<span face=\"Verdana\" foreground=\"#000000\" size=\"small\"><b>%s</b></span>\n", str);
  else if (size == 2)
    sprintf(tmp, "<span face=\"Verdana\" underline=\"double\"foreground=\"#000000\" size=\"large\"><b>%s</b></span>\n", str);
  else if (size == 3)
    sprintf(tmp, "<span face=\"Verdana\" underline=\"double\"foreground=\"#000000\" size=\"x-large\"><b>%s</b></span>\n", str);
  else if (size == 4)
    sprintf(tmp, "<span face=\"Verdana\" underline=\"double\"foreground=\"#000000\" size=\"xx-large\"><b>%s</b></span>\n", str);

  res = g_locale_to_utf8(tmp, -1, NULL, NULL, NULL);  //Convertion du texte avec les balises
  lab = gtk_label_new(res); // Application de la convertion à notre label
  g_free(res); // Libération de la mémoire
  gtk_label_set_use_markup(GTK_LABEL(lab), TRUE); // On dit que l'on utilise les balises pango
  gtk_label_set_justify(GTK_LABEL(lab), GTK_JUSTIFY_CENTER); // On centre notre texte
  return lab;
}
