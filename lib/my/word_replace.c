/*
** word_replace.c for libmy in /home/doumer_c/replace
**
** Made by clement doumergue
** Login   <doumer_c@epitech.net>
**
** Started on  Tue May 10 02:57:51 2016 clement doumergue
** Last update Mon Jun  6 11:53:20 2016 clement doumergue
*/

#include <stdlib.h>
#include <string.h>
#include "my.h"

int		count_word_occs(const char *str, const char *word)
{
  int		i;
  size_t	len;
  unsigned int	occ;

  len = my_strlen(word);
  if ((i = get_str_pos(str, word)) == FAILURE)
    return (0);
  occ = (IS_WORD_SEP(str[i + len])
	 && (i == 0 || IS_WORD_SEP(str[i - 1]))) ? 1 : 0;
  str += i + len;
  while ((i = get_str_pos(str, word)) != FAILURE)
    {
      if (IS_WORD_SEP(str[i + len]) && IS_WORD_SEP(str[i - 1]))
	occ += 1;
      str += len;
    }
  return (occ);
}

static char	*simple_replace_word(char *str, const char *orig,
				     const char *rep, int len)
{
  int		i;

  i = 0;
  while (str[i] != '\0')
    {
      if (!my_strncmp(str + i, orig, len) && (i == 0 || IS_WORD_SEP(str[i - 1]))
	  && IS_WORD_SEP(str[i + len]))
	{
	  my_strncpy(str + i, rep, len);
	  i += len;
	}
      else
	i += 1;
    }
  return (str);
}

static char	*resize_replace_word(char *str, const char *orig,
				     const char *rep, int *lens)
{
  char		*new;
  int		idx[2];

  if ((new = my_calloc(sizeof(char) * (lens[NEW] + 1))) == NULL)
    {
      free(str);
      return (NULL);
    }
  idx[WORD] = 0;
  idx[REP] = 0;
  while (str[idx[WORD]] && idx[REP] < lens[NEW])
    {
      if (!my_strncmp(str + idx[WORD], orig, lens[WORD])
	  && IS_BEGIN && IS_WORD_SEP(str[idx[WORD] + lens[WORD]]))
  	{
  	  my_strncpy(new + idx[REP], rep, lens[REP]);
  	  idx[WORD] += lens[WORD];
  	  idx[REP] += lens[REP];
  	}
      else
  	new[idx[REP]++] = str[idx[WORD]++];
    }
  free(str);
  new[lens[NEW]] = '\0';
  return (new);
}

char	*replace_word(char *str, const char *word, const char *rep)
{
  int	lens[3];
  int	occs;

  occs = count_word_occs(str, word);
  if (occs == 0)
    return (str);
  if ((lens[WORD] = my_strlen(word)) == (lens[REP] = my_strlen(rep)))
    return (simple_replace_word(str, word, rep, lens[WORD]));
  lens[NEW] = my_strlen(str) + occs * (lens[REP] - lens[WORD]);
  return (resize_replace_word(str, word, rep, lens));
}
