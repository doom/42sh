/*
** my_dputchar.c for libdoom in /home/doumer_c/libmy
** 
** Made by clement doumergue
** Login   <doumer_c@epitech.net>
** 
** Started on  Wed Jan 27 22:16:38 2016 clement doumergue
** Last update Wed Jan 27 22:17:07 2016 clement doumergue
*/

#include <unistd.h>
#include "my_dprintf.h"

int	my_dputchar(int fd, char c)
{
  write(fd, &c, 1);
  return (1);
}
