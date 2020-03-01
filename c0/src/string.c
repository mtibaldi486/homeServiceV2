/* **************************************************************************************** */
/*                                                                                          */
/*                                               :::::::::: ::::::::   ::::::::  :::::::::: */
/*   string.c                                    :+:       :+:        :+:   :+:     :+:     */
/*                                              +:+       +:+        +:+           +:+      */
/*   By: root <root@myges.fr>                  +#++:++#  +#++:++#++ :#:           +#+       */
/*                                            +#+              +#+ +#+  +#+#     +#+        */
/*   Created: 2020/02/25 16:22:46 by root    #+#              #+# #+#    #+     #+#         */
/*   Updated: 2020/02/29 11:56:56 by root   ##########  ########  ######## ###########      */
/*                                                                                          */
/* **************************************************************************************** */
#include "../inc/hs.h"

int check_text(const gchar *str)
{
  int i= 0;

  if (!*str)
    return 0;
  while (str[i])
  {
    if (!isupper(str[i]) && !islower(str[i]) && str[i] != ' ')
      return 0;
    i++;
  }
  return 1;
}

int check_address(const gchar *str)
{
  int i = 0;

  if (!*str)
    return 0;
  while (str[i])
  {
    if (str[i] != ' ' && !isalnum(str[i]))
      return 0;
    i++;
  }
  return 1;
}

int check_phone(const gchar *str)
{
  int i = 0;

  if (!*str)
    return 0;
  if (str[i] == '+')
    i++;
  while (str[i])
  {
    if (!(str[i] >= 48 && str[i] <= 57))
      return 0;
    i++;
  }
  return 1;
}

int check_num(const gchar *str)
{
  int i;

  i = 0;
  if (!*str)
    return 0;
  while (str[i])
  {
    if (!isdigit(str[i]))
      return (0);
    i++;
  }
  return (1);
}

int check_price(const gchar *str)
{
  int i = 0;

  if (!*str)
    return 0;
  while (str[i] && str[i] != '.')
  {
    if (!isdigit(str[i]))
      return 0;
    i++;
  }
  if (str[i] == '.')
    i++;
  while (str[i])
  {
    if (!isdigit(str[i]))
      return 0;
    i++;
  }
  return 1;
}
