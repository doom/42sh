/*
** builtins.c for mysh in /home/doumer_c/rendu/PSU_2015_minishell2
**
** Made by clement doumergue
** Login   <doumer_c@epitech.net>
**
** Started on  Tue Mar 22 22:45:03 2016 clement doumergue
** Last update Sun Jun  5 00:21:25 2016 clement doumergue
*/

#include <stdlib.h>
#include "mysh.h"

static const t_builtin	g_builtins[] =
  {
    {"cd", &my_cd},
    {"printenv", &my_printenv},
    {"setenv", &my_setenv},
    {"unsetenv", &my_unsetenv},
    {"env", &my_printenv},
    {"alias", &my_alias},
    {"unalias", &my_unalias},
    {"echo", &my_echo},
    {"history", &history},
    {NULL, NULL}
  };

int		check_builtins(char **argv, t_shell *sh)
{
  register int	i;

  if (!argv || !argv[0])
    return (SUCCESS);
  if (argv[0][0] == REDO_OP)
    return (redo_cmd(argv, sh));
  if (!my_strcmp(argv[0], "exit"))
    return (my_exit(argv, sh));
  i = 0;
  while (g_builtins[i].func != NULL && my_strcmp(argv[0], g_builtins[i].name))
    i += 1;
  if (g_builtins[i].func == NULL)
    return (42);
  return (g_builtins[i].func(argv, ((5 == i || i == 6) ? sh->aliases
				    : ((i == 8) ? sh->history : sh->env))));
}
