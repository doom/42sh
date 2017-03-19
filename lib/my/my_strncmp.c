/*
** my_strncmp.c for libdoom in /home/doumer_c/libmy
** 
** Made by clement doumergue
** Login   <doumer_c@epitech.net>
** 
** Started on  Wed Jan 27 23:19:02 2016 clement doumergue
** Last update Tue May 10 00:30:56 2016 clement doumergue
*/

#include <stdlib.h>

int	my_strncmp(char *s1, char *s2, int n)
{
  int	i;

  if (s1 == NULL && s2 == NULL)
    return (0);
  else if (s1 == NULL || s2 == NULL)
    return (1);
  i = 0;
  while (i < n && s1[i] != '\0')
    {
      if (s1[i] != s2[i])
	return (s1[i] - s2[i]);
      i = i + 1;
    }
  if (i < n)
    return (s1[i] - s2[i]);
  return (0);
}
