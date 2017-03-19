/*
** handlers.c for 42sh in /home/doumer_c/common/lib
** 
** Made by clement doumergue
** Login   <doumer_c@epitech.net>
** 
** Started on  Tue Apr 12 23:33:54 2016 clement doumergue
** Last update Mon May  2 19:03:47 2016 clement doumergue
*/

#include <curses.h>
#include <stdlib.h>
#include <string.h>
#include <termios.h>
#include <stdbool.h>
#include "my.h"
#include "input.h"

int	handle_backspace(t_line *l, t_shell *sh)
{
  if (l->pos > 0)
    {
      memmove(l->str + l->pos - 1, l->str + l->pos,
	      my_strlen(l->str + l->pos) + 1);
      l->pos -= 1;
      l->len -= 1;
      print_line(l, sh);
    }
  return (0);
}

int	handle_clear(t_line *l, t_shell *sh)
{
  if (put_seq("cl") == EXIT_SUCCESS)
    print_line(l, sh);
  return (0);
}

int	handle_left(t_line *l, __attribute__ ((unused)) t_shell *sh)
{
  if (l->pos)
    {
      if (put_seq("le") == EXIT_SUCCESS)
	l->pos -= 1;
    }
  else
    beep();
  return (0);
}

int	handle_right(t_line *l, __attribute__ ((unused)) t_shell *sh)
{
  if (l->pos < l->len)
    {
      if (put_seq("nd") == EXIT_SUCCESS)
	l->pos += 1;
    }
  else
    beep();
  return (0);
}

int	handle_up(t_line *l, t_shell *sh)
{
  if (sh->hist_cur && sh->hist_cur->prev)
    sh->hist_cur = sh->hist_cur->prev;
  else if (!sh->hist_cur && sh->history->last)
    sh->hist_cur = sh->history->last;
  else
    return (0);
  free(l->str);
  if ((l->str = my_strdup(sh->hist_cur->data)) == NULL)
    return (FAILURE);
  l->size = my_strlen(l->str);
  l->len = l->size;
  l->pos = l->len;
  print_line(l, sh);
  return (0);
}
