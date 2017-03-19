/*
** export.c for  in /home/giraud_e/Rendu/SystemUnix/PSU_2015_42sh/srcs/rc
**
** Made by Louis Giraud
** Login   <giraud_e@epitech.net>
**
** Started on  Mon May 30 16:00:43 2016 Louis Giraud
** Last update Tue May 31 16:09:16 2016 Louis Giraud
*/

#include <string.h>
#include <stdlib.h>
#include "mysh.h"

int		myshrc_export(t_dblist *env, const char *line)
{
  char		*var;
  char		*data;

  if ((var = strtok(NULL, "=")) == NULL
      || (data = strtok(NULL, GET_LIM(line))) == NULL)
    return (FAILURE);
  return (update_var_value(env, var, data));
}
