/*
** my_dprintf.c for libdoom in /home/doumer_c/libmy
** 
** Made by clement doumergue
** Login   <doumer_c@epitech.net>
** 
** Started on  Wed Jan 27 22:15:50 2016 clement doumergue
** Last update Sun Jun  5 21:28:23 2016 clement doumergue
*/

#include <stdlib.h>
#include "my_dprintf.h"

static int	(*g_ftab[])(int, va_list, int) =
{
  &dput_int,
  &dput_char,
  &dput_string,
  &dput_maj_hex,
  &dput_min_hex,
  &dput_oct,
  &dput_bin,
  &dput_pointer,
  &dput_string_maj,
  &dput_unsigned,
  &dput_int
};

static int	handle_dintermediate(char c)
{
  int		i;
  char		inter[4];

  my_strcpy(inter, "#+ ");
  i = 0;
  while (i < 3 && inter[i] != c)
    i = i + 1;
  return (i);
}

static int	id_and_ddisp(int fd, const char *format, va_list ap, int *pos)
{
  char		symbols[12];
  int		i;
  int		opt;

  if ((opt = handle_dintermediate(format[*pos])) != 3)
    *pos += 1;
  my_strcpy(symbols, "dcsXxobpSui");
  i = 0;
  while (symbols[i] != format[*pos] && symbols[i] != '\0')
    i = i + 1;
  if (symbols[i] != '\0')
    return (g_ftab[i](fd, ap, opt));
  else if (format[*pos] != '%' && format[*pos] != '\0')
    {
      my_dputchar(fd, '%');
      if (opt != 3 && format[*pos] != ' ')
	my_dputchar(fd, format[--*pos]);
      else
	my_dputchar(fd, format[*pos]);
    }
  return (2);
}

int	my_vdprintf(int fd, const char *format, va_list ap)
{
  int	i;

  i = 0;
  if (format == NULL)
    return (1);
  while (i < my_strlen(format))
    {
      if (format[i] == '%')
	{
	  if (format[++i] == '%')
	    my_dputchar(fd, '%');
	  else if (format[i] != '%')
	    id_and_ddisp(fd, format, ap, &i);
	}
      else
	my_dputchar(fd, format[i]);
      i = i + 1;
    }
  return (SUCCESS);
}

int		my_dprintf(int fd, const char *format, ...)
{
  va_list	ap;
  int		cpt;

  if (format == NULL)
    return (1);
  va_start(ap, format);
  cpt = my_vdprintf(fd, format, ap);
  va_end(ap);
  return (cpt);
}
