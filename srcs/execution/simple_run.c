/*
** run.c for mysh in /home/doumer_c/rendu/PSU_2015_minishell2
** 
** Made by clement doumergue
** Login   <doumer_c@epitech.net>
** 
** Started on  Tue Mar 22 22:13:48 2016 clement doumergue
** Last update Sun Jun  5 21:32:40 2016 clement doumergue
*/

#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <signal.h>
#include "mysh.h"

static const t_signal_message	messages[] =
  {
    {SIGQUIT, "Quit (core dumped)\n"},
    {SIGABRT, "Aborted (core dumped)\n"},
    {SIGFPE, "Floating point exception (core dumped)\n"},
    {SIGKILL, "Killed\n"},
    {SIGSEGV, "Segmentation fault (core dumped)\n"},
    {SIGPIPE, "Broken pipe\n"},
    {SIGTERM, "Terminated\n"},
    {SIGBUS, "Bus error (core dumped)\n"},
  };

static int	handle_errors(int status, t_shell *sh)
{
  int		i;
  int		sig;

  sig = WTERMSIG(status);
  i = -1;
  while (++i < 8)
    if (sig == messages[i].signal)
      {
	my_dprintf(STDERR_FILENO, messages[i].message);
	return ((sh->exit_status = 128 + sig));
      }
  return ((sh->exit_status = WEXITSTATUS(status)));
}

static void	exec_child(char **argv, t_shell *sh)
{
  char		**env;

  if (sh->pipes_count > 0)
    {
      close(sh->cfg.pipefd[0]);
      if (dup2(sh->cfg.pipefd[1], 1) == FAILURE)
        exit(1);
    }
  env = env_to_tab(sh->env);
  if (execve(argv[0], argv, env) == FAILURE)
    {
      free(env);
      (void)my_puterror(BAD_EXEC(argv[0]));
      exit(1);
    }
  free(env);
}

static int	store_pid(int pid, t_shell *sh)
{
  if (append_to_dblist_int(sh->pids, pid) == FAILURE)
    {
      kill(pid, SIGQUIT);
      return (FAILURE);
    }
  sh->pipes_count -= 1;
  return (SUCCESS);
}

static int	simple_exec(char **argv, t_shell *sh)
{
  int		pid;
  int		status;

  status = 0;
  if (sh->pipes_count)
    if (pipe(sh->cfg.pipefd) == FAILURE)
      return (FAILURE);
  if ((pid = fork()) == FAILURE)
    return (my_puterror(FORK_FAILED));
  if (pid == 0)
    exec_child(argv, sh);
  if (sh->pipes_count > 0)
    {
      if (store_pid(pid, sh) == FAILURE)
	return (FAILURE);
    }
  else
    {
      signal(SIGINT, SIG_IGN);
      waitpid(pid, &status, 0);
      signal(SIGINT, SIG_DFL);
    }
  return ((WIFSIGNALED(status) || WIFEXITED(status))
	  ? handle_errors(status, sh) : SUCCESS);
}

int	simple_command(const char *input, t_shell *sh)
{
  int	ret;
  char	**argv;

  if ((argv = my_split(input, " \t\v")) == NULL || *argv == NULL)
    return (FAILURE);
  ret = check_builtins(argv, sh);
  if (ret == SUCCESS || ret == FAILURE)
    {
      if (ret)
	sh->exit_status = 1;
      free_tab(argv);
      return (ret);
    }
  if (find_path(argv, sh) == FAILURE)
    {
      if (sh->pipes_count > 0)
	sh->pipes_count -= 1;
      sh->exit_status = 1;
      return (my_dprintf(2, NOT_FOUND));
    }
  ret = simple_exec(argv, sh);
  free_tab(argv);
  return (ret);
}
