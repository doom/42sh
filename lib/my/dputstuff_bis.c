/*
** dputstuff_bis.c for libdoom in /home/doumer_c/libmy
** 
** Made by clement doumergue
** Login   <doumer_c@epitech.net>
** 
** Started on  Wed Jan 27 22:20:04 2016 clement doumergue
** Last update Sat Apr  2 01:31:52 2016 clement doumergue
*/

#include <stdlib.h>
#include "my_dprintf.h"

int		dput_oct(int fd, va_list ap, int opt)
{
  unsigned int	n;
  int		offset;

  n = va_arg(ap, unsigned int);
  offset = 0;
  if (opt == 0)
    offset = my_dputchar(fd, '0');
  return (my_dputnbr_base(fd, n, "01234567") + offset);
}

int		dput_bin(int fd, va_list ap, int opt __attribute__ ((unused)))
{
  unsigned int	n;

  n = va_arg(ap, unsigned int);
  return (my_dputnbr_base(fd, n, "01"));
}

int		dput_pointer(int fd, va_list ap, int opt)
{
  unsigned long	p;
  int		offset;

  p = va_arg(ap, unsigned long);
  if (p != 0)
    {
      offset = 0;
      if (opt == 1)
	offset = my_dputchar(fd, '+');
      my_dputstr(fd, "0x");
      return (my_dputlong_base(fd, p, "0123456789abcdef") + 2 + offset);
    }
  my_dputstr(fd, "(nil)");
  return (5);
}

int	dput_string_maj(int fd, va_list ap, int opt __attribute__ ((unused)))
{
  char	*str;

  str = va_arg(ap, char *);
  if (str != NULL)
    return (my_dshowstr_oct(fd, str));
  my_dputstr(fd, "(null)");
  return (7);
}

int		dput_unsigned(int fd, va_list ap,
			      int opt __attribute__ ((unused)))
{
  unsigned int	n;

  n = va_arg(ap, unsigned int);
  return (my_dputnbr_base(fd, n, "0123456789"));
}
