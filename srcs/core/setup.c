/*
** setup.c for mysh in /home/doumer_c/rendu/PSU_2015_minishell2
**
** Made by clement doumergue
** Login   <doumer_c@epitech.net>
**
** Started on  Mon Mar 21 13:19:29 2016 clement doumergue
** Last update Sun Jun  5 18:40:09 2016 clement doumergue
*/

#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include "mysh.h"

int	release_shell(t_shell *sh)
{
  release_dblist(sh->env, &free);
  release_dblist(sh->aliases, &free);
  release_dblist(sh->history, &free);
  free(sh->pids);
  free(sh->prompt);
  free(sh);
  return (SUCCESS);
}

t_dblist	*get_backup_env(void)
{
  t_dblist	*env;

  if ((env = init_dblist()) == NULL)
    return (NULL);
  if (append_to_dblist(env, my_strdup("PATH=/bin:/usr/bin")) == FAILURE
      || append_to_dblist(env, my_strdup("USER=user")) == FAILURE
      || append_to_dblist(env, my_strdup("PWD=.")) == FAILURE
      || append_to_dblist(env, my_strdup("OLDPWD=/")) == FAILURE)
    {
      release_dblist(env, &free);
      return (NULL);
    }
  return (env);
}

static int	get_fd_info(int ac, char **av, t_shell *sh)
{
  sh->fd = 0;
  if (ac > 0)
    if ((sh->fd = open(av[0], O_RDONLY)) == FAILURE)
      return (FAILURE);
  sh->interactive = my_isatty(sh->fd);
  return (EXIT_SUCCESS);
}

t_shell		*setup_shell(int ac, char **av, char **env)
{
  t_shell	*sh;

  if ((sh = my_calloc(sizeof(*sh))) == NULL)
    return (NULL);
  if (get_fd_info(ac, av, sh) == FAILURE)
    {
      free(sh);
      return (NULL);
    }
  sh->env = (env && *env) ? env_to_dblist(env) : get_backup_env();
  if (sh->env == NULL)
    return (NULL);
  if (!(sh->aliases = init_dblist()) || !(sh->history = init_dblist())
      || !(sh->pids = init_dblist_int()))
    {
      release_dblist(sh->env, &free);
      return (NULL);
    }
  if (open_myshrc(sh) == FAILURE || generate_prompt(sh) == FAILURE)
    return (NULL);
  sh->hist_cur = NULL;
  sh->count = 0;
  sh->cfg.bk[0] = dup(0);
  return (sh);
}
