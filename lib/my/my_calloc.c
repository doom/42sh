/*
** my_calloc.c for my_calloc in /home/szterg_r/Documents/PSU_2015_42sh
** 
** Made by roman sztergbaum
** Login   <szterg_r@epitech.net>
** 
** Started on  Sat Jun  4 13:44:20 2016 roman sztergbaum
** Last update Sat Jun  4 13:51:38 2016 roman sztergbaum
*/

#include <stdlib.h>
#include <string.h>
#include "my.h"

void	*my_calloc(size_t size)
{
  void	*p;

  if ((p = malloc(size)) == NULL)
    return (NULL);
  memset(p, '\0', size);
  return (p);
}
