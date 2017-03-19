/*
** cd.c for mysh in /home/doumer_c/Desktop/real_home/doumer_c/rendu/PSU_2015_minishell1
** 
** Made by clement doumergue
** Login   <doumer_c@epitech.net>
** 
** Started on  Tue Jan  5 00:17:33 2016 clement doumergue
** Last update Sun Jun  5 00:19:13 2016 clement doumergue
*/

#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include "mysh.h"

static char	*orig = NULL;

static char	*my_cat_paths(char *base, char *add)
{
  char		*new;
  int		base_len;
  int		add_len;

  if (base == NULL || add == NULL)
    return (NULL);
  if (dir_exists(base) == 0)
    return (NULL);
  base_len = my_strlen(base);
  add_len = my_strlen(add);
  if ((new = my_xmalloc(sizeof(*new) * (base_len + add_len + 2))) == NULL)
    return (NULL);
  my_strncpy(new, base, base_len);
  new[base_len] = '/';
  my_strncpy(new + base_len + 1, add, add_len);
  new[base_len + add_len + 1] = '\0';
  return (new);
}

static void	clean_path(char *path)
{
  int		i;
  int		count;
  bool		no_slash;
  char		*slash_ptr;

  count = 0;
  if ((i = my_strlen(path)) < 3)
    return ;
  no_slash = false;
  while (i >= 3 && (!my_strcmp("../", path + i - 3)
		    || ((no_slash = true)
			&& !my_strcmp("..", path + i - 2))))
    {
      path[i - ((no_slash) ? 2 : 3)] = '\0';
      i -= (no_slash) ? 2 : 3;
      count += 1;
      no_slash = false;
    }
  if (!count++ || count_char(path, '/') < count)
    return ;
  while (count--)
    if ((slash_ptr = strrchr(path, '/')) != NULL)
      *(slash_ptr + ((count) ? 0 : 1)) = '\0';
}

static void	update_wdvars(char *new, t_dblist *env)
{
  update_var_value(env, "OLDPWD", my_getenv("PWD", env));
  update_var_value(env, "PWD", new);
}

int		update_dir(char *new, t_dblist *env)
{
  clean_path(new);
  if (chdir(new) == FAILURE)
    {
      my_puterror("%s: %s.\n", orig, strerror(errno));
      free(orig);
      orig = NULL;
      return (FAILURE);
    }
  update_wdvars(new, env);
  free(orig);
  orig = NULL;
  return (SUCCESS);
}

int	my_cd(char **args, t_dblist *env)
{
  char	*cur;
  char	*new;

  if (!orig)
    orig = my_strdup(args[1]);
  if (!args || !args[0] || !args[1])
    return (update_dir(my_getenv("HOME", env), env));
  if (my_strcmp(args[1], "-") == 0)
    return (update_dir(my_strdup(my_getenv("OLDPWD", env)), env));
  if (args[1][0] == '/')
    return (update_dir(args[1], env));
  cur = getcwd(NULL, 512);
  if (cur == NULL || (new = my_cat_paths(cur, args[1])) == NULL)
    return (FAILURE);
  free(cur);
  free(args[1]);
  args[1] = new;
  return (my_cd(args, env));
}
