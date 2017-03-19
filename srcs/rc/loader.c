/*
** loader.c for  in /home/giraud_e/Rendu/SystemUnix/PSU_2015_42sh/srcs/rc
**
** Made by Louis Giraud
** Login   <giraud_e@epitech.net>
**
** Started on  Mon May 30 15:27:59 2016 Louis Giraud
** Last update Sun Jun  5 00:39:35 2016 clement doumergue
*/

#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "get_next_line.h"
#include "mysh.h"

static void	replace_first_equals(char *line)
{
  int		idx;

  idx = 0;
  while (line[idx] != '=' && line[idx] != '\0')
    idx++;
  if (line[idx] == '=')
    line[idx] = ' ';
}

static bool	line_is_a_comment(const char *line)
{
  int		idx;

  idx = 0;
  while (line[idx] == ' ' || line[idx] == '\t')
    line++;
  return ((line[idx] == '#'));
}

static int	myshrc_cmd(t_shell *shell,
			   char *line,
			   const char *token)
{
  if (my_strcmp(token, "export") == 0)
    {
      if (myshrc_export(shell->env, line) == FAILURE)
	return (my_puterror(INVALID_EXPORT, line));
      free(line);
    }
  else
    {
      if (my_strcmp(token, "alias") == 0)
	replace_first_equals(line);
      if (handle_input(line, shell) == FAILURE)
	return (my_puterror(INVALID_ALIAS, line));
    }
  return (SUCCESS);
}

int		open_myshrc(t_shell *shell)
{
  char		*exec;
  char		*line;
  char		*cpln;
  int		fd;

  if (update_var_value(shell->env, "PS1", ">") == FAILURE)
    return (FAILURE);
  if ((fd = open(RCFILE, O_RDONLY)) <= 0)
    return (SUCCESS);
  while ((line = get_next_line(fd)) != NULL)
    {
      if (line_is_a_comment(line) == false)
	{
	  if ((cpln = my_strdup(line)) != NULL
	      && (exec = strtok(line, RCLIM)) != NULL)
	    if (myshrc_cmd(shell, cpln, exec) == FAILURE)
	      return (FAILURE);
	}
      free(line);
    }
  return (SUCCESS);
}
