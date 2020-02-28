/* **************************************************************************************** */
/*                                                                                          */
/*                                               :::::::::: ::::::::   ::::::::  :::::::::: */
/*   hs.h                                        :+:       :+:        :+:   :+:     :+:     */
/*                                              +:+       +:+        +:+           +:+      */
/*   By: root <root@myges.fr>                  +#++:++#  +#++:++#++ :#:           +#+       */
/*                                            +#+              +#+ +#+  +#+#     +#+        */
/*   Created: 2020/02/25 16:22:10 by root    #+#              #+# #+#    #+     #+#         */
/*   Updated: 2020/02/28 09:45:18 by root   ##########  ########  ######## ###########      */
/*                                                                                          */
/* **************************************************************************************** */
#ifndef HS_H
#define HS_H

//#include <gtk/gtkx.h>
#include "gtk/gtk.h"
#include <string.h>
#include <qrencode.h>
#include <mysql.h>
#include <ctype.h>

#include <unistd.h>

typedef struct s_conf
{
  char *ip_srv;
  char *name_db;
  char *user_db;
  char *pass_db;
  char *city;
}             t_conf;

typedef struct s_home
{
  GtkWidget *fixed;
  GtkWidget *btn;
  GtkWidget *img;
  GtkWidget *label;
}              t_home;

typedef struct s_menu
{
  GtkWidget *fixed;
  GtkWidget *img;
  GtkWidget *btn_add;
  GtkWidget *btn_list;
}              t_menu;

typedef struct s_add
{
  GtkWidget *fixed;
  GtkWidget *img;
  GtkWidget *title_lab;
  GtkWidget *btn_return;
  GtkWidget *btn_register;

  GtkWidget *lab_error;
  //toute les entrer de la page add.c
  GtkWidget *name_entry;
  GtkWidget *phone_entry;
  GtkWidget *mphone_entry;
  GtkWidget *address_entry;
  GtkWidget *tarif_entry;
  GtkWidget *suplement_entry;
  GtkWidget *nameCompany_entry;
  GtkWidget *cp_entry;
  GtkWidget *categorie_entry;
  GtkWidget *mail_entry;

  GtkWidget *name_lab;
  GtkWidget *phone_lab;
  GtkWidget *mphone_lab;
  GtkWidget *address_lab;
  GtkWidget *tarif_lab;
  GtkWidget *suplement_lab;
  GtkWidget *nameCompany_lab;
  GtkWidget *cp_lab;
  GtkWidget *categorie_lab;
  GtkWidget *mail_lab;
}               t_add;

typedef struct s_input
{
  const gchar *name;
  const gchar *fixe_phone;
  const gchar *mobil_phone;
  const gchar *address;
  const gchar *url_qr; // envoyer le param
  const gchar *tarif;
  const gchar *suplement;
  const gchar *city;
  const gchar *company_name; //PAs oublié de le recup
  const gchar *cp;
  const gchar *categorie;
  const gchar *mail;
}              t_input;

typedef struct s_list
{
  GtkWidget *fixed;
  GtkWidget *img;
  GtkWidget *scrollWindow;
  GtkWidget *viewport;
  GtkWidget *comboList;
  GtkWidget *title_lab;
  GtkWidget *btn_return;
}              t_list;

typedef struct s_profil
{
  GtkWidget *fixed;
  GtkWidget *img;
  GtkWidget *title_lab;
  GtkWidget *btn_return;

  GtkWidget *id;
  GtkWidget *tel_mobil;
  GtkWidget *tel_fixe;
  GtkWidget *address;
  GtkWidget *cp;
  GtkWidget *img_qr;
  GtkWidget *salary;
  GtkWidget *supplement;
  GtkWidget *name_company;
  GtkWidget *category;
  GtkWidget *mail;
  GtkWidget *reccurent;
  GtkWidget *reduce_price;
}              t_profil;

typedef struct s_data_profil
{
  char id[42];
  char name[42];
  char tel_mobil[42];
  char tel_fixe[42];
  char address[42];
  char cp[42];
  char path_qr[42];
  char salary[42];
  char supplement[42];
  char name_company[42];
  char category[42];
  char mail[42];
  char reccurent[42];
  char reduce_price[42];
}              t_data_profil;

////////////////////////A SUPPRIMER///////////
void display_conf(); //configuration.c
void  display_input(t_input *input); //add_form_process.c

/////GLOBAL_C///////
GtkWidget *window;
t_conf    *conf;

///////MAIN_C////////
void free_conf();

//////CONFIGURATION_C///////
t_conf *load_conf(void);
char *parse_line(char *str, int *counter);
int  check_conf();
void create_conf(void);

///////HOME_C///////
int   create_home();
void create_label_home(char *str);
void  destroy_home(t_home *home);
void  goto_menu(GtkButton *btn, gpointer data);

/////MENU_C/////////
void create_menu();
void  destroy_menu(t_menu *menu);
void goto_add(GtkButton *btn, gpointer data);
void goto_list(GtkButton *btn, gpointer data);

//////ADD_C////////
void create_add();
void register_provider(GtkButton *btn, gpointer data);
GtkWidget *create_combo_box();
void add_to_profil(t_add *add);
void add_to_menu(GtkButton *btn, gpointer data);
void create_widget_add(t_add *add);
void put_widget_add(t_add *add);
void destroy_add(t_add *add);

////ADD_FORM_PROCESS//////////////
t_input *collect_input(t_add *add);
t_input   *init_input(t_input *input);
void   load_input(t_add *add, t_input *input);
char   *check_input(t_input *input);
void check_error_add(char *error, t_add *add);

/////LIST_PROVIDER_C//////////
void create_list();
void list_to_menu(GtkButton *btn, gpointer data);
void display_combo_box(t_list *list);
void destroy_list(t_list *list);

/////QRCODE_C////////////////
void make_qr(t_input *input);
char *recup_last_id();

/////ADD_MYSQL_C///////////
int   insert_presta_bdd(t_input *input);
void check_categorie(MYSQL *con, t_input *input);
void  finish_with_error(MYSQL *con);

////////PROFIL_C/////////////
void            create_profil(char *id);
t_data_profil   *select_user(char *id, t_data_profil *data);
void            profil_to_list(GtkButton *btn, gpointer data);
void            destroy_profil(t_profil *profil);

/////GTK_UTILS_C///////
GtkWidget *create_lab(GtkWidget *lab, char *str, int size);

/////////STRING_C////////////
int check_text(const gchar *str);
int check_num(const gchar *str);
int check_phone(const gchar *str);
int check_price(const gchar *str);

#endif
