/*
** utils.c for 42sh in /home/doumer_c/rendu/PSU_2015_42sh
** 
** Made by clement doumergue
** Login   <doumer_c@epitech.net>
** 
** Started on  Tue May 17 14:33:24 2016 clement doumergue
** Last update Fri Jun  3 01:55:21 2016 clement doumergue
*/

#include "autocomplete.h"

bool	is_at_cmd(const t_line *l)
{
  int	i;

  i = l->pos;
  while (i >= 0 && !IS_SEP(l->str[i]))
    i -= 1;
  if (i < 0)
    return (true);
  while (i >= 0 && IS_SEP(l->str[i]))
    i -= 1;
  return ((i >= 0 && (l->str[i] == '|' || l->str[i] == '&'
		      || l->str[i] == ';')) ? true : false);
}

char		*last_item(const t_line *l)
{
  register int	i;

  i = l->pos - 1;
  while (i > 0 && !IS_WORD_SEP(l->str[i]))
    i -= 1;
  if (IS_WORD_SEP(l->str[i]))
    i += 1;
  return (my_strndup(l->str + i, l->pos - i));
}

char		*last_word(const t_line *l)
{
  register int	i;

  i = l->pos - 1;
  while (i > 0 && !IS_SEP(l->str[i]))
    i -= 1;
  if (IS_SEP(l->str[i]))
    i += 1;
  return (my_strndup(l->str + i, l->pos - i));
}
