/*
** display.c for 42sh in /home/doumer_c/rendu/PSU_2015_42sh/minishell2
** 
** Made by clement doumergue
** Login   <doumer_c@epitech.net>
** 
** Started on  Tue May  3 11:10:05 2016 clement doumergue
** Last update Wed Aug 31 12:17:59 2016 clement doumergue
*/

#include <ncurses.h>
#include <unistd.h>
#include <string.h>
#include "autocomplete.h"

static void	handle_autocomp_input(const char *buf, t_comp_tab *t)
{
  char		*seq;

  seq = tigetstr("kcub1");
  if (!my_strncmp(buf, seq, my_strlen(seq)) && t->cur->prev)
    t->cur = t->cur->prev;
  seq = tigetstr("kcuf1");
  if ((!my_strncmp(buf, seq, my_strlen(seq))
       || !my_strncmp(buf, "\t", 1)) && t->cur->next)
    t->cur = t->cur->next;
}

static char	*prompt_completion(t_comp_tab *tab, char *type)
{
  char		buf[4];

  put_seq("vi");
  print_tab(tab);
  memset(buf, '\0', sizeof(buf));
  while (read(0, buf, 3) > 0 && buf[0] != '\n' && buf[0] != 'q')
    {
      handle_autocomp_input(buf, tab);
      memset(buf, '\0', sizeof(buf));
      hide_tab(tab);
      print_tab(tab);
    }
  hide_tab(tab);
  put_seq("ve");
  *type = ((t_file *)tab->cur->data)->type;
  return ((buf[0] != 'q') ? ((t_file *)tab->cur->data)->name : NULL);
}

char			show_comptab(const t_dblist *completions, t_line *l)
{
  t_comp_tab		tab;
  struct winsize	size;
  const char		*result;
  char			type;

  if (completions->size == 1)
    {
      result = ((t_file *)completions->first->data)->name;
      type = ((t_file *)completions->first->data)->type;
    }
  else
    {
      if (ioctl(0, TIOCGWINSZ, &size) == FAILURE)
	return (0);
      init_comp_tab(&tab, &size, completions);
      if (tab.height > size.ws_row)
	{
	  my_printf("\nToo many completions, please be more precise\n");
	  return (0);
	}
      if ((result = prompt_completion(&tab, &type)) == NULL)
	return (0);
    }
  update_line(l, replace_prev_word(l->str, l->pos, result));
  return ((type == 4) ? '/' : ' ');
}
