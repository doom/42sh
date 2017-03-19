/*
** dputstuff.c for libdoom in /home/doumer_c/libmy
** 
** Made by clement doumergue
** Login   <doumer_c@epitech.net>
** 
** Started on  Wed Jan 27 22:19:15 2016 clement doumergue
** Last update Thu Jan 28 00:20:31 2016 clement doumergue
*/

#include <stdlib.h>
#include "my_dprintf.h"

int	dput_char(int fd, va_list ap, int opt)
{
  char	c;

  (void)opt;
  c = va_arg(ap, int);
  my_dputchar(fd, c);
  return (1);
}

int	dput_string(int fd, va_list ap, int opt)
{
  char	*str;

  (void)opt;
  str = va_arg(ap, char *);
  if (str != NULL)
    return (my_dputstr(fd, str));
  my_dputstr(fd, "(null)");
  return (6);
}

int	dput_int(int fd, va_list ap, int opt)
{
  int	n;
  int	offset;

  offset = 0;
  n = va_arg(ap, int);
  if (opt == 1 && n >= 0)
    offset = my_dputchar(fd, '+');
  else if (opt == 2 && n >= 0)
    offset = my_dputchar(fd, ' ');
  return (my_dput_nbr(fd, n) + offset);
}

int		dput_maj_hex(int fd, va_list ap, int opt)
{
  unsigned int	n;
  int		offset;

  offset = 0;
  n = va_arg(ap, unsigned int);
  if (opt == 0)
    offset = my_dputstr(fd, "0X");
  return (my_dputnbr_base(fd, n, "0123456789ABCDEF") + offset);
}

int		dput_min_hex(int fd, va_list ap, int opt)
{
  unsigned int	n;
  int		offset;

  offset = 0;
  n = va_arg(ap, int);
  if (opt == 0)
    offset = my_dputstr(fd, "0x");
  return (my_dputnbr_base(fd, n, "0123456789abcdef") + offset);
}
