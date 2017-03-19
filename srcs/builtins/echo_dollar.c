/*
** echo_dollar.c for echo in /home/tavart_f/rendu/PSU2/PSU_2015_42sh/minishell2/srcs/builtins
** 
** Made by Fanny Tavart
** Login   <tavart_f@epitech.net>
** 
** Started on  Fri May  6 14:37:01 2016 Fanny Tavart
** Last update Thu Jun  2 15:34:42 2016 Fanny Tavart
*/

#include <unistd.h>
#include "mysh.h"

static int	count_dollarsign(const char *str)
{
  int		count;
  int		idx;

  idx = 0;
  count = 0;
  while (str[idx] != '\0')
    {
      if (str[idx] == '$')
	{
	  count += 1;
	  if (str[idx + 1] != '$')
	    return (count);
	}
      idx += 1;
    }
  return (count);
}

static int	print_pid(const char *str)
{
  int		count;

  count = count_dollarsign(str);
  if ((count_dollarsign(str) % 2) != 0)
    count = (count_dollarsign(str) - 1);
  while (count != 0)
    {
      count /= 2;
      if (count != 0)
	my_dprintf(1, "%d", getpid());
    }
  return (count_dollarsign(str));
}

static void	print_undefined(const char *str, int count_dollars)
{
  int		idx;

  idx = count_dollars;
  while (str[idx] != '\0' && str[idx] != '$')
    {
      (void)write(1, &str[idx], 1);
      idx += 1;
    }
  (void)write(1, ": Undifined variable.", 21);
}

static void	get_str_env(char *str,
			    int count,
			    const t_dblist *env,
			    t_options option)
{
  int		idx;
  char		*print_env;
  char		sep;

  idx = count;
  sep = '\0';
  while (str[idx] != '\0' && str[idx] != ' ' && str[idx] != '\t')
    idx += 1;
  if (str[idx] != '\0')
    sep = str[idx];
  str[idx] = '\0';
  print_env = my_getenv(str + count, env);
  (void)write(1, print_env, my_strlen(print_env));
  str[idx] = sep;
  if (option.e != 1)
    print_backslash_escapes(str + idx);
  else
    print_av(str + idx, &option);
}

void	print_env(char *str, const t_dblist *env, t_options option)
{
  int	count;
  int	check;
  int	idx;

  count = print_pid(str);
  check = 0;
  idx = 0;
  while (str[idx] != '$')
    idx += 1;
  str = str + idx;
  if (count % 2 != 0 && str[count] != '\0')
    {
      get_str_env(str, count, env, option);
      check = 1;
    }
  if (count % 2 != 0 && check == 0 && str[count] == '\0')
    (void)write(1, "$", 1);
  else if (check == 0 && count % 2 != 0)
    print_undefined(str, count);
  else if (check == 0 && count % 2 == 0 && str[count] != '\0')
    (void)write(1, str + count, my_strlen(str + count));
}
