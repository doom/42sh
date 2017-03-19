/*
** fd_config.c for mysh in /home/doumer_c/rendu/PSU_2015_minishell2
** 
** Made by clement doumergue
** Login   <doumer_c@epitech.net>
** 
** Started on  Sat Apr  9 16:08:28 2016 clement doumergue
** Last update Sat Jun  4 19:09:09 2016 clement doumergue
*/

#include <unistd.h>
#include <stdlib.h>
#include "mysh.h"

int	prep_redir(int rfd, int fd, int *bk)
{
  bk[0] = dup(fd);
  if (bk[0] == -1)
    return (FAILURE);
  return ((dup2(rfd, fd) == FAILURE) ? FAILURE : SUCCESS);
}

int	reset_redir(int rfd, int fd, int *bk)
{
  if (dup2(bk[0], fd) == FAILURE)
    return (FAILURE);
  close(rfd);
  close(bk[0]);
  return (SUCCESS);
}
