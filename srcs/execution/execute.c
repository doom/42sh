/*
** execute.c for mysh in /home/doumer_c/rendu/PSU_2015_minishell2
** 
** Made by clement doumergue
** Login   <doumer_c@epitech.net>
** 
** Started on  Wed Apr  6 00:28:46 2016 clement doumergue
** Last update Sun Jun  5 16:38:52 2016 Cros
*/

#include <stdlib.h>
#include "mysh.h"

static int	(*g_funcstab[])(t_tree *, t_tree *, t_shell *) =
{
  &exec_delim,
  &exec_and,
  &exec_or,
  &exec_pipe,
  &exec_dlredir,
  &exec_lredir,
  &exec_drredir,
  &exec_rredir,
  NULL
};

void		print_infix(t_tree *tree, int depth)
{
  if (tree != NULL)
    {
      print_infix(tree->left, depth + 1);
      my_printf("depth: %d op: %d exp: %s\n", depth, tree->op, tree->exp);
      print_infix(tree->right, depth + 1);
    }
}

int		execute_tree(t_tree *tree, t_shell *sh)
{
  if (!tree)
    return (FAILURE);
  if (tree->op < NONE)
    return (g_funcstab[tree->op](tree->left, tree->right, sh));
  return (simple_command(skip_blank(tree->exp), sh));
}
