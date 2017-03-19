/*
** replace.c for libmy in /home/doumer_c/rendu/PSU_2015_42sh/minishell2
**
** Made by clement doumergue
** Login   <doumer_c@epitech.net>
**
** Started on  Thu May  5 13:19:22 2016 clement doumergue
** Last update Sat Jun  4 12:57:33 2016 szterg_r
*/

#include <stdlib.h>
#include "my.h"

int		count_occurences(const char *str, const char *sub)
{
  int		i;
  int		len;

  len = my_strlen(sub);
  if ((str = my_strstr(str, sub)) == NULL)
    return (0);
  str += len;
  i = 1;
  while ((str = my_strstr(str, sub)))
    {
      str += len;
      i += 1;
    }
  return (i);
}

char	*replace_all_words(char *s, const char *w, const char *rep)
{
  char	*new;
  int	len[3];
  int	i;
  int	k;

  len[0] = my_strlen(s) - ((len[1] = my_strlen(w)) - (len[2] = my_strlen(rep)))
    * count_occurences(s, w);
  if ((new = malloc(sizeof(char) * (len[0] + 1))) == NULL)
    return (NULL);
  k = 0;
  i = 0;
  while (i < my_strlen(s))
    {
      if (my_strncmp(s + i, w, len[1]) == 0)
	{
	  my_strncpy(new + k, rep, len[2]);
	  k += len[2];
	  i += len[1];
	}
      else
	new[k++] = s[i++];
    }
  new[k] = '\0';
  free(s);
  return (new);
}

char	*replace_first_word(char *s, const char *w, const char *rep)
{
  char	*new;
  char	*ptr;
  int	len[3];

  if ((ptr = my_strstr(s, w)) == NULL)
    return (s);
  len[0] = my_strlen(s) - ((len[2] = my_strlen(w)) - (len[1] = my_strlen(rep)));
  if ((new = malloc(sizeof(char) * (len[0] + 1))) == NULL)
    return (NULL);
  my_strncpy(new, s, ptr - s);
  my_strncpy(new + (ptr - s), rep, len[1]);
  my_strcpy(new + (ptr - s) + len[1], ptr + len[2]);
  free(s);
  return (new);
}
