/*
** globbing.c for 42sh in /home/doumer_c/rendu/PSU_2015_42sh
** 
** Made by clement doumergue
** Login   <doumer_c@epitech.net>
** 
** Started on  Wed Jun  1 12:46:54 2016 clement doumergue
** Last update Sun Jun  5 20:37:12 2016 clement doumergue
*/

#include <glob.h>
#include <stdlib.h>
#include <string.h>
#include "mysh.h"

void		my_glob_to_str(glob_t *pglob, char *str)
{
  size_t	i;
  size_t	pos;
  size_t	len;

  pos = 0;
  i = 0;
  while (i < pglob->gl_pathc)
    {
      len = my_strlen(pglob->gl_pathv[i]);
      strncpy(str + pos, pglob->gl_pathv[i], len);
      str[pos + len] = ' ';
      pos += len + 1;
      i += 1;
    }
  str[pos - 1] = '\0';
  globfree(pglob);
}

char		*replace_pattern(char *exp, char *pattern)
{
  glob_t	pglob;
  char		*new;
  int		len;
  unsigned int 	i;

  if (strchr(pattern, '"'))
    return (exp);
  if (glob(pattern, GLOB_MARK | GLOB_TILDE | GLOB_BRACE, NULL, &pglob) != 0)
    {
      my_puterror(GLOB_ERROR);
      return (exp);
    }
  len = 0;
  i = 0;
  while (i < pglob.gl_pathc)
    len += my_strlen(pglob.gl_pathv[i++]);
  if (!(new = malloc(sizeof(char) * (len += pglob.gl_pathc))))
    {
      free(exp);
      return (NULL);
    }
  my_glob_to_str(&pglob, new);
  exp = replace_word(exp, pattern, new);
  free(new);
  return (exp);
}

static size_t	len_word(const char *str, const char *seps)
{
  size_t	len;

  len = 0;
  while (*str && is_instr(*str, seps) == false)
    {
      str++;
      len += 1;
    }
  return (len);
}

char		*replace_globs(char *exp)
{
  char		*dup;
  size_t	size;
  size_t       	len;
  size_t	pos;
  char		bk;

  if (!(dup = my_strdup(exp)))
    return (NULL);
  pos = 0;
  size = my_strlen(dup);
  while (pos < size)
    {
      bk = dup[pos + (len = len_word(dup + pos, " \t"))];
      dup[pos + len] = '\0';
      if (strchr(dup + pos, '*') || (strchr(dup + pos, '~'))
	  || (strchr(dup + pos, '[') && strchr(dup + pos, ']')))
	if (!(exp = replace_pattern(exp, dup + pos)))
	  return (NULL);
      dup[pos + len] = bk;
      pos += len;
      while (dup[pos] == ' ' || dup[pos] == '\t')
	pos += 1;
    }
  free(dup);
  return (exp);
}
