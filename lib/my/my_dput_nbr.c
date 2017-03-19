/*
** my_dput_nbr.c for libdoom in /home/doumer_c/libmy
** 
** Made by clement doumergue
** Login   <doumer_c@epitech.net>
** 
** Started on  Wed Jan 27 22:17:45 2016 clement doumergue
** Last update Wed Jan 27 22:17:58 2016 clement doumergue
*/

#include "my_dprintf.h"

int	my_dput_nbr(int fd, int nb)
{
  int	cpt;

  cpt = 0;
  if (nb == -2147483648)
    {
      cpt += my_dputchar(fd, '-');
      cpt += my_dputchar(fd, '2');
      cpt += my_dput_nbr(fd, 147483648);
    }
  else
    {
      if (nb < 0)
	{
	  cpt += my_dputchar(fd, '-');
	  nb = -nb;
	}
      if (nb >= 10)
	cpt += my_dput_nbr(fd, nb / 10);
      cpt += my_dputchar(fd, '0' + nb % 10);
    }
  return (cpt);
}
