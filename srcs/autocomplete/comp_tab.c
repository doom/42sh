/*
** comp_tab.c for 42sh in /home/doumer_c/rendu/PSU_2015_42sh/minishell2
**
** Made by clement doumergue
** Login   <doumer_c@epitech.net>
**
** Started on  Thu May  5 02:47:17 2016 clement doumergue
** Last update Wed Jun  1 12:48:56 2016 szterg_r
*/

#include "my.h"
#include "autocomplete.h"

int		get_tab_width(const t_dblist *list)
{
  t_elem	*e;
  int		len;
  int		max;

  max = 0;
  e = list->first;
  while (e)
    {
      if ((len = my_strlen(((t_file *)e->data)->name)) > max)
	max = len;
      e = e->next;
    }
  return (max);
}

void	init_comp_tab(t_comp_tab *tab,
		      const struct winsize *s,
		      const t_dblist *completions)
{
  tab->step_x = get_tab_width(completions) + 1;
  tab->width = s->ws_col / tab->step_x;
  tab->height = completions->size / tab->width + 1;
  tab->source = completions;
  tab->cur = completions->first;
}

void		print_tab(const t_comp_tab *tab)
{
  t_elem	*e;
  int		x;
  t_file	*f;

  put_seq("do");
  put_seq("cr");
  e = tab->source->first;
  x = 0;
  while (e)
    {
      f = e->data;
      if (!my_strcmp(f->name, ((t_file *)tab->cur->data)->name))
	put_seq("mr");
      show_file(f, tab->step_x);
      put_seq("me");
      e = e->next;
      if (++x >= tab->width)
	{
	  put_seq("do");
	  put_seq("cr");
	  x = 0;
	}
    }
}

void	hide_tab(const t_comp_tab *tab)
{
  int	i;

  i = 0;
  while (i++ < tab->height)
    {
      put_seq("dl");
      put_seq("up");
    }
}
