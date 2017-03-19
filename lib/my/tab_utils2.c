/*
** tab_utils2.c for libmy in /home/doumer_c/rendu/PSU_2015_tetris
** 
** Made by clement doumergue
** Login   <doumer_c@epitech.net>
** 
** Started on  Sat Mar 19 16:56:13 2016 clement doumergue
** Last update Mon Mar 21 14:19:55 2016 clement doumergue
*/

#include <stdlib.h>
#include "my.h"

bool	contains_str(char **tab, int size, const char *str)
{
  int	i;

  if (tab == NULL)
    return (0);
  i = 0;
  while (i < size)
    {
      if (my_strcmp(tab[i], str) == 0)
	return (true);
      i += 1;
    }
  return (false);
}
