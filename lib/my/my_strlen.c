/*
** my_strlen.c for libdoom in /home/doumer_c/libmy
**
** Made by clement doumergue
** Login   <doumer_c@epitech.net>
**
** Started on  Wed Jan 27 23:00:01 2016 clement doumergue
** Last update Wed Jun  1 13:51:59 2016 szterg_r
*/

#include <stdlib.h>

int	my_strlen(const char *str)
{
  int	i;

  if (str == NULL)
    return (0);
  i = 0;
  while (str[i] != '\0')
    i = i + 1;
  return (i);
}
