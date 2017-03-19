/*
** echo.c for echo in /home/tavart_f/rendu/PSU2/PSU_2015_42sh/minishell2/srcs/builtins
** 
** Made by Fanny Tavart
** Login   <tavart_f@epitech.net>
** 
** Started on  Tue Apr 26 18:13:44 2016 Fanny Tavart
** Last update Fri Jun  3 12:27:43 2016 Fanny Tavart
*/

#include <unistd.h>
#include "mysh.h"

static int	check_it(t_options *option, int idx, const char *str, int count)
{
  int		check;

  check = 0;
  if ((str[idx] == 'n' || str[idx] == 'e')
      && (str[idx + 1] == '\0'
	  || str[idx + 1] == 'n' || str[idx + 1] == 'e'))
    {
      check = 1;
      if (str[idx] == 'n')
	option->n = 1;
      else if (str[idx] == 'e')
	option->e = 1;
      if (str[idx + 1] != '\0'
	  && str[idx + 1] != 'e' && str[idx + 1] != 'n')
	if (count == 1)
	  {
	    init_options(option);
	    check = 0;
	  }
    }
  return (check);
}

static char	check_str(const char *str, t_options *option, int count)
{
  int		idx;
  int		check;

  idx = 1;
  while (str[idx] != '\0')
    {
      check = check_it(option, idx, str, count);
      idx += 1;
    }
  if (check == 1)
    count += 1;
  return (count);
}

static int	check_options(char **av, t_options *option)
{
  int		idx;
  int		count;

  idx = 1;
  count = 0;
  while (av[idx] != NULL)
    {
      if (av[idx][0] == '-' && (av[idx - 1][0] == '-' || idx - 1 == 0))
	count = check_str(av[idx], option, count);
      idx += 1;
    }
  return (count);
}

static int	contains_dollar(const char *str)
{
  int		idx;

  idx = 0;
  while (str[idx] != '\0')
    {
      if (str[idx] == '$')
	return (1);
      idx += 1;
    }
  return (0);
}

int		my_echo(char **av, t_dblist *env)
{
  int		idx;
  t_options	option;

  init_options(&option);
  idx = (check_options(av, &option) + 1);
  while (av[idx] != NULL)
    {
      if (option.e != 1)
	print_backslash_escapes(av[idx]);
      else
	print_av(av[idx], &option);
      if (contains_dollar(av[idx]) == 1)
	print_env(av[idx], env, option);
      if (av[idx + 1] != NULL)
	(void)write(1, " ", 1);
      idx += 1;
    }
  if (option.n == 0)
    (void)write(1, "\n", 1);
  return (SUCCESS);
}
