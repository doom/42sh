/*
** alias.c for mysh in /home/doumer_c/rendu/PSU_2015_minishell2
**
** Made by clement doumergue
** Login   <doumer_c@epitech.net>
**
** Started on  Wed Apr  6 14:47:36 2016 clement doumergue
** Last update Sat Jun  4 11:58:18 2016 szterg_r
*/

#include <stdlib.h>
#include "mysh.h"

static int	my_showalias(char **argv, t_dblist *al)
{
  if (!argv || !argv[1])
    return (show_dblist(al));
  if (argv[2])
    return (my_dprintf(2, "showalias: too many arguments\n"));
  return (my_printf("%s\n", my_getenv(argv[1], al)));
}

int	my_alias(char **argv, t_dblist *al)
{
  if (!argv || !argv[1] || !argv[2])
    return (my_showalias(argv, al));
  update_var_value(al, argv[1], argv[2]);
  return (SUCCESS);
}

int	my_unalias(char **argv, t_dblist *al)
{
  if (!argv || !argv[1])
    return (my_dprintf(2, "unalias: too few arguments\n"));
  else if (argv[2])
    return (my_dprintf(2, "unalias: too many arguments\n"));
  remove_var(al, argv[1]);
  return (SUCCESS);
}

char		*replace_aliases(char *input, const t_dblist *al)
{
  t_elem	*e;
  char		*cur;
  int		pos;

  if ((!my_strncmp(input, "alias", 5) && IS_SEP(input[5]))
      || (!my_strncmp(input, "unalias", 7) && IS_SEP(input[7])))
    return (input);
  e = al->first;
  while (e && input && (cur = my_strdup(e->data)))
    {
      pos = get_char_pos(cur, '=');
      cur[pos] = '\0';
      input = replace_word(input, cur, cur + pos + 1);
      free(cur);
      e = e->next;
    }
  return (input);
}
