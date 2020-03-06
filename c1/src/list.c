/* **************************************************************************************** */
/*                                                                                          */
/*                                               :::::::::: ::::::::   ::::::::  :::::::::: */
/*   list.c                                      :+:       :+:        :+:   :+:     :+:     */
/*                                              +:+       +:+        +:+           +:+      */
/*   By: root <root@myges.fr>                  +#++:++#  +#++:++#++ :#:           +#+       */
/*                                            +#+              +#+ +#+  +#+#     +#+        */
/*   Created: 2020/03/06 12:54:29 by root    #+#              #+# #+#    #+     #+#         */
/*   Updated: 2020/03/06 13:56:38 by root   ##########  ########  ######## ###########      */
/*                                                                                          */
/* **************************************************************************************** */

#include "../inc/fusion.h"

t_dir *lst_new(char *str, int id)
{
  t_dir *new;

  if (!(new = malloc(sizeof(t_dir))))
    return NULL;
  new->id = id;
  new->path = strdup(str);
  new->next = NULL;
  return  new;
}

void	lstadd_back(t_dir **alst, t_dir *new)
{
	t_dir		*begin;

	if (!(alst && new))
		return ;
	begin = *alst;
	if (!begin)
    *alst = new;
	else
	{
		while (begin->next)
			begin = begin->next;
		begin->next = new;
	}
  return ;
}

void display_list(t_dir *start)
{
  t_dir *lst;

  lst = start;
  if (lst)
    while (lst)
    {
      printf("id = %d || str = %s\n", lst->id , lst->path);
      lst = lst->next;
    }
}
