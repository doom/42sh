/*
** tree.c for mysh in /home/doumer_c/rendu/PSU_2015_minishell2
** 
** Made by clement doumergue
** Login   <doumer_c@epitech.net>
** 
** Started on  Sat Apr  2 11:45:34 2016 clement doumergue
** Last update Wed May 25 14:55:57 2016 clement doumergue
*/

#include <stdlib.h>
#include "mysh.h"

t_tree		*init_tree(t_tree *left, t_tree *right)
{
  t_tree	*tree;

  if ((tree = malloc(sizeof(*tree))) == NULL)
    return (NULL);
  tree->left = left;
  tree->right = right;
  return (tree);
}

t_tree		*tree_with_exp(char *exp, te_op_type op)
{
  t_tree	*tree;

  if ((tree = init_tree(NULL, NULL)) == NULL)
    return (NULL);
  tree->op = op;
  tree->exp = exp;
  return (tree);
}

int		make_subtrees(t_tree *root, int pos, te_op_type op)
{
  root->left = tree_with_exp(root->exp, NONE);
  root->right = tree_with_exp(root->exp + pos, NONE);
  if (!root->left || !root->right)
    return (false);
  root->op = op;
  root->exp = NULL;
  return (true);
}

void	release_tree(t_tree *tree)
{
  if (tree)
    {
      release_tree(tree->left);
      release_tree(tree->right);
      free(tree);
    }
}
