/*
** input.h for 42sh in /home/doumer_c/common/lib
**
** Made by clement doumergue
** Login   <doumer_c@epitech.net>
**
** Started on  Tue Apr 12 23:06:08 2016 clement doumergue
** Last update Sun Jun  5 19:46:45 2016 clement doumergue
*/

#ifndef INPUT_H_
# define INPUT_H_

# include "mysh.h"

# define PREMADE_NUM 7
# define BUFF_SIZE 10
# define SEQ_COUNT 11
# define FAILURE -1

typedef struct	s_line
{
  int		pos;
  int	        len;
  int	        size;
  char		*str;
}		t_line;

typedef struct	s_seq_handler
{
  char		*seq;
  int		(*func)(t_line *, t_shell *);
}		t_seq_handler;

/*
** ESCAPE SEQUENCES
*/
int		handle_seq(const char *buf, t_line *l, t_shell *sh);
int		put_seq(const char *cap);
int		init_line(t_line *line);
int		add_to_line(t_line *line, char *buff, t_shell *sh);
void		print_line(t_line *l, t_shell *sh);
void		update_line(t_line *l, char *str);

/*
** HANDLERS
*/
int		handle_backspace(t_line *, t_shell *);
int		handle_clear(t_line *, t_shell *);
int		handle_tab(t_line *, t_shell *);
int		handle_left(t_line *, t_shell *);
int		handle_right(t_line *, t_shell *);
int		handle_up(t_line *, t_shell *);
int		handle_down(t_line *, t_shell *);
int		handle_ctrlc(t_line *, t_shell *);
int		handle_ctrlk(t_line *, t_shell *);
int		handle_ctrla(t_line *l, t_shell *sh);
int		handle_ctrle(t_line *l, t_shell *sh);
int		autocomplete(t_line *, t_shell *);

#endif /* !INPUT_H_ */
