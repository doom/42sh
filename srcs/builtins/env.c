/*
** env.c for mysh in /home/doumer_c/rendu/PSU_2015_minishell2
**
** Made by clement doumergue
** Login   <doumer_c@epitech.net>
**
** Started on  Mon Mar 21 18:19:32 2016 clement doumergue
** Last update Sun Jun  5 13:30:14 2016 clement doumergue
*/

#include <unistd.h>
#include <stdlib.h>
#include "mysh.h"

char		*my_getenv(const char *str, const t_dblist *env)
{
  t_elem	*cur;

  cur = var_by_name(env, str);
  return ((cur) ? my_strchr((char *)(cur->data), '=') + 1 : "");
}

int	my_printenv(char **args, t_dblist *env)
{
  if (!args || !args[1])
    return (show_dblist(env));
  if (args[2])
    return (my_dprintf(STDERR_FILENO, TOO_MANY_ARGS("env")));
  return (my_printf("%s\n", my_getenv(args[1], env)));
}

int	my_unsetenv(char **args, t_dblist *env)
{
  if (args == NULL || args[1] == NULL)
    return (my_dprintf(STDERR_FILENO, TOO_FEW_ARGS("unsetenv")));
  return (remove_var(env, args[1]));
}

int	my_setenv(char **args, t_dblist *env)
{
  if (!args || !args[1])
    return (my_printenv(NULL, env));
  if (args[1][0] != '_' && !IS_MIN(args[1][0]) && !IS_MAJ(args[1][0]))
    return (my_dprintf(STDERR_FILENO, LETTER_VAR));
  if (!is_alphanum(args[1]))
    return (my_dprintf(STDERR_FILENO, NOT_ALPHANUM));
  if (args[2] == NULL)
    return (update_var_value(env, args[1], ""));
  if (args[3])
    return (my_dprintf(STDERR_FILENO, TOO_MANY_ARGS("setenv")));
  return (update_var_value(env, args[1], args[2]));
}

char		*replace_vars(char *input, const t_dblist *env)
{
  t_elem	*e;
  char		*cur;
  int		pos;

  e = env->first;
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
