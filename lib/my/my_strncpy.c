/*
** my_strncpy.c for libdoom in /home/doumer_c/libmy
** 
** Made by clement doumergue
** Login   <doumer_c@epitech.net>
** 
** Started on  Wed Jan 27 22:55:34 2016 clement doumergue
** Last update Wed Feb 24 11:10:43 2016 clement doumergue
*/

#include <stdlib.h>

char	*my_strncpy(char *dest, const char *src, int n)
{
  int	i;

  if (src == NULL || dest == NULL)
    return (NULL);
  i = 0;
  while (i < n && src[i] != '\0')
    {
      dest[i] = src[i];
      i = i + 1;
    }
  while (i < n)
    {
      dest[i] = '\0';
      i = i + 1;
    }
  return (dest);
}
