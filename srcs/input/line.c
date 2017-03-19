/*
** line.c for 42sh in /home/doumer_c/common/lib
**
** Made by clement doumergue
** Login   <doumer_c@epitech.net>
**
** Started on  Tue Apr 12 23:01:09 2016 clement doumergue
** Last update Wed Jun  1 13:59:44 2016 clement doumergue
*/

#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <termios.h>
#include <stdbool.h>
#include "my.h"
#include "input.h"

static int	resize_line(t_line *line)
{
  char		*new;

  line->size += BUFF_SIZE;
  if ((new = malloc(sizeof(char) * line->size)) == NULL)
    return (FAILURE);
  memset(new, '\0', line->size);
  my_strcpy(new, line->str);
  free(line->str);
  line->str = new;
  return (EXIT_SUCCESS);
}

int	add_to_line(t_line *line, char *buff, t_shell *sh)
{
  int	len;

  len = my_strlen(buff);
  if (line->len + len >= line->size)
    if (resize_line(line) == FAILURE)
      return (FAILURE);
  if (line->len == line->pos)
    my_strcpy(line->str + line->pos, buff);
  else
    {
      memmove(line->str + line->pos + len,
	      line->str + line->pos, line->len - line->pos);
      my_strncpy(line->str + line->pos, buff, len);
    }
  line->pos += len;
  line->len += len;
  print_line(line, sh);
  return (EXIT_SUCCESS);
}

void	update_line(t_line *l, char *str)
{
  l->str = str;
  l->len = my_strlen(l->str);
  l->size = l->len + 1;
  l->pos = l->len;
}

int	init_line(t_line *line)
{
  if ((line->str = malloc(sizeof(char) * (BUFF_SIZE + 1))) == NULL)
    return (FAILURE);
  memset(line->str, '\0', BUFF_SIZE + 1);
  line->pos = 0;
  line->len = 0;
  line->size = BUFF_SIZE;
  return (EXIT_SUCCESS);
}
