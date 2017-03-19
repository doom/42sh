/*
** main.c for mysh in /home/doumer_c/rendu/PSU_2015_minishell2
**
** Made by clement doumergue
** Login   <doumer_c@epitech.net>
**
** Started on  Mon Mar 21 12:56:50 2016 clement doumergue
** Last update Sun Jun  5 00:40:37 2016 clement doumergue
*/

#include <stdlib.h>
#include "get_next_line.h"
#include "mysh.h"

int		handle_input(char *input, t_shell *sh)
{
  char		*exp;
  t_tree	*exp_tree;

  sh->count += 1;
  exp = my_strdup(skip_blank(input));
  if (!exp || *exp == '\0')
    {
      free(input);
      free(exp);
      return (SUCCESS);
    }
  add_to_history(sh->history, exp);
  if ((exp = replace_word(exp, "\"\"", "")) == NULL
      ||(exp = replace_aliases(exp, sh->aliases)) == NULL
      || (exp = replace_globs(exp)) == NULL)
    return (FAILURE);
  sh->pipes_count = 0;
  if ((exp_tree = parse_exp(exp)) != NULL)
    execute_tree(exp_tree, sh);
  kill_pids(sh->pids);
  release_tree(exp_tree);
  free(exp);
  free(input);
  return (SUCCESS);
}

static int	run_shell(t_shell *sh)
{
  char		*input;

  sh->exit_status = 0;
  sh->run = true;
  sh->hist_cur = NULL;
  while (sh->run && init_term(&sh->term, my_getenv("TERM", sh->env)) != FAILURE
	 && show_prompt(sh) && (input = read_command(sh)) != NULL)
    {
      reset_term(&sh->term);
      my_dputchar(1, 10);
      if (handle_input(remove_comments(input), sh) != SUCCESS)
	return (FAILURE);
      sh->hist_cur = NULL;
    }
  my_dputchar(1, 10);
  return (SUCCESS);
}

static int	run_script(t_shell *sh)
{
  char		*input;

  sh->exit_status = 0;
  sh->run = true;
  while (sh->run && (input = get_next_line(sh->fd)) != NULL)
    if (handle_input(remove_comments(input), sh) != SUCCESS)
      return (FAILURE);
  return (SUCCESS);
}

int			main(int ac, char **av, char **env)
{
  t_shell		*sh;
  int			ret;

  if ((sh = setup_shell(ac - 1, av + 1, env)) == NULL)
    return (my_puterror(SETUP_FAILED));
  if (sh->interactive)
    {
      if (init_term(&sh->term, my_getenv("TERM", sh->env)) == FAILURE
	  || init_seqs() == FAILURE || reset_term(&sh->term) == FAILURE)
	return (my_puterror(SETUP_FAILED));
      run_shell(sh);
      reset_term(&sh->term);
      release_seqs();
    }
  else
    run_script(sh);
  ret = sh->exit_status;
  release_shell(sh);
  return (ret);
}
