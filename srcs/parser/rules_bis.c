/*
** rules_bis.c for mysh in /home/doumer_c/rendu/PSU_2015_minishell2
** 
** Made by clement doumergue
** Login   <doumer_c@epitech.net>
** 
** Started on  Sun Apr 10 15:06:39 2016 clement doumergue
** Last update Sun Jun  5 21:32:03 2016 clement doumergue
*/

#include <stdlib.h>
#include "mysh.h"

int	rredir_rule(t_tree *root)
{
  int	pos;
  int	len;

  pos = get_last_pos(root->exp, RRED);
  if (pos == -1)
    return (true);
  if (is_begin(root->exp, pos))
    return (move_words(root->exp + pos, RRED) ? rredir_rule(root) : FAILURE);
  len = my_strlen(RRED);
  my_memset(root->exp + pos, '\0', len);
  if (is_empty_invalid(root->exp + pos + len) || is_empty_invalid(root->exp))
    return (my_puterror("Invalid null command.\n"));
  if (make_subtrees(root, pos + len, RRED_OP) == false)
    return (false);
  return (true);
}

int    drredir_rule(t_tree *root)
{
  int	pos;
  int	len;

  pos = get_last_pos(root->exp, DRRED);
  if (pos == -1)
    return (rredir_rule(root) == true);
  if (is_begin(root->exp, pos))
    return (move_words(root->exp + pos, DRRED) ? drredir_rule(root) : FAILURE);
  len = my_strlen(DRRED);
  my_memset(root->exp + pos, '\0', len);
  if (is_empty_invalid(root->exp + pos + len)
      || is_empty_invalid(root->exp))
    return (my_puterror("Invalid null command.\n"));
  if (make_subtrees(root, pos + len, DRRED_OP) == false)
    return (false);
  return (true);
}

int	lredir_rule(t_tree *root)
{
  int	pos;
  int	len;

  pos = get_last_pos(root->exp, LRED);
  if (pos == -1)
    return (drredir_rule(root) == true);
  if (is_begin(root->exp, pos))
    return (move_words(root->exp + pos, LRED) ? lredir_rule(root) : FAILURE);
  len = my_strlen(LRED);
  my_memset(root->exp + pos, '\0', len);
  if (is_empty_invalid(root->exp + pos + len) || is_empty_invalid(root->exp))
    return (my_puterror("Invalid null command.\n"));
  if (make_subtrees(root, pos + len, LRED_OP) == false)
    return (false);
  return (true);
}
