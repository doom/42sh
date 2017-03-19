/*
** print_echo.c for echo in /home/tavart_f/rendu/PSU2/PSU_2015_42sh/minishell2/srcs/builtins
** 
** Made by Fanny Tavart
** Login   <tavart_f@epitech.net>
** 
** Started on  Fri May  6 14:42:46 2016 Fanny Tavart
** Last update Fri Jun  3 12:27:51 2016 Fanny Tavart
*/

#include <unistd.h>
#include "mysh.h"

void	init_options(t_options *option)
{
  option->e = 0;
  option->n = 0;
}

static int	print_special_char(const char escape)
{
  if (escape == 'a')
    (void)write(1, "\a", 1);
  else if (escape == 'b')
    (void)write(1, "\b", 1);
  else if (escape == 'c')
    return (1);
  else if (escape == 'e')
    (void)write(1, "\033", 1);
  else if (escape == 'f')
    (void)write(1, "\f", 1);
  else if (escape == 'n')
    (void)write(1, "\n", 1);
  else if (escape == 't')
    (void)write(1, "\t", 1);
  else if (escape == 'v')
    (void)write(1, "\v", 1);
  else
    return (-1);
  return (0);
}

static void	print_backslash(const char *str, int idx)
{
  (void)write(1, "\\", 1);
  if (str[idx] != '\0')
    (void)write(1, &str[idx], 1);
}

void	print_backslash_escapes(const char *str)
{
  int	idx;

  idx = 0;
  while (str[idx] != '\0' && str[idx] != '$')
    {
      (void)write(1, &str[idx], 1);
      idx += 1;
    }
}

void	print_av(const char *str, t_options *option)
{
  int	idx;
  int	check_char;

  idx = 0;
  while (str[idx] != '\0' && str[idx] != '$')
    {
      if (str[idx] == '\\')
	{
	  if (str[idx + 1] != '\0')
	    idx += 1;
	  if ((check_char = print_special_char(str[idx])) == -1)
	    print_backslash(str, idx);
	  else if (check_char == 1)
	    {
	      option->n = 1;
	      return ;
	    }
	}
      else
	(void)write(1, &str[idx], 1);
      idx += 1;
    }
}
