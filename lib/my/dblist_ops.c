/*
** dblist_ops.c for libdoom in /home/doumer_c/libmy
**
** Made by clement doumergue
** Login   <doumer_c@epitech.net>
**
** Started on  Wed Jan 27 22:08:26 2016 clement doumergue
** Last update Sat Jun  4 16:38:47 2016 clement doumergue
*/

#include <stdlib.h>
#include "double_list.h"

t_elem		*create_elem(void *data)
{
  t_elem	*elem;

  if (data == NULL)
    return (NULL);
  if ((elem = my_xmalloc(sizeof(*elem))) == NULL)
    return (NULL);
  elem->data = data;
  return (elem);
}

int		append_to_dblist(t_dblist *list, void *data)
{
  t_elem	*elem;

  elem = create_elem(data);
  if (elem == NULL)
    return (FAILURE);
  elem->prev = list->last;
  elem->next = NULL;
  if (list->last != NULL)
    list->last->next = elem;
  else
    list->first = elem;
  list->last = elem;
  list->size += 1;
  return (SUCCESS);
}

t_elem_int	*create_elem_int(int data)
{
  t_elem_int	*elem;

  if ((elem = my_xmalloc(sizeof(*elem))) == NULL)
    return (NULL);
  elem->data = data;
  return (elem);
}

int		append_to_dblist_int(t_dblist_int *list, int data)
{
  t_elem_int	*elem;

  elem = create_elem_int(data);
  if (elem == NULL)
    return (FAILURE);
  elem->prev = list->last;
  elem->next = NULL;
  if (list->last != NULL)
    list->last->next = elem;
  else
    list->first = elem;
  list->last = elem;
  list->size += 1;
  return (SUCCESS);
}

void		*front_pop_from_dblist(t_dblist *l)
{
  char		*data;
  t_elem	*tmp;

  tmp = l->first;
  if (tmp == NULL)
    return (NULL);
  data = tmp->data;
  l->first = tmp->next;
  if (l->first)
    l->first->prev = NULL;
  else
    l->last = NULL;
  free(tmp);
  l->size -= 1;
  return (data);
}
