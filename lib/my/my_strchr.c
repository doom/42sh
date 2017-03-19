/*
** my_strchr.c for libmy in /home/doumer_c/rendu/PSU_2015_minishell2
** 
** Made by clement doumergue
** Login   <doumer_c@epitech.net>
** 
** Started on  Mon Mar 21 16:09:01 2016 clement doumergue
** Last update Tue May 17 14:23:21 2016 clement doumergue
*/

#include "my.h"

int	get_char_pos(const char *str, char c)
{
  int	i;

  i = 0;
  while (str[i] != '\0' && str[i] != c)
    i += 1;
  return ((str[i] != '\0') ? i : -1);
}

int	get_last_char(const char *str, char c)
{
  int	i;

  i = my_strlen(str) - 1;
  while (i >= 0 && str[i] != c)
    i -= 1;
  return (i);
}

char	*my_strchr(const char *str, char c)
{
  while (*str != c)
    str++;
  return ((char *)str);
}
