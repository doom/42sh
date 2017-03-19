/*
** exit.c for 42sh in /home/doumer_c/rendu/PSU_2015_42sh
** 
** Made by clement doumergue
** Login   <doumer_c@epitech.net>
** 
** Started on  Mon May 30 18:32:25 2016 clement doumergue
** Last update Sun Jun  5 12:46:38 2016 clement doumergue
*/

#include <unistd.h>
#include "mysh.h"

static int	check_exit(char *nb)
{
  int		idx;

  idx = 0;
  if (nb[0] == '-')
    idx = 1;
  while (nb[idx] != '\0')
    {
      if (nb[idx] < '0' || nb[idx] > '9')
	return (1);
      idx += 1;
    }
  return (0);
}

int	my_exit(char **args, t_shell *sh)
{
  if (args[1] != NULL && check_exit(args[1]) != 0)
    {
      my_dprintf(2, "exit: Badly formed number.\n");
      return (FAILURE);
    }
  if (args[1] != NULL && args[2] != NULL)
    {
      my_dprintf(2, "exit: Expression Syntax.\n");
      return (FAILURE);
    }
  sh->exit_status = (args[1]) ? my_getnbr(args[1]) : 0;
  sh->run = false;
  return (SUCCESS);
}
