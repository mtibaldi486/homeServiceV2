/* **************************************************************************************** */
/*                                                                                          */
/*                                               :::::::::: ::::::::   ::::::::  :::::::::: */
/*   fusion.h                                    :+:       :+:        :+:   :+:     :+:     */
/*                                              +:+       +:+        +:+           +:+      */
/*   By: root <root@myges.fr>                  +#++:++#  +#++:++#++ :#:           +#+       */
/*                                            +#+              +#+ +#+  +#+#     +#+        */
/*   Created: 2020/03/03 22:42:00 by root    #+#              #+# #+#    #+     #+#         */
/*   Updated: 2020/03/28 16:13:41 by root   ##########  ########  ######## ###########      */
/*                                                                                          */
/* **************************************************************************************** */

#ifndef _FUSION_H
# define _FUSION_H

#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>

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
void display_list(t_dir *start);


//UTILS_C
int get_input(char *input, int size);
int check_input_choice(char *str);

#endif
