/*
** word_len.c for 42sh in /home/doumer_c/rendu/PSU_2015_42sh
** 
** Made by clement doumergue
** Login   <doumer_c@epitech.net>
** 
** Started on  Thu May 26 23:14:08 2016 clement doumergue
** Last update Thu May 26 23:33:37 2016 clement doumergue
*/

#include "my.h"

int	word_len(const char *str)
{
  int	i;

  i = 0;
  while (str[i] && !IS_SEP(str[i]) && get_char_pos("&|><", str[i]) == FAILURE)
    i += 1;
  return (i);
}
