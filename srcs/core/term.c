/*
** term.c for 42sh in /home/doumer_c/rendu/PSU_2015_42sh/minishell2
** 
** Made by clement doumergue
** Login   <doumer_c@epitech.net>
** 
** Started on  Mon Apr 25 22:44:20 2016 clement doumergue
** Last update Tue May 31 21:06:16 2016 clement doumergue
*/

#include <stdlib.h>
#include <term.h>
#include <termios.h>
#include <sys/termios.h>
#include <sys/ioctl.h>
#include <ncurses.h>
#include "input.h"
#include "mysh.h"

int	reset_term(struct termios *term)
{
  put_seq("ke");
  put_seq("ks");
  term->c_lflag = (ICANON | ECHO | ISIG);
  term->c_cc[VMIN] = 2;
  term->c_cc[VTIME] = 10;
  if (tcsetattr(0, TCSADRAIN, term) == -1)
    return (FAILURE);
  return (EXIT_SUCCESS);
}

int	init_term(struct termios *term, char *term_name)
{
  if (term_name == NULL || tgetent(NULL, term_name) != 1
      || tcgetattr(0, term) == -1)
    return (FAILURE);
  term->c_lflag &= ~(ICANON);
  term->c_lflag &= ~(ECHO);
  term->c_lflag &= ~(ISIG);
  term->c_cc[VMIN] = 1;
  term->c_cc[VTIME] = 0;
  if (tcsetattr(0, TCSADRAIN, term) == -1)
    return (FAILURE);
  put_seq("ks");
  return (EXIT_SUCCESS);
}
