/*
** seqs.c for 42sh in /home/doumer_c/common/lib
**
** Made by clement doumergue
** Login   <doumer_c@epitech.net>
**
** Started on  Wed Apr 13 14:44:56 2016 clement doumergue
** Last update Wed Jun  1 12:47:46 2016 szterg_r
*/

#include <stdlib.h>
#include <unistd.h>
#include <termios.h>
#include <term.h>
#include <curses.h>
#include "input.h"

static const char	premade_seqs[][PREMADE_NUM] =
  {
    {127, 0},
    {'\f', 0},
    {'\t', 0},
    {3, 0},
    {'\v', 0},
    {1, 0},
    {5, 0}
  };

static t_seq_handler	seqs[] =
  {
    {NULL, &handle_backspace},
    {NULL, &handle_clear},
    {NULL, &handle_tab},
    {NULL, &handle_ctrlc},
    {NULL, &handle_ctrlk},
    {NULL, &handle_ctrla},
    {NULL, &handle_ctrle},
    {NULL, &handle_left},
    {NULL, &handle_right},
    {NULL, &handle_up},
    {NULL, &handle_down}
  };

static const char	*caps[] =
  {
    "kcub1",
    "kcuf1",
    "kcuu1",
    "kcud1",
    NULL
  };

int	my_putcap(int c)
{
  return (write(1, &c, 1));
}

int		put_seq(const char *cap)
{
  const char	*seq;

  seq = tgetstr(cap, NULL);
  if (!seq)
    return (FAILURE);
  tputs(seq, 0, &my_putcap);
  return (EXIT_SUCCESS);
}

int	init_seqs(void)
{
  int	i;
  char	*seq;

  i = -1;
  while (++i < PREMADE_NUM)
    if ((seqs[i].seq = my_strdup(premade_seqs[i])) == NULL)
      return (FAILURE);
  i -= 1;
  while (++i < SEQ_COUNT)
    {
      if ((seq = tigetstr(caps[i - PREMADE_NUM])) == NULL || seq == (char *)-1)
	return (FAILURE);
      if ((seqs[i].seq = my_strdup(seq)) == NULL)
	return (FAILURE);
    }
  return (0);
}

void	release_seqs(void)
{
  int	i;

  i = 0;
  while (i < SEQ_COUNT)
    free(seqs[i++].seq);
}

int	handle_seq(const char *buf, t_line *l, t_shell *sh)
{
  int	i;

  i = 0;
  while (i < SEQ_COUNT && my_strcmp(buf, seqs[i].seq))
    i += 1;
  return ((i < SEQ_COUNT) ? seqs[i].func(l, sh) : FAILURE);
}
