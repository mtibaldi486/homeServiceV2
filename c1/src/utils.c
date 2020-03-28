/* **************************************************************************************** */
/*                                                                                          */
/*                                               :::::::::: ::::::::   ::::::::  :::::::::: */
/*   utils.c                                     :+:       :+:        :+:   :+:     :+:     */
/*                                              +:+       +:+        +:+           +:+      */
/*   By: root <root@myges.fr>                  +#++:++#  +#++:++#++ :#:           +#+       */
/*                                            +#+              +#+ +#+  +#+#     +#+        */
/*   Created: 2020/03/03 22:38:19 by root    #+#              #+# #+#    #+     #+#         */
/*   Updated: 2020/03/06 16:07:41 by root   ##########  ########  ######## ###########      */
/*                                                                                          */
/* **************************************************************************************** */

#include "../inc/fusion.h"

int get_input(char *input, int size)
{
  if (!input && size <= 0)
    return 0;
  fgets(input, size, stdin);
  if (input[strlen(input) - 1] == '\n')
    input[strlen(input) - 1] = '\0';
  return 1;
}

int check_input_choice(char *str)
{
  int i = 0;

  while (str[i])
  {
    if (!isdigit(str[i]) && str[i] != ',')
      return 0;
    i++;
  }
  return 1;
}
