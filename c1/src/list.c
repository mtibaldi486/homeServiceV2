/* **************************************************************************************** */
/*                                                                                          */
/*                                               :::::::::: ::::::::   ::::::::  :::::::::: */
/*   list.c                                      :+:       :+:        :+:   :+:     :+:     */
/*                                              +:+       +:+        +:+           +:+      */
/*   By: root <root@myges.fr>                  +#++:++#  +#++:++#++ :#:           +#+       */
/*                                            +#+              +#+ +#+  +#+#     +#+        */
/*   Created: 2020/03/06 12:54:29 by root    #+#              #+# #+#    #+     #+#         */
/*   Updated: 2020/03/28 16:25:30 by root   ##########  ########  ######## ###########      */
/*                                                                                          */
/* **************************************************************************************** */

#include "../inc/fusion.h"

t_dir *lst_new(char *str)
{
  t_dir *new;

  if (!(new = malloc(sizeof(t_dir))))
    return NULL;
  new->path = strdup(str);
  new->next = NULL;
  return  new;
}

t_dir *lstdelone(t_dir *lst, t_dir **start)
{
  t_dir *begin = *start;
  t_dir *before = begin;

  if (lst == begin)
  {
    *start = begin->next;
    free(begin->path);
    free(begin);
    return(*start);
  }
  while(begin)
  {
    if (lst == begin)
    {
      if (lst->next)
        before->next = lst->next;
      else
        before->next = NULL;
      free(lst->path);
      free(lst);
      return before;
    }
    before = begin;
    begin = begin->next;
  }
  return (0);
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
      printf("list str = %s\n", lst->path);
      lst = lst->next;
    }
}
