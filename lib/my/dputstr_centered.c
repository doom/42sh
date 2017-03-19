/*
** dputstr_centered.c for libmy in /home/doumer_c/rendu/PSU_2015_42sh/
**
** Made by clement doumergue
** Login   <doumer_c@epitech.net>
**
** Started on  Thu May  5 01:38:37 2016 clement doumergue
** Last update Sun Jun  5 21:29:51 2016 clement doumergue
*/

#include <unistd.h>
#include "my.h"

void	dputstr_centered(__attribute__((unused))int fd,
			 const char *str, int size)
{
  int	i;
  int	len;

  len = my_strlen(str);
  if (size < len)
    return ;
  i = 0;
  while (i++ < (size - len) / 2)
    write(1, " ", 1);
  i += write(1, str, len);
  while (i++ < size)
    write(1, " ", 1);
}

void	dputstr_left(__attribute__((unused))int fd,
		     const char *str, int size)
{
  int	len;

  len = my_strlen(str);
  if (size < len)
    return ;
  size -= write(1, str, len);
  while (size--)
    write(1, " ", 1);
}
