/*
** my_printf.c for my_printf in /home/doumer_c/rendu/PSU_2015_minishell2
** 
** Made by clement doumergue
** Login   <doumer_c@epitech.net>
** 
** Started on  Mon Mar 21 22:50:15 2016 clement doumergue
** Last update Mon Mar 21 22:51:44 2016 clement doumergue
*/

#include <unistd.h>
#include "my.h"

int		my_printf(const char *format, ...)
{
  va_list	ap;
  int		cpt;

  if (format == NULL)
    return (1);
  va_start(ap, format);
  cpt = my_vdprintf(STDOUT_FILENO, format, ap);
  va_end(ap);
  return (cpt);
}
