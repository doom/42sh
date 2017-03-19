/*
** word_replace_prev.c for libmy in /home/doumer_c/replace
** 
** Made by clement doumergue
** Login   <doumer_c@epitech.net>
** 
** Started on  Wed May 11 01:30:29 2016 clement doumergue
** Last update Wed Jun  1 18:16:04 2016 clement doumergue
*/

#include <stdlib.h>
#include "my.h"

static int	prev_word_len(const char *str, int pos)
{
  int		len;

  len = 0;
  while (pos-- && !IS_WORD_SEP(str[pos]))
    len += 1;
  return (len);
}

char	*replace_prev_word(char *str, int pos, const char *rep)
{
  char	*new;
  int	len;
  int	len_rep;

  if ((len = prev_word_len(str, pos)) == (len_rep = my_strlen(rep)))
    return (my_strncpy(str + pos - len, rep, len_rep) - pos + len);
  if ((new = malloc(sizeof(char)
		    * (my_strlen(str) + len_rep - len + 1))) == NULL)
    {
      free(str);
      return (NULL);
    }
  my_strncpy(new, str, pos - len);
  my_strncpy(new + pos - len, rep, len_rep);
  my_strcpy(new + pos - len + len_rep, str + pos);
  free(str);
  return (new);
}
