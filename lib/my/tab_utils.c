/*
** free_tab.c for libmy in /home/doumer_c/rendu/PSU_2015_minishell1
**
** Made by clement doumergue
** Login   <doumer_c@epitech.net>
**
** Started on  Tue Jan 12 11:02:51 2016 clement doumergue
** Last update Sun Jun  5 11:35:46 2016 szterg_r
*/

#include <stdlib.h>
#include "my.h"

int	get_tab_size(char **tab)
{
  int	i;

  i = 0;
  while (tab[i] != NULL)
    i += 1;
  return (i);
}

int	replace_tab_entry(char **tab, int pos, char *new)
{
  if (tab == NULL || new == NULL)
    return (FAILURE);
  if (get_tab_size(tab) <= pos)
    return (FAILURE);
  free(tab[pos]);
  tab[pos] = new;
  return (SUCCESS);
}

void	show_tab(char **tab)
{
  int	i;

  if (tab == NULL)
    return ;
  i = 0;
  while (tab[i] != NULL)
    my_dprintf(1, "%s\n", tab[i++]);
}

void	free_tab(char **tab)
{
  int	i;

  if (tab == NULL)
    return ;
  i = 0;
  while (tab[i])
    free(tab[i++]);
  free(tab);
}
