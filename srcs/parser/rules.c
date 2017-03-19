/*
** parse.c for mysh in /home/doumer_c/rendu/PSU_2015_minishell2
** 
** Made by clement doumergue
** Login   <doumer_c@epitech.net>
** 
** Started on  Fri Apr  8 11:03:29 2016 clement doumergue
** Last update Sun Jun  5 17:14:03 2016 clement doumergue
*/

#include <stdlib.h>
#include "mysh.h"

int	dlredir_rule(t_tree *root)
{
  int	pos;
  int	len;

  pos = get_last_pos(root->exp, DLRED);
  if (pos == -1)
    return (lredir_rule(root) == true);
  if (is_begin(root->exp, pos))
    return (move_words(root->exp + pos, DLRED) ? dlredir_rule(root) : FAILURE);
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

int     and_rule(t_tree *root)
{
  int	pos;
  int	len;

  pos = get_last_pos(root->exp, AND);
  if (pos == -1)
    return (pipe_rule(root) == true);
  len = my_strlen(AND);
  my_memset(root->exp + pos, '\0', len);
  if (make_subtrees(root, pos + len, AND_OP) == false)
    return (false);
  return (and_rule(root->left) == true && and_rule(root->right) == true);
}

int	or_rule(t_tree *root)
{
  int	pos;
  int	len;

  pos = get_last_pos(root->exp, OR);
  if (pos == -1)
    return (and_rule(root) == true);
  len = my_strlen(OR);
  my_memset(root->exp + pos, '\0', len);
  if (make_subtrees(root, pos + len, OR_OP) == false)
    return (false);
  return (or_rule(root->left) == true && or_rule(root->right) == true);
}

int	delim_rule(t_tree *root)
{
  int	pos;
  int	len;

  pos = get_last_pos(root->exp, DELIM);
  if (pos == -1)
    return (or_rule(root) == true);
  len = my_strlen(DELIM);
  my_memset(root->exp + pos, '\0', len);
  if (make_subtrees(root, pos + len, DELIM_OP) == false)
    return (false);
  return (delim_rule(root->left) == true && delim_rule(root->right) == true);
}
