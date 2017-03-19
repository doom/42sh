/*
** my_dputnbr_base.c for libdoom in /home/doumer_c/libmy
**
** Made by clement doumergue
** Login   <doumer_c@epitech.net>
**
** Started on  Wed Jan 27 22:13:47 2016 clement doumergue
** Last update Mon May 30 12:37:51 2016 szterg_r
*/

#include "my_dprintf.h"

int	my_dputnbr_base(int fd, unsigned int nbr, char *base)
{
  int	len_base;
  int	cpt;

  cpt = 0;
  len_base = my_strlen(base);
  if (len_base <= 1)
    return (0);
  if ((int)nbr < 0)
    {
      cpt += my_dputchar(fd, '-');
      nbr = -nbr;
    }
  if ((int)nbr >= len_base)
    cpt += my_dputnbr_base(fd, nbr / len_base, base);
  cpt += my_dputchar(fd, base[nbr % len_base]);
  return (cpt);
}
