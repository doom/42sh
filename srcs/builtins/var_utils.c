/*
** var_utils.c for mysh in /home/doumer_c/rendu/PSU_2015_minishell2
** 
** Made by clement doumergue
** Login   <doumer_c@epitech.net>
** 
** Started on  Wed Apr  6 15:07:31 2016 clement doumergue
** Last update Wed Apr  6 15:07:51 2016 clement doumergue
*/

#include <stdlib.h>
#include "double_list.h"

t_dblist	*env_to_dblist(char **tab)
{
  t_dblist	*list;
  int		i;

  if ((list = init_dblist()) == NULL)
    return (NULL);
  i = 0;
  while (tab[i] != NULL)
    {
      if (append_to_dblist(list, my_strdup(tab[i])) == FAILURE)
	{
	  release_dblist(list, &free);
	  return (NULL);
	}
      i += 1;
    }
  return (list);
}

t_elem		*var_by_name(const t_dblist *env, const char *name)
{
  t_elem	*e;
  char		*var;
  int		len;

  len = my_strlen(name);
  e = env->first;
  while (e != NULL)
    {
      var = e->data;
      if (my_strncmp(var, name, len) == 0 && var[len] == '=')
	return (e);
      e = e->next;
    }
  return (NULL);
}

int		update_var_value(t_dblist *env,
				 const char *name,
				 const char *value)
{
  t_elem	*e;
  char		*var;
  int		name_len;

  if (!name || !value)
    return (FAILURE);
  name_len = my_strlen(name);
  if ((var = malloc(sizeof(*var) * (name_len + my_strlen(value) + 2))) == NULL)
    return (FAILURE);
  my_strncpy(var, name, name_len);
  var[name_len] = '=';
  my_strcpy(var + name_len + 1, value);
  e = var_by_name(env, name);
  if (e == NULL)
    return (append_to_dblist(env, var));
  free(e->data);
  e->data = var;
  return (SUCCESS);
}

int		remove_var(t_dblist *env, const char *name)
{
  t_elem	*e;

  if (name == NULL)
    return (SUCCESS);
  e = var_by_name(env, name);
  return (remove_elem(env, e));
}

char		**env_to_tab(t_dblist *env)
{
  char		**tab;
  t_elem	*e;
  int		i;

  if ((tab = malloc(sizeof(*tab) * (env->size + 1))) == NULL)
    return (NULL);
  e = env->first;
  i = 0;
  while (e && i < env->size)
    {
      tab[i++] = e->data;
      e = e->next;
    }
  tab[i] = NULL;
  return (tab);
}
