/*
** my_strcpy.c for libdoom in /home/doumer_c/libmy
** 
** Made by clement doumergue
** Login   <doumer_c@epitech.net>
** 
** Started on  Wed Jan 27 23:08:59 2016 clement doumergue
** Last update Wed Feb 24 11:10:50 2016 clement doumergue
*/

#include <stdlib.h>

char	*my_strcpy(char *dest, const char *src)
{
  int	i;

  if (src == NULL || dest == NULL)
    return (NULL);
  i = 0;
  while (src[i] != '\0')
    {
      dest[i] = src[i];
      i = i + 1;
    }
  dest[i] = '\0';
  return (dest);
}
