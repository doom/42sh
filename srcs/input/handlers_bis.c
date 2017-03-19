/*
** handlers_bis.c for 42sh in /home/doumer_c/common/lib
** 
** Made by clement doumergue
** Login   <doumer_c@epitech.net>
** 
** Started on  Wed Apr 13 17:41:59 2016 clement doumergue
** Last update Sun Jun  5 21:24:11 2016 clement doumergue
*/

#include <unistd.h>
#include <stdlib.h>
#include "input.h"

int	handle_down(t_line *l, t_shell *sh)
{
  bool	empty;

  empty = false;
  if (sh->hist_cur && sh->hist_cur->next)
    sh->hist_cur = sh->hist_cur->next;
  else
    {
      sh->hist_cur = NULL;
      empty = true;
    }
  free(l->str);
  if ((l->str = my_strdup((empty) ? "" : sh->hist_cur->data)) == NULL)
    return (FAILURE);
  l->size = my_strlen(l->str);
  l->len = l->size;
  l->pos = l->len;
  print_line(l, sh);
  return (SUCCESS);
}

int	handle_tab(t_line *l, t_shell *sh)
{
  return (autocomplete(l, sh));
}

int	handle_ctrlc(t_line *l, t_shell *sh)
{
  write(1, "\n", 1);
  free(l->str);
  sh->exit_status = 1;
  init_line(l);
  print_line(l, sh);
  return (SUCCESS);
}

int	handle_ctrlk(t_line *l, t_shell *sh)
{
  int	i;

  i = l->pos;
  while (i < l->len)
    l->str[i++] = '\0';
  l->len = l->pos;
  print_line(l, sh);
  return (SUCCESS);
}

int	handle_ctrla(t_line *l, t_shell *sh)
{
  if (l->pos)
    {
      while (--l->pos)
	put_seq("le");
      print_line(l, sh);
    }
  return (SUCCESS);
}
