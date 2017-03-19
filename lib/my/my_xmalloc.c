/*
** my_xmalloc.c for libdoom in /home/doumer_c/libmy
** 
** Made by clement doumergue
** Login   <doumer_c@epitech.net>
** 
** Started on  Wed Jan 27 22:09:46 2016 clement doumergue
** Last update Tue Mar 22 22:32:06 2016 clement doumergue
*/

#include <stdlib.h>
#include "my.h"

void	*my_xmalloc(int size)
{
  void	*ptr;

  ptr = malloc(size);
  if (ptr == NULL)
    my_puterror("Malloc failed !\n");
  return (ptr);
}
