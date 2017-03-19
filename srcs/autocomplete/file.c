/*
** file.c for 42sh in /home/doumer_c/rendu/PSU_2015_42sh
** 
** Made by clement doumergue
** Login   <doumer_c@epitech.net>
** 
** Started on  Thu May 12 23:11:21 2016 clement doumergue
** Last update Tue May 17 14:33:11 2016 clement doumergue
*/

#include <stdlib.h>
#include "autocomplete.h"

t_file		*new_file(const char *name, unsigned char type)
{
  t_file	*file;

  if ((file = malloc(sizeof(t_file))) == NULL
      || (file->name = my_strdup(name)) == NULL)
    {
      free(file);
      return (NULL);
    }
  file->type = type;
  return (file);
}

void		free_file(t_file *file)
{
  free(file->name);
  free(file);
}

char	*color_from_file_type(unsigned char type)
{
  if (type == 4)
    return (GREEN);
  return (WHITE);
}

void	show_file(t_file *file, int space)
{
  my_printf("%s", color_from_file_type(file->type));
  dputstr_left(1, file->name, space);
  my_printf("%s", NORMAL);
}

int	cmp_files(const t_file *a, const t_file *b)
{
  return (my_strcmp(a->name, b->name));
}
