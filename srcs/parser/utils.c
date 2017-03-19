/*
** utils.c for 42sh in /home/doumer_c/rendu/PSU_2015_42sh
** 
** Made by clement doumergue
** Login   <doumer_c@epitech.net>
** 
** Started on  Tue May 31 18:23:23 2016 clement doumergue
** Last update Wed Jun  1 18:50:58 2016 clement doumergue
*/

#include <stdlib.h>
#include <stdbool.h>
#include "my.h"

bool	is_begin(const char *str, int pos)
{
  int	i;

  i = 0;
  while (str[i] == ' ' && str[i] == '\t' && i < pos)
    i += 1;
  return (i >= pos - 1);
}

int	words_len(const char *str, int n)
{
  int	i;

  i = 0;
  while (str[i] && n >= 0)
    {
      if (i == 0 || (str[i] != ' ' && str[i] != '\t'
		     && (str[i - 1] == ' ' || str[i - 1] == '\t')))
	n -= 1;
      i += 1;
    }
  return (i - 1);
}

bool	move_words(char *str, const char *op)
{
  char	*dup;
  int	op_len;
  int	n_word;
  int	len;
  int	total;

  if (count_words(str, " \t") <= 1)
    {
      (void)my_puterror("Invalid null command.\n");
      return (false);
    }
  if ((dup = my_strdup(str)) == NULL)
    return (false);
  op_len = my_strlen(op);
  n_word = (str[op_len] == ' ' || str[op_len] == '\t') ? 2 : 1;
  len = words_len(str, n_word);
  total = my_strlen(dup);
  my_strncpy(str, dup + len, total - len);
  my_strncpy(str + total - len, dup, len);
  free(dup);
  return (true);
}
