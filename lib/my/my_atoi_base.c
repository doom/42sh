/*
** my_atoi_base.c for ex_4 in /home/exam/rendu/ex_4
** 
** Made by Exam User
** Login   <exam@epitech.net>
** 
** Started on  Tue Apr  5 17:00:16 2016 Exam User
** Last update Mon May  2 17:46:14 2016 clement doumergue
*/

#include <stdlib.h>
#include "my.h"

static int	index_of(char c, const char *str)
{
  int		i;

  i = 0;
  while (str[i] != '\0')
    {
      if (str[i] == c)
	return (i);
      i += 1;
    }
  return (0);
}

int	my_atoi_base(const char *str, const char *base)
{
  int	n;
  int	i;
  int	len;
  int	sign;

  if (str == NULL || base == NULL)
    return (0);
  sign = 1;
  while (*str == '-' || *str == '+')
    if (*str++ == '-')
      sign *= -1;
  len = my_strlen(base);
  n = 0;
  i = 0;
  while (str[i] != '\0')
    {
      n = n * (len * ((sign * n >= 0) ? 1 : sign));
      n = n + (index_of(str[i], base) * sign);
      i += 1;
    }
  return (n);
}

int	my_atoi(const char *str)
{
  return (my_atoi_base(str, "0123456789"));
}
