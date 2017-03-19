/*
** my_split.c for libmy in /home/doumer_c/rendu/PSU_2015_minishell2
**
** Made by clement doumergue
** Login   <doumer_c@epitech.net>
**
** Started on  Mon Mar 21 23:54:57 2016 clement doumergue
** Last update Sun Jun  5 18:45:00 2016 roman sztergbaum
*/

#include <stdlib.h>
#include "string.h"
#include "my.h"

bool		is_instr(char c, const char *str)
{
  int		i;

  i = 0;
  while (str[i] != '\0' && str[i] != c)
    i += 1;
  return (str[i] == c);
}

static int	get_word_len(const char *str, const char *seps)
{
  int		i;
  int		decrease;

  decrease = 0;
  i = 0;
  while (str[i] != '\0' && is_instr(str[i], seps) == false)
    {
      if (str[i] == '"')
	{
	  i += 1;
	  while (str[i] != '"')
	    i += 1;
	  decrease += 2;
	}
      i += 1;
    }
  return (i - decrease);
}

int		count_words(const char *str, const char *seps)
{
  int		i;
  int		len;

  len = 0;
  i = 0;
  while (str[i] != '\0')
    {
      if (i == 0 || (is_instr(str[i], seps) == 0 && is_instr(str[i - 1], seps)))
	len += 1;
      if (str[i] == '"')
	while (str[++i] != '"');
      i += 1;
    }
  return (len);
}

static int	write_str_in_tab(char **tab,
				 const char *str,
				 int pos,
				 const char *seps)
{
  int		len;
  int		i;
  int		k;

  if ((len = get_word_len(str, seps)) == 0 && !strchr(seps, ':'))
    return (FAILURE);
  if ((tab[pos] = malloc(sizeof(*str) * (len + 1))) == NULL)
    return (FAILURE);
  i = 0;
  k = 0;
  while (k < len && str[i] && !is_instr(str[i], seps))
    {
      if (str[i] == '"')
	{
	  while (str[++i] != '"')
	    tab[pos][k++] = str[i];
	}
      else
	tab[pos][k++] = str[i];
      i += 1;
    }
  tab[pos][len] = '\0';
  while (str[i] != '\0' && is_instr(str[i], seps))
    i += 1;
  return (i);
}

char	**my_split(const char *str, const char *seps)
{
  char	**tab;
  int	size;
  int	i;
  int	j;
  int	skip;
  int	len;

  if (str == NULL || seps == NULL || count_char(str, '"') % 2)
    return (NULL);
  size = count_words(str, seps);
  if ((tab = malloc((size + 1) * sizeof(*tab))) == NULL)
    return (NULL);
  memset(tab, '\0', sizeof(*tab));
  len = my_strlen(str);
  i = 0;
  j = 0;
  while (i < len)
    {
      if ((skip = write_str_in_tab(tab, str + i, j++, seps)) == FAILURE)
	return (NULL);
      i += skip;
    }
  tab[size] = NULL;
  return (tab);
}
