/*
** my_dshowstr_oct.c for libdoom in /home/doumer_c/libmy
** 
** Made by clement doumergue
** Login   <doumer_c@epitech.net>
** 
** Started on  Wed Jan 27 22:12:26 2016 clement doumergue
** Last update Sat Mar 19 12:57:13 2016 clement doumergue
*/

#include "my_dprintf.h"

int	my_dshowstr_oct(int fd, const char *str)
{
  int	i;
  int	cpt;

  cpt = 0;
  i = 0;
  while (str[i] != '\0')
    {
      if (32 < str[i] && str[i] <= 126)
	cpt += my_dputchar(fd, str[i]);
      else if (str[i] == 32)
	cpt += my_dputstr(fd, "(space)");
      else if (str[i] == 27)
	cpt += my_dputstr(fd, "^E");
      i = i + 1;
    }
  return (cpt);
}
