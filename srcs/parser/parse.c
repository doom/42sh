/*
** parse.c for mysh in /home/doumer_c/rendu/PSU_2015_minishell2
**
** Made by clement doumergue
** Login   <doumer_c@epitech.net>
**
** Started on  Fri Apr  8 11:41:28 2016 clement doumergue
** Last update Wed Jun  1 12:46:09 2016 szterg_r
*/

#include <stdlib.h>
#include "mysh.h"

t_tree		*parse_exp(char *input)
{
  int		ret;
  t_tree	*tree;

  if (count_char(input, '"') % 2)
    {
      (void)my_puterror(UNMATCHED_SYM, "\"");
      return (NULL);
    }
  tree = tree_with_exp(input, NONE);
  if (!tree)
    return (NULL);
  ret = delim_rule(tree);
  if (ret == -1 || ret == false)
    {
      release_tree(tree);
      return (NULL);
    }
  return (tree);
}
