/*
** dputstuff_ter.c for libdoom in /home/doumer_c/libmy
** 
** Made by clement doumergue
** Login   <doumer_c@epitech.net>
** 
** Started on  Wed Jan 27 22:18:46 2016 clement doumergue
** Last update Wed Feb 10 11:20:50 2016 clement doumergue
*/

#include "my_dprintf.h"

int		dput_float(int fd, va_list ap, int opt)
{
  double	f;
  int		offset;

  offset = 0;
  f = va_arg(ap, double);
  if (opt == 1 && f > 0)
    offset = my_dputchar(fd, '+');
  return (my_dput_float(fd, f, 1000000) + offset);
}
