/*
** is_empty.c for libmy in /home/doumer_c/rendu/PSU_2015_minishell2
** 
** Made by clement doumergue
** Login   <doumer_c@epitech.net>
** 
** Started on  Fri Apr  8 12:11:27 2016 clement doumergue
** Last update Sun Jun  5 21:28:43 2016 clement doumergue
*/

#include "my.h"

char	*skip_blank(char *str)
{
  if (!str)
    return (str);
  while (IS_SEP(*str) && *str != '\0')
    str += 1;
  return (str);
}

char	*cut_end(char *str)
{
  int	i;

  i = 0;
  while (str[i] != '\0' && !IS_SEP(str[i]))
    i += 1;
  str[i] = '\0';
  return (str);
}

bool	is_empty(const char *str)
{
  int	i;

  i = 0;
  while (str[i] != '\0')
    {
      if (!IS_SEP(str[i]))
	return (false);
      i += 1;
    }
  return (true);
}
