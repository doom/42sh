/*
** history.c for 42sh in /home/doumer_c/rendu/PSU_2015_42sh
**
** Made by clement doumergue
** Login   <doumer_c@epitech.net>
**
** Started on  Mon May  2 18:17:21 2016 clement doumergue
** Last update Sat Jun  4 12:37:26 2016 szterg_r
*/

#include <stdio.h>
#include <stdlib.h>
#include "mysh.h"

void	add_to_history(t_dblist *history, const char *input)
{
  if (input[0] != '!' && append_to_dblist(history, my_strdup(input)) != FAILURE)
    if (history->size >= 1000)
      free(front_pop_from_dblist(history));
}

static int	show_history(t_dblist *history)
{
  t_elem	*e;
  register int	i;

  i = 1;
  e = history->first;
  while (e)
    {
      printf("%*d  %s\n", 5, i++, (const char *)e->data);
      e = e->next;
    }
  return (SUCCESS);
}

int		history(char **argv, t_dblist *history)
{
  t_elem	*e;

  if (!argv[1])
    return (show_history(history));
  if (is_number(argv[1])
      && (e = get_elem_at_index(history, my_getnbr(argv[1]) - 1)))
    printf("%s  %s\n", argv[1], (const char *)e->data);
  return (SUCCESS);
}
