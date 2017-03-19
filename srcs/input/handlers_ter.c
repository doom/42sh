/*
** handlers_ter.c for 42sh in /home/doumer_c/rendu/PSU_2015_42sh
** 
** Made by clement doumergue
** Login   <doumer_c@epitech.net>
** 
** Started on  Wed Jun  1 01:51:38 2016 clement doumergue
** Last update Wed Jun  1 23:43:30 2016 clement doumergue
*/

#include "input.h"

int	handle_ctrle(t_line *l, t_shell *sh)
{
  if (l->pos < l->len)
    {
      while (++l->pos < l->len)
	put_seq("le");
      print_line(l, sh);
    }
  return (SUCCESS);
}
