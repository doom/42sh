/*
** my_memset.c for libmy in /home/doumer_c/rendu/PSU_2015_minishell2
** 
** Made by clement doumergue
** Login   <doumer_c@epitech.net>
** 
** Started on  Sun Apr  3 14:58:27 2016 clement doumergue
** Last update Mon Apr  4 13:56:23 2016 clement doumergue
*/

#include <stdlib.h>
#include "my.h"

void	*my_memset(void *ptr, int c, int n)
{
  int	i;
  char	*octs;

  if (ptr == NULL)
    return (NULL);
  octs = ptr;
  i = 0;
  while (i < n)
    octs[i++] = c;
  return (ptr);
}
