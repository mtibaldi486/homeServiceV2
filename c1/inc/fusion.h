/* **************************************************************************************** */
/*                                                                                          */
/*                                               :::::::::: ::::::::   ::::::::  :::::::::: */
/*   fusion.h                                    :+:       :+:        :+:   :+:     :+:     */
/*                                              +:+       +:+        +:+           +:+      */
/*   By: root <root@myges.fr>                  +#++:++#  +#++:++#++ :#:           +#+       */
/*                                            +#+              +#+ +#+  +#+#     +#+        */
/*   Created: 2020/03/03 22:42:00 by root    #+#              #+# #+#    #+     #+#         */
/*   Updated: 2020/03/29 21:49:05 by root   ##########  ########  ######## ###########      */
/*                                                                                          */
/* **************************************************************************************** */

#ifndef _FUSION_H
# define _FUSION_H

#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

typedef struct s_conf
{
  char *ip_srv;
  char *name_db;
  char *user_db;
  char *pass_db;
}             t_conf;

typedef struct s_dir
{
  char          *path;
  struct s_dir *next;
}              t_dir;

//MAIN_C
int   select_dir(t_dir **start);
int   open_dir(char *path, t_dir **start);

//LIST_C
t_dir *lst_new(char *str);
t_dir *lstdelone(t_dir *dir, t_dir **start);
void	lstadd_back(t_dir **alst, t_dir *new);
void dellist(t_dir **start);
void display_list(t_dir *start);

//MERGE_C
void merge(t_dir *start,  char *path, t_conf *conf);
int import_dump(char *path_dump, char *path_log, t_conf *conf);
void create_path_log(char *path_log, char *path);
void check_errors(char *path_log);

//SETUP_C
t_conf *load_conf();
char *parse_line(char *str, int *counter);
int  check_conf(t_conf *conf);
void create_conf(void);
void free_conf(t_conf *conf);
void display_conf(t_conf *conf);


//UTILS_C
int get_input(char *input, int size);
int check_input_choice(char *str);

#endif
