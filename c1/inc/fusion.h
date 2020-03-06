/* **************************************************************************************** */
/*                                                                                          */
/*                                               :::::::::: ::::::::   ::::::::  :::::::::: */
/*   fusion.h                                    :+:       :+:        :+:   :+:     :+:     */
/*                                              +:+       +:+        +:+           +:+      */
/*   By: root <root@myges.fr>                  +#++:++#  +#++:++#++ :#:           +#+       */
/*                                            +#+              +#+ +#+  +#+#     +#+        */
/*   Created: 2020/03/03 22:42:00 by root    #+#              #+# #+#    #+     #+#         */
/*   Updated: 2020/03/06 13:38:08 by root   ##########  ########  ######## ###########      */
/*                                                                                          */
/* **************************************************************************************** */

#ifndef _FUSION_H
# define _FUSION_H

#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct s_dir
{
  int           id;
  char          *path;
  struct s_dir *next;
}              t_dir;

//MAIN_C
int   select_dir(char **dir);
int   show_dir(char *path);
void  display_dir(char **strs);
void  free_dir_backup(char **strs);
int   check_input_choice(char *input);
int   parse_input(char *input, int *choice);
int   substrmt(char *start, char *end, int *res);


//LIST_C
t_dir *lst_new(char *str, int id);
void	lstadd_back(t_dir **alst, t_dir *new);
void display_list(t_dir *start);


//UTILS_C
int get_input(char *input, int size);

#endif
