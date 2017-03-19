/*
** dblist_utils.c for libdoom in /home/doumer_c/libmy
** 
** Made by clement doumergue
** Login   <doumer_c@epitech.net>
** 
** Started on  Wed Jan 27 22:08:50 2016 clement doumergue
** Last update Fri May 13 00:14:07 2016 clement doumergue
*/

#include <stdlib.h>
#include "double_list.h"

int		remove_elem(t_dblist *list, t_elem *elem)
{
  if (elem == NULL)
    return (SUCCESS);
  if (elem == list->first)
      list->first = elem->next;
  else
    elem->prev->next = elem->next;
  if (elem == list->last)
    list->last = elem->prev;
  else
    elem->next->prev = elem->prev;
  elem->next = NULL;
  elem->prev = NULL;
  free(elem->data);
  free(elem);
  list->size -= 1;
  return (SUCCESS);
}

t_elem		*get_elem_at_index(t_dblist *list, int idx)
{
  t_elem	*e;
  register int	i;

  i = 0;
  e = list->first;
  while (e && i++ < idx)
    e = e->next;
  return (e);
}

void	swap_elem(t_elem *a, t_elem *b)
{
  void	*c;

  c = a->data;
  a->data = b->data;
  b->data = c;
}

void		sort_dblist(t_dblist *list, int (*cmp)())
{
  t_elem	*a;
  t_elem	*b;

  if (list->size <= 1)
    return ;
  a = list->first;
  while (a->next != NULL)
    {
      b = a->next;
      while (b != NULL)
	{
	  if (cmp(a->data, b->data) > 0)
	    swap_elem(a, b);
	  b = b->next;
	}
      a = a->next;
    }
}
