/*
** get_next_line.c for get_next_line in /home/doumer_c/rendu/CPE_2015_getnextline
**
** Made by clement doumergue
** Login   <doumer_c@epitech.net>
**
** Started on  Thu Jan  7 13:15:22 2016 clement doumergue
** Last update Sun Jan 17 23:43:00 2016 clement doumergue
*/

#include <stdlib.h>
#include <unistd.h>
#include "get_next_line.h"

static int	my_resize_line(t_line *line, int add_size)
{
  int		i;
  char		*new;

  if (line->buff == NULL)
    return (0);
  else if (line->pos == 0)
    {
      line->buff[0] = '\0';
      return (0);
    }
  if ((new = malloc(sizeof(*line->buff) * (line->pos + add_size + 1))) == NULL)
    {
      line->buff = NULL;
      return (-1);
    }
  i = 0;
  while (i < line->pos)
    {
      new[i] = line->buff[i];
      i = i + 1;
    }
  free(line->buff);
  line->buff = new;
  line->buff[i] = '\0';
  return (0);
}

static int	my_append_to_line(t_line *line, char *buffer, int *cur)
{
  while (cur[0] < cur[1] && buffer[cur[0]] != '\n')
    {
      line->buff[line->pos] = buffer[cur[0]];
      line->pos += 1;
      cur[0] += 1;
    }
  if (cur[0] < cur[1] && buffer[cur[0]++] == '\n')
    return (1);
  return (0);
}

static char	*my_final_resize(t_line *line, char has_eol)
{
  if (line->pos > 0)
    my_resize_line(line, 0);
  else if (has_eol != 0)
    {
      free(line->buff);
      if ((line->buff = malloc(sizeof(*line->buff))) != NULL)
	line->buff[0] = '\0';
    }
  else
    {
      free(line->buff);
      line->buff = NULL;
    }
  return (line->buff);
}

char		*get_next_line(const int fd)
{
  static char	buff[READ_SIZE];
  t_line	line;
  static int	cur[2];
  char		should_ret;

  if ((line.buff = malloc(sizeof(*line.buff) * (READ_SIZE + 1))) == NULL)
    return (NULL);
  line.pos = 0;
  while (((should_ret = my_append_to_line(&line, buff, cur)) == 0)
	 && (cur[1] = read(fd, buff, READ_SIZE)) > 0)
    {
      if (my_resize_line(&line, cur[1]) == -1)
	{
	  line.pos = -1;
	  break;
	}
      cur[0] = 0;
    }
  if (should_ret != 0)
    return (my_final_resize(&line, 1));
  else if (cur[1] == -1)
    line.pos = -1;
  return (my_final_resize(&line, 0));
}
