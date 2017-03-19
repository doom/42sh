/*
** input.c for 42sh in /home/doumer_c/common/lib
**
** Made by clement doumergue
** Login   <doumer_c@epitech.net>
**
** Started on  Tue Apr 12 20:31:34 2016 clement doumergue
** Last update Fri Jun  3 00:47:51 2016 clement doumergue
*/

#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include "input.h"
#include "mysh.h"

char		*read_command(t_shell *sh)
{
  int		ret;
  t_line	line;
  char		buffer[5];

  if (init_line(&line) == FAILURE)
    return (NULL);
  memset(buffer, '\0', sizeof(buffer));
  while (buffer[0] != 10)
    {
      memset(buffer, '\0', sizeof(buffer));
      if (read(sh->fd, buffer, 4) == -1 || buffer[0] == 4)
	{
	  free(line.str);
	  return (NULL);
	}
      if (buffer[0] != 10)
	{
	  if ((ret = handle_seq(buffer, &line, sh)) == true || ret == FAILURE)
	    my_printf("%s", buffer);
	  if (ret == FAILURE && line.str)
	    add_to_line(&line, buffer, sh);
	}
    }
  return ((line.str) ? line.str : my_strdup(""));
}
