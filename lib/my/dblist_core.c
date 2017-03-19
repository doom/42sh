/*
** dblist_core.c for libdoom in /home/doumer_c/libmy
** 
** Made by clement doumergue
** Login   <doumer_c@epitech.net>
** 
** Started on  Wed Jan 27 22:08:01 2016 clement doumergue
** Last update Sat Jun  4 16:35:15 2016 clement doumergue
*/

#include <stdlib.h>
#include "double_list.h"

t_dblist	*init_dblist(void)
{
  t_dblist	*list;

  if ((list = my_xmalloc(sizeof(*list))) == NULL)
    return (NULL);
  list->first = NULL;
  list->last = NULL;
  list->size = 0;
  return (list);
}

t_dblist_int	*init_dblist_int(void)
{
  t_dblist_int	*list;

  if ((list = my_xmalloc(sizeof(*list))) == NULL)
    return (NULL);
  list->first = NULL;
  list->last = NULL;
  list->size = 0;
  return (list);
}

void		release_dblist(t_dblist *list, void (*free_func)())
{
  t_elem	*tmp;

  if (!list)
    return ;
  while (list->first)
    {
      tmp = list->first;
      list->first = list->first->next;
      if (free_func != NULL)
	free_func(tmp->data);
      free(tmp);
    }
  list->first = NULL;
  list->last = NULL;
  free(list);
}

int		show_dblist(const t_dblist *list)
{
  t_elem	*cur;

  cur = list->first;
  while (cur)
    {
      my_dprintf(1, "%s\n", (char *)(cur->data));
      cur = cur->next;
    }
  return (SUCCESS);
}
