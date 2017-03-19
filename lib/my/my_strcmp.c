/*
** my_strcmp.c for libdoom in /home/doumer_c/libmy
** 
** Made by clement doumergue
** Login   <doumer_c@epitech.net>
** 
** Started on  Wed Jan 27 23:14:18 2016 clement doumergue
** Last update Sat Mar 12 17:34:31 2016 clement doumergue
*/

#include <stdlib.h>

int	my_strcmp(const char *s1, const char *s2)
{
  int	i;

  if (s1 == NULL && s2 == NULL)
    return (1);
  else if (s1 == NULL || s2 == NULL)
    return (0);
  i = 0;
  while (s1[i] != '\0')
    {
      if (s1[i] != s2[i])
	return (s1[i] - s2[i]);
      i = i + 1;
    }
  if (s1[i] != s2[i])
    return (s1[i] - s2[i]);
  return (0);
}
