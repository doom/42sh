/*
** my_strndup.c for tetris in /home/doumer_c/rendu/PSU_2015_tetris
** 
** Made by clement doumergue
** Login   <doumer_c@epitech.net>
** 
** Started on  Wed Feb 24 09:56:59 2016 clement doumergue
** Last update Fri Mar 18 13:16:20 2016 clement doumergue
*/

#include <stdlib.h>
#include "my.h"

char	*my_strndup(const char *str, int len)
{
  char	*new;

  if (str == NULL)
    return (NULL);
  if ((new = my_xmalloc(sizeof(*new) * (len + 1))) == NULL)
    return (NULL);
  my_strncpy(new, str, len);
  new[len] = '\0';
  return (new);
}

char	*my_strdup(const char *str)
{
  return (my_strndup(str, my_strlen(str)));
}
