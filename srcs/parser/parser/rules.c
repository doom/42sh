/*
** parse.c for mysh in /home/doumer_c/rendu/PSU_2015_minishell2
** 
** Made by clement doumergue
** Login   <doumer_c@epitech.net>
** 
** Started on  Fri Apr  8 11:03:29 2016 clement doumergue
** Last update Wed May 25 15:14:11 2016 clement doumergue
*/

#include <stdlib.h>
#include "mysh.h"

int	lredir_rule(t_tree *root)
{
  int	pos;
  int	len;

  pos = get_last_pos(root->exp, LRED);
  if (pos == -1)
    return (drredir_rule(root) == true);
  len = my_strlen(LRED);
  my_memset(root->exp + pos, '\0', len);
  if (is_empty_invalid(root->exp + pos + len) || is_empty_invalid(root->exp))
    return (my_puterror("Invalid null command.\n"));
  if (make_subtrees(root, pos + len, LRED_OP) == false)
    return (false);
  return (true);
}

int	dlredir_rule(t_tree *root)
{
  int	pos;
  int	len;

  pos = get_last_pos(root->exp, DLRED);
  if (pos == -1)
    return (lredir_rule(root) == true);
  len = my_strlen(DLRED);
  my_memset(root->exp + pos, '\0', len);
  if (is_empty_invalid(root->exp + pos + len)
      || is_empty_invalid(root->exp))
    return (my_puterror("Invalid null command.\n"));
  if (make_subtrees(root, pos + len, DLRED_OP) == false)
    return (false);
  return (true);
}

int	pipe_rule(t_tree *root)
{
  int	pos;
  int	len;

  pos = get_last_pos(root->exp, PIPE);
  if (pos == -1)
    return (dlredir_rule(root) == true);
  len = my_strlen(PIPE);
  my_memset(root->exp + pos, '\0', len);
  if (is_empty_invalid(root->exp + pos + len)
      || is_empty_invalid(root->exp))
    return (my_puterror("Invalid null command.\n"));
  if (make_subtrees(root, pos + len, PIPE_OP) == false)
    return (false);
  return (pipe_rule(root->left) == true && pipe_rule(root->right) == true);
}

int	andor_rule(t_tree *root)
{
  int	max;
  int	pos[2];
  int	len;

  max = MY_MAX((pos[0] = get_last_pos(root->exp, AND)),
	       (pos[1] = get_last_pos(root->exp, OR)));
  if (max == -1)
    return (pipe_rule(root) == true);
  len = my_strlen(AND);
  my_memset(root->exp + max, '\0', len);
  if (is_empty_invalid(root->exp + max + len) ||
      is_empty_invalid(root->exp))
    return (my_puterror("Invalid null command.\n"));
  if (make_subtrees(root, max + len, (pos[0] == max) ? AND_OP : OR_OP) == false)
    return (false);
  return (andor_rule(root->left) == true && andor_rule(root->right) == true);
}

int	delim_rule(t_tree *root)
{
  int	pos;
  int	len;

  pos = get_last_pos(root->exp, DELIM);
  if (pos == -1)
    return (andor_rule(root) == true);
  len = my_strlen(DELIM);
  my_memset(root->exp + pos, '\0', len);
  if (make_subtrees(root, pos + len, DELIM_OP) == false)
    return (false);
  return (delim_rule(root->left) == true && delim_rule(root->right) == true);
}
