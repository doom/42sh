/*
** get_str_pos.c for libmy in /home/doumer_c/rendu/PSU_2015_minishell2
** 
** Made by clement doumergue
** Login   <doumer_c@epitech.net>
** 
** Started on  Sun Apr  3 14:43:33 2016 clement doumergue
** Last update Sun Jun  5 21:26:17 2016 clement doumergue
*/

#include "my.h"

int	get_str_pos(const char *str, const char *to_find)
{
  int	i;
  int	len;

  if ((len = my_strlen(to_find)) > my_strlen(str))
    return (-1);
  i = 0;
  while (str[i + len - 1] != '\0')
    {
      if (my_strncmp(str + i, to_find, len) == 0)
	return (i);
      i += 1;
    }
  return (-1);
}

int	get_last_pos(const char *str, const char *to_find)
{
  int	i;
  int	len;
  int	slen;

  if ((len = my_strlen(to_find)) > (slen = my_strlen(str)))
    return (-1);
  i = slen - 1;
  while (i >= 0)
    {
      if (str[i] == '"')
	{
	  i -= 1;
	  while (str[i] != '"' && i)
	    i -= 1;
	  if (i == 0)
	    return (-1);
	}
      if (my_strncmp(str + i, to_find, len) == 0)
	return (i);
      i -= 1;
    }
  return (-1);
}
