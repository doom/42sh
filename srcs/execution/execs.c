/*
** execs.c for mysh in /home/doumer_c/rendu/PSU_2015_minishell2
**
** Made by clement doumergue
** Login   <doumer_c@epitech.net>
**
** Started on  Fri Apr  8 15:35:42 2016 clement doumergue
** Last update Sun Jun  5 19:33:52 2016 clement doumergue
*/

#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include "mysh.h"

int	exec_delim(t_tree *left, t_tree *right, t_shell *sh)
{
  int	ret[2];

  ret[0] = execute_tree(left, sh);
  ret[1] = execute_tree(right, sh);
  return (ret[0] || ret[1]);
}

int	exec_and(t_tree *left, t_tree *right, t_shell *sh)
{
  int	ret;

  ret = execute_tree(left, sh);
  if (sh->exit_status == 0)
    ret = execute_tree(right, sh);
  return (ret);
}

int	exec_or(t_tree *left, t_tree *right, t_shell *sh)
{
  int	ret;

  ret = execute_tree(left, sh);
  if (sh->exit_status != 0)
    ret = execute_tree(right, sh);
  return (ret);
}

void		kill_pids(t_dblist_int *pids)
{
  t_elem_int	*e;

  while (pids->first)
    {
      e = pids->first;
      pids->first = pids->first->next;
      (void)kill(e->data, SIGQUIT);
      free(e);
    }
  pids->first = NULL;
  pids->last = NULL;
}

int	exec_pipe(t_tree *left, t_tree *right, t_shell *sh)
{
  sh->pipes_count += 1;
  execute_tree(left, sh);
  if (sh->exit_status != 0)
    {
      dup2(sh->cfg.bk[0], 0);
      return (FAILURE);
    }
  if (dup2(sh->cfg.pipefd[0], 0) == FAILURE)
    return (FAILURE);
  close(sh->cfg.pipefd[1]);
  execute_tree(right, sh);
  if (sh->exit_status != 0)
    {
      dup2(sh->cfg.bk[0], 0);
      return (FAILURE);
    }
  if (sh->pipes_count == 0)
    if (dup2(sh->cfg.bk[0], 0) == FAILURE)
      return (FAILURE);
  return (SUCCESS);
}
