/*
** my_strstr.c for strstr in /home/szterg_r/Final_lib/Library/srcs
**
** Made by
** Login   <szterg_r@epitech.net>
**
** Started on  Sun Dec  6 18:31:31 2015
** Last update Fri May  6 14:12:03 2016 clement doumergue
*/

#include <stddef.h>

char	*my_strstr(const char *str, const char *to_find)
{
  int	i;
  int	count;

  if (!str || !to_find)
    return (NULL);
  i = 0;
  count = 0;
  while (str[i])
    {
      count = (str[i] == to_find[count]) ? count + 1 : 0;
      if (!to_find[count])
	{
	  i = i - (count - 1);
	  return ((char *)str + i);
	}
      i += 1;
    }
  return (NULL);
}
