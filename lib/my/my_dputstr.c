/*
** my_dputstr.c for libdoom in /home/doumer_c/libmy
** 
** Made by clement doumergue
** Login   <doumer_c@epitech.net>
** 
** Started on  Wed Jan 27 22:13:21 2016 clement doumergue
** Last update Thu Jan 28 00:14:28 2016 clement doumergue
*/

#include "my_dprintf.h"

int	my_dputstr(int fd, const char *str)
{
  int	i;

  i = 0;
  while (str[i] != '\0')
    my_dputchar(fd, str[i++]);
  return (i);
}
