/* **************************************************************************************** */
/*                                                                                          */
/*                                               :::::::::: ::::::::   ::::::::  :::::::::: */
/*   add_form_process.c                          :+:       :+:        :+:   :+:     :+:     */
/*                                              +:+       +:+        +:+           +:+      */
/*   By: root <root@myges.fr>                  +#++:++#  +#++:++#++ :#:           +#+       */
/*                                            +#+              +#+ +#+  +#+#     +#+        */
/*   Created: 2020/02/25 16:21:49 by root    #+#              #+# #+#    #+     #+#         */
/*   Updated: 2020/03/02 22:44:10 by root   ##########  ########  ######## ###########      */
/*                                                                                          */
/* **************************************************************************************** */

#include "../inc/hs.h"

t_input *collect_input(t_add *add)
{
  t_input *input = NULL;

  if (!(input = init_input(input)))
  return (NULL);
  load_input(add, input);
  if (check_input(input))
  {
    check_error_add(check_input(input), add);
    free(input);
    return (NULL);
  }
  return (input);
}

t_input   *init_input(t_input *input)
{
  if (!(input = malloc(sizeof(t_input))))
    return (NULL);
  input->name = NULL;
  input->fixe_phone = NULL;
  input->mobil_phone = NULL;
  input->address = NULL;
  input->url_qr = NULL;
  input->tarif = NULL ;
  input->suplement = NULL;
  input->company_name = NULL;
  input->cp = NULL;
  input->categorie = NULL;
  input->mail = NULL;
  return (input);
}

void   load_input(t_add *add, t_input *input)
{
  input->name = gtk_entry_get_text (GTK_ENTRY(add->name_entry));
  input->fixe_phone = gtk_entry_get_text (GTK_ENTRY(add->phone_entry));
  input->mobil_phone = gtk_entry_get_text (GTK_ENTRY(add->mphone_entry));
  input->address = gtk_entry_get_text (GTK_ENTRY(add->address_entry));
  input->tarif = gtk_entry_get_text (GTK_ENTRY(add->tarif_entry));
  input->suplement = gtk_entry_get_text (GTK_ENTRY(add->suplement_entry));
  input->company_name = gtk_entry_get_text (GTK_ENTRY(add->nameCompany_entry));
  input->cp = gtk_entry_get_text (GTK_ENTRY(add->cp_entry));
  input->categorie = gtk_combo_box_text_get_active_text(GTK_COMBO_BOX_TEXT(add->categorie_entry));
  input->mail = gtk_entry_get_text (GTK_ENTRY(add->mail_entry));
  return ;
}

char   *check_input(t_input *input)
{
  if (!check_text(input->name))
    return ("nom");
  if (!check_phone(input->fixe_phone))
    return ("fixe");
  if (!check_phone(input->mobil_phone))
    return ("mobile");
  if (!check_address(input->address))
    return ("adresse");
  if (!check_num(input->cp))
    return ("CP");
  if (!check_price(input->tarif))
    return ("prix/heure");
  if (!check_text(input->company_name))
    return ("Nom entreprise");
  if (!check_text(input->categorie))
    return ("Categorie");
  if (!check_text(input->mail))
    return ("Mail");
  return NULL;
}

void check_error_add(char *error, t_add *add)
{
  char str[70];

  if (add->lab_error)
    gtk_widget_destroy(add->lab_error);
  strcpy(str, error);
  if (strstr(error, "nom") || strstr(error, "adresse") || strstr(error, "Nom entreprise") || strstr(error, "Categorie") || strstr(error, "Mail"))
  {
    strcat(str, " doit etre uniquement composé de lettre ou d'espace");
    add->lab_error = create_lab(add->lab_error, str, 1);
    gtk_fixed_put(GTK_FIXED(add->fixed), add->lab_error, 240, 480);
  }
  else if (strstr(error, "mobile") || strstr(error, "fixe"))
  {
    strcat(str, " n'est pas valide");
    add->lab_error = create_lab(add->lab_error, str, 1);
    gtk_fixed_put(GTK_FIXED(add->fixed), add->lab_error, 240, 480);
  }
  else if (strstr(error, "prix/heure"))
  {
    strcat(str, " doit etre sous le format 00.00");
    add->lab_error = create_lab(add->lab_error, str, 1);
    gtk_fixed_put(GTK_FIXED(add->fixed), add->lab_error, 240, 480);
  }
  else if (strstr(error, "CP"))
  {
    strcat(str, " doit contenir uniquement des chiffres");
    add->lab_error = create_lab(add->lab_error, str, 1);
    gtk_fixed_put(GTK_FIXED(add->fixed), add->lab_error, 240, 480);
  }
  gtk_widget_show_all(window);
  return ;
}

void  display_input(t_input *input)
{
  printf("name = %s\nfixe phone = %s\nmobile = %s\naddress = %s\nurl qr = %s\n%s\n%s\n%s\n%s\n%s\n%s\n",input->name, input->fixe_phone, input->mobil_phone, input->address, input->url_qr, input->tarif, input->suplement, input->company_name, input->cp, input->categorie, input->mail);
  return ;
}
