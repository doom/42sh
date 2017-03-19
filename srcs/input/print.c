/*
** print.c for 42sh in /home/doumer_c/rendu/PSU_2015_42sh
** 
** Made by clement doumergue
** Login   <doumer_c@epitech.net>
** 
** Started on  Fri Jun  3 00:33:04 2016 clement doumergue
** Last update Sun Jun  5 16:21:26 2016 clement doumergue
*/

#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "input.h"
#include "mysh.h"

static const char	*g_bltns[] =
  {
    "cd",
    "printenv",
    "setenv",
    "unsetenv",
    "env",
    "alias",
    "unalias",
    "echo",
    "history",
    "exit",
    NULL
  };

static bool	is_in_path(const char *str, const t_shell *sh)
{
  char		**path;
  char		*cmd;
  int		i;

  if (str[0] == '/')
    return ((access(str, X_OK) || dir_exists(str)) ? false : true);
  else if (my_strncmp("./", str, 2) == 0)
    return ((access(str + 2, X_OK) || dir_exists(str)) ? false : true);
  if ((path = my_split(get_path(sh->env), ":")) == NULL)
    return (false);
  i = 0;
  while (path[i] != NULL)
    {
      if ((cmd = get_file(path[i++], str)) != NULL && !dir_exists(cmd))
	{
	  free_tab(path);
	  free(cmd);
	  return (true);
	}
      free(cmd);
    }
  free_tab(path);
  return (false);
}

static bool	is_valid_bin(char *str, int len, const t_shell *sh)
{
  char		bk;
  bool		ret;

  bk = str[len];
  str[len] = '\0';
  ret = is_in_path(str, sh);
  str[len] = bk;
  return (ret);
}

static bool	is_builtin_or_alias(char *str, int len, const t_shell *sh)
{
  t_elem	*e;
  int		i;
  char		bk;
  bool		ret;
  int		max;

  bk = str[len];
  str[len] = '\0';
  ret = false;
  e = sh->aliases->first;
  while (e && (max = MY_MAX(get_char_pos(e->data, '='), len))
	 && !(ret = !my_strncmp(str, e->data, max)))
    e = e->next;
  if (!ret)
    {
      i = 0;
      while (g_bltns[i] && my_strcmp(g_bltns[i], str))
	i += 1;
      ret = (g_bltns[i]) ? true : false;
    }
  str[len] = bk;
  return (ret);
}

static int	print_command(char *str, int max, t_shell *sh)
{
  int		i;
  bool		quote;

  i = word_len(str);
  if (is_builtin_or_alias(str, i, sh))
    write(1, BLUE, sizeof(BLUE));
  else
    write(1, (is_valid_bin(str, i, sh)) ? GREEN : RED, sizeof(GREEN));
  write(1, str, i);
  write(1, NORMAL, sizeof(NORMAL));
  quote = false;
  while (i < max && str[i] != '&' && str[i] != '|' && str[i] != ';')
    {
      if (str[i] == '"')
	{
	  if ((quote = !quote))
	    my_printf("%s\"", YELLOW);
	  else
	    my_printf("\"%s", NORMAL);
	}
      else
	write(1, &str[i], 1);
      i += 1;
    }
  return (i);
}

void	print_line(t_line *l, t_shell *sh)
{
  int	pos;

  put_seq("dl");
  put_seq("cr");
  show_prompt(sh);
  if (l->str)
    {
      pos = 0;
      while (pos < l->len)
	{
	  while (l->str[pos] && (IS_SEP(l->str[pos])
				 || l->str[pos] == '&' || l->str[pos] == '|'))
	    write(1, &l->str[pos++], 1);
	  pos += print_command(l->str + pos, l->len - pos, sh);
	  write(1, NORMAL, sizeof(NORMAL));
	}
      while (pos-- > l->pos)
	put_seq("le");
    }
}
