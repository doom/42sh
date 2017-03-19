/*
** redo.c for 42sh in /home/doumer_c/rendu/PSU_2015_42sh
**
** Made by clement doumergue
** Login   <doumer_c@epitech.net>
**
** Started on  Mon May  2 01:01:05 2016 clement doumergue
** Last update Sat Jun  4 12:34:08 2016 szterg_r
*/

#include <stdlib.h>
#include "mysh.h"

const char	*get_last_cmd(const t_dblist *history, const char *start)
{
  t_elem	*e;
  register int	len;

  len = my_strlen(start);
  e = history->last;
  while (e && my_strncmp((const char *)e->data, start, len))
    e = e->prev;
  return ((e) ? e->data : NULL);
}

const char	*get_cmd_index(const t_dblist *history, int nbr)
{
  t_elem	*e;
  register int	i;

  e = history->last;
  i = 1;
  while (e && i++ < nbr)
    e = e->prev;
  return ((e) ? e->data : NULL);
}

int		redo_cmd(char **argv, t_shell *sh)
{
  const char	*last;

  if (argv[0][1] == '\0')
    return (SUCCESS);
  last = (is_number(argv[0] + 1))
    ? get_cmd_index(sh->history, my_atoi(argv[0] + 1))
    : get_last_cmd(sh->history, GET_PATTERN(argv));
  if (last == NULL)
    return (my_printf("42sh: %s: event not found\n", argv[0]));
  return (handle_input(my_strdup(last), sh));
}
