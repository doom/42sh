/*
** utils.c for mysh in /home/doumer_c/rendu/PSU_2015_minishell2
** 
** Made by clement doumergue
** Login   <doumer_c@epitech.net>
** 
** Started on  Mon Mar 21 14:13:39 2016 clement doumergue
** Last update Tue May 31 21:00:13 2016 clement doumergue
*/

#include <sys/stat.h>
#include <unistd.h>
#include <stdbool.h>
#include "mysh.h"

int		dir_exists(const char *path)
{
  struct stat	info;

  if (stat(path, &info) == -1)
    return (FAILURE);
  if (S_ISDIR(info.st_mode))
    return (true);
  return (false);
}

char	*remove_comments(char *str)
{
  int	i;

  i = 0;
  while (str[i] != '\0' && str[i] != '#' && !is_empty(str + i))
    i += 1;
  str[i] = '\0';
  return (str);
}

bool	is_empty_invalid(const char *str)
{
  int	i;

  i = 0;
  while (str[i] != '\0')
    {
      if (my_strncmp(str + i, AND, my_strlen(AND)) == 0
	  || my_strncmp(str + i, OR, my_strlen(OR)) == 0)
	return (true);
      else if (!IS_SEP(str[i]))
	return (false);
      i += 1;
    }
  return (true);
}

bool		my_isatty(int fd)
{
  struct stat	info;

  if (fd != STDIN_FILENO)
    return (false);
  if (fstat(0, &info) == -1)
    return (false);
  if (S_ISCHR(info.st_mode))
    return (true);
  return (false);
}
