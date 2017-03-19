/*
** autocomplete.c for 42sh in /home/doumer_c/rendu/PSU_2015_42sh/minishell2
**
** Made by clement doumergue
** Login   <doumer_c@epitech.net>
**
** Started on  Sat Apr 30 22:33:10 2016 clement doumergue
** Last update Tue Aug 30 15:16:11 2016 clement doumergue
*/

#include <stdlib.h>
#include <stdbool.h>
#include <dirent.h>
#include <sys/types.h>
#include "autocomplete.h"

static const char	*g_bltns[] =
  {
    "cd",
    "printenv",
    "setenv",
    "unsetenv",
    "env",
    "alias",
    "unalias",
    "echo",
    "history",
    "exit",
    NULL
  };

int		add_file(t_dblist *files, const char *name, unsigned char type)
{
  t_file	*f;

  if ((f = new_file(name, type)) == NULL)
    return (FAILURE);
  return (append_to_dblist(files, f));
}

t_dblist	*complete_word(DIR *dir, const char *word, bool at_cmd)
{
  register int	len;
  t_dblist	*files;
  struct dirent	*entry;
  int		i;

  len = my_strlen(word);
  if ((files = init_dblist()) == NULL)
    return (NULL);
  while ((entry = readdir(dir)) != NULL)
    if (!my_strncmp(entry->d_name, word, len))
      if (!IS_CUR_OR_PRNT(entry->d_name)
	  && add_file(files, entry->d_name, entry->d_type) == FAILURE)
	{
	  release_dblist(files, &free_file);
	  return (NULL);
	}
  i = (at_cmd) ? -1 : 9;
  while (g_bltns[++i] != NULL)
    if (!my_strncmp(g_bltns[i], word, len))
      if (add_file(files, g_bltns[i], DT_REG) == FAILURE)
	{
	  release_dblist(files, &free_file);
	  return (NULL);
	}
  return (files);
}

static DIR	*get_dir(const t_line *l, bool *at_cmd)
{
  DIR		*dir;
  char		*word;
  int		pos;

  if ((*at_cmd = is_at_cmd(l)))
    return (opendir("/usr/bin"));
  word = last_word(l);
  if ((pos = get_last_char(word, '/')) == -1)
    {
      free(word);
      return (opendir("."));
    }
  word[pos] = '\0';
  dir = (pos == 0) ? opendir("/") : opendir(word);
  free(word);
  return (dir);
}

int		autocomplete(t_line *l, t_shell *sh)
{
  t_dblist	*completions;
  char		*word;
  DIR		*dir;
  char		add[2];
  bool		at_cmd;

  if (l->len == 0 || (dir = get_dir(l, &at_cmd)) == NULL
      || (word = last_item(l)) == NULL)
    return (FAILURE);
  completions = complete_word(dir, word, at_cmd);
  closedir(dir);
  free(word);
  if (!completions || completions->size == 0)
    {
      release_dblist(completions, &free_file);
      return (FAILURE);
    }
  sort_dblist(completions, &cmp_files);
  add[1] = '\0';
  add[0] = show_comptab(completions, l);
  release_dblist(completions, &free_file);
  if (add[0] != 0)
    add_to_line(l, add, sh);
  print_line(l, sh);
  return (SUCCESS);
}
