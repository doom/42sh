/*
** errors.c for libdoom in /home/doumer_c/libmy
** 
** Made by clement doumergue
** Login   <doumer_c@epitech.net>
** 
** Started on  Wed Jan 27 22:07:26 2016 clement doumergue
** Last update Sat Mar 12 13:44:21 2016 clement doumergue
*/

#include <stdlib.h>
#include "my.h"

int		my_puterror(const char *format, ...)
{
  va_list	ap;

  va_start(ap, format);
  my_vdprintf(2, format, ap);
  va_end(ap);
  return (FAILURE);
}
