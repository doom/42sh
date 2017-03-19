/*
** run_utils.c for mysh in /home/doumer_c/rendu/PSU_2015_minishell2
** 
** Made by clement doumergue
** Login   <doumer_c@epitech.net>
** 
** Started on  Tue Apr  5 22:54:15 2016 clement doumergue
** Last update Sun Jun  5 00:58:12 2016 clement doumergue
*/

#include <unistd.h>
#include <stdlib.h>
#include "mysh.h"

static const char	*g_path = "/bin:/usr/bin";

const char		*get_path(const t_dblist *env)
{
  t_elem		*cur;
  char			*value;

  cur = var_by_name(env, "PATH");
  if (cur && (value = my_strchr(cur->data, '=') + 1))
    return (value);
  return (g_path);
}

int		find_path(char **argv, const t_shell *sh)
{
  char		**path;
  char		*cmd;
  int		i;

  if (access(argv[0], X_OK) == 0 && !dir_exists(argv[0]))
    return (SUCCESS);
  else if (my_strncmp("./", argv[0], 2) == 0)
    return ((access(argv[0] + 2, X_OK) || dir_exists(argv[0])) ? FAILURE
	    : replace_tab_entry(argv, 0, my_strdup(argv[0] + 2)));
  if ((path = my_split(get_path(sh->env), ":")) == NULL)
    return (FAILURE);
  i = 0;
  while (path[i] != NULL)
    if ((cmd = get_file(path[i++], argv[0])) != NULL && !dir_exists(cmd))
      {
	free_tab(path);
	return (replace_tab_entry(argv, 0, cmd));
      }
  free_tab(path);
  return (FAILURE);
}
