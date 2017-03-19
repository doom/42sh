/*
** get_file.c for libmy in /home/doumer_c/Desktop/real_home/doumer_c/rendu/PSU_2015_minishell1
** 
** Made by clement doumergue
** Login   <doumer_c@epitech.net>
** 
** Started on  Tue Jan 12 13:42:09 2016 clement doumergue
** Last update Tue Apr  5 23:19:33 2016 clement doumergue
*/

#include <unistd.h>
#include <stdlib.h>
#include "my.h"

char	*get_file(const char *dir, const char *file)
{
  char	*new;
  int	d_len;
  int	len;

  if (dir == NULL || file == NULL)
    return (NULL);
  d_len = my_strlen(dir);
  len = d_len + my_strlen(file) + ((dir[d_len - 1] != '/') ? 2 : 1);
  if ((new = my_xmalloc(sizeof(*new) * len)) == NULL)
    return (NULL);
  my_strcpy(new, dir);
  if (dir[d_len - 1] != '/')
    new[d_len] = '/';
  my_strcpy(new + d_len + ((dir[d_len - 1] != '/') ? 1 : 0), file);
  if (access(new, X_OK) != -1)
    return (new);
  free(new);
  return (NULL);
}
