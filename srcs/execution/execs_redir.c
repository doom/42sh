/*
** execs_redir.c for mysh in /home/doumer_c/rendu/PSU_2015_minishell2
**
** Made by clement doumergue
** Login   <doumer_c@epitech.net>
**
** Started on  Fri Apr  8 18:46:25 2016 clement doumergue
** Last update Sat Jun  4 19:08:54 2016 clement doumergue
*/

#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <sys/fcntl.h>
#include "get_next_line.h"
#include "mysh.h"

int	exec_rredir(t_tree *left, t_tree *right, t_shell *sh)
{
  int	ret;
  int	rfd;
  int	bk[2];

  right->exp = cut_end(skip_blank(right->exp));
  if ((rfd = open(right->exp, O_WRONLY | O_CREAT | O_TRUNC,
		  S_IRUSR | S_IWUSR)) == FAILURE)
    return (my_puterror(OPEN_ERROR(right->exp)));
  if (prep_redir(rfd, STDOUT_FILENO, bk) == FAILURE)
    return (my_puterror("Failed to redirect command output.\n"));
  ret = execute_tree(left, sh);
  if (reset_redir(rfd, STDOUT_FILENO, bk) == FAILURE)
    return (my_puterror(RESET_FAILED));
  return (ret);
}

int	exec_drredir(t_tree *left, t_tree *right, t_shell *sh)
{
  int	ret;
  int	rfd;
  int	bk[2];

  right->exp = cut_end(skip_blank(right->exp));
  if ((rfd = open(right->exp, O_WRONLY | O_CREAT | O_APPEND,
		  S_IRUSR | S_IWUSR)) == FAILURE)
    return (my_puterror(OPEN_ERROR(right->exp)));
  prep_redir(rfd, STDOUT_FILENO, bk);
  ret = execute_tree(left, sh);
  reset_redir(rfd, STDOUT_FILENO, bk);
  return (ret);
}

int	exec_lredir(t_tree *left, t_tree *right, t_shell *sh)
{
  int	ret;
  int	rfd;
  int	bk[2];

  right->exp = cut_end(skip_blank(right->exp));
  if ((rfd = open(right->exp, O_RDONLY)) == FAILURE)
    return (my_puterror(OPEN_ERROR(right->exp)));
  if (prep_redir(rfd, STDIN_FILENO, bk) == FAILURE)
    return (my_puterror("Failed to take %s as input.\n"));
  ret = execute_tree(left, sh);
  if (reset_redir(rfd, STDIN_FILENO, bk) == FAILURE)
    return (my_puterror(RESET_FAILED));
  return (ret);
}

int	exec_dlredir(t_tree *left, t_tree *right, t_shell *sh)
{
  char	*buf;
  int	tfd;
  int	bk[2];
  int	ret;

  right->exp = cut_end(skip_blank(right->exp));
  if ((tfd = open("/tmp", O_TMPFILE | O_RDWR, S_IRUSR)) < 0)
    return (my_puterror(OPEN_FAIL));
  while (!my_printf("? ") && (buf = get_next_line(0)) != NULL
	 && my_strcmp(buf, right->exp))
    {
      (void)write(tfd, buf, strlen(buf));
      (void)write(tfd, "\n", 1);
      free(buf);
    }
  free(buf);
  if (lseek(tfd, 0, SEEK_SET) == FAILURE
      || prep_redir(tfd, STDIN_FILENO, bk) == FAILURE)
    return (my_puterror(DLRED_FAILED));
  ret = execute_tree(left, sh);
  if (reset_redir(tfd, STDIN_FILENO, bk) == FAILURE)
    return (my_puterror(RESET_FAILED));
  return (ret);
}
