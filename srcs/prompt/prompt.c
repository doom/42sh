/*
** ps1.c for  in /home/giraud_e/Rendu/SystemUnix/PSU_2015_42sh/srcs
**
** Made by Louis Giraud
** Login   <giraud_e@epitech.net>
**
** Started on  Tue May 31 16:37:56 2016 Louis Giraud
** Last update Wed Jun  1 23:20:17 2016 clement doumergue
*/

#include <stdlib.h>
#include "mysh.h"

static const t_escape	g_esc_tab[] =
  {
    {'u', "USER"},
    {'h', "HOSTNAME"},
    {'H', "HOME"},
    {'s', "SHELL"}
  };

static char	*var_for_flag(char c)
{
  int		i;

  i = 0;
  while (i < 4 && c != g_esc_tab[i].flag)
    i += 1;
  return ((i == 4) ? NULL : g_esc_tab[i].var);
}

static int	prompt_len(const char *ps1, const t_dblist *env)
{
  int		len;
  char		*var;

  len = 0;
  while (*ps1)
    {
      if (*ps1++ == '\\')
	len += ((var = var_for_flag(*ps1++)) == NULL)
	  ? 2 : my_strlen(my_getenv(var, env));
      else
	len += 1;
    }
  return (len);
}

int	get_prompt(const char *ps1, t_shell *shell)
{
  int	i;
  int	k;
  int	len;
  char	*var;

  i = -1;
  k = 0;
  while (ps1[++i] != '\0')
    {
      if (ps1[i] == '\\' && (var = var_for_flag(ps1[i + 1])) != NULL)
	{
	  i += 1;
	  len = my_strlen(my_getenv(var, shell->env));
	  my_strncpy(shell->prompt + k, my_getenv(var, shell->env), len);
	  k += len;
	}
      else
	shell->prompt[k++] = ps1[i];
    }
  shell->prompt[k] = '\0';
  return (SUCCESS);
}

int	generate_prompt(t_shell *shell)
{
  char	*ps1;
  int	len;

  if ((ps1 = my_getenv("PS1", shell->env))[0] == '\0')
    return ((!(shell->prompt = my_strdup("> "))) ? FAILURE : SUCCESS);
  len = prompt_len(ps1, shell->env);
  if (!(shell->prompt = malloc(sizeof(char) * (len + 1))))
    return (FAILURE);
  return (get_prompt(ps1, shell));
}

static char	*g_args[] =
  {
    "echo",
    "-n",
    "-e",
    NULL,
    NULL
  };

int	show_prompt(const t_shell *shell)
{
  char	*color;

  g_args[3] = shell->prompt;
  (void)my_echo(g_args, shell->env);
  if (!my_strcmp("yes", my_getenv("DIR_PROMPT", shell->env)))
    {
      if ((color = my_getenv("DIR_COLOR", shell->env))[0])
	{
	  g_args[3] = color;
	  my_echo(g_args, shell->env);
	}
	my_printf("[%s]%s", my_getenv("PWD", shell->env), NORMAL);
    }
  if (!my_strcmp("yes", my_getenv("NUM_PROMPT", shell->env)))
    {
      if ((color = my_getenv("NUM_COLOR", shell->env))[0])
	{
	  g_args[3] = color;
	  my_echo(g_args, shell->env);
	}
      my_printf("[%d]%s", shell->count, NORMAL);
    }
  return (1);
}
