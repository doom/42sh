/*
** autocomplete.h for 42sh in /home/doumer_c/rendu/PSU_2015_42sh/minishell2
** 
** Made by clement doumergue
** Login   <doumer_c@epitech.net>
** 
** Started on  Wed May  4 01:30:27 2016 clement doumergue
** Last update Tue Aug 30 15:15:20 2016 clement doumergue
*/

#ifndef AUTOCOMPLETE_H_
# define AUTOCOMPLETE_H_

# include <sys/ioctl.h>
# include "double_list.h"
# include "input.h"

# define IS_CUR_OR_PRNT(x) (x[0] == '.' && (!x[1] || (x[1] == '.' && !x[2])))

typedef struct		s_file
{
  char			*name;
  unsigned char		type;
}			t_file;

typedef struct		s_comp_tab
{
  const t_dblist	*source;
  const t_elem		*cur;
  int			width;
  int			height;
  int			step_x;
}			t_comp_tab;

void	init_comp_tab(t_comp_tab *tab, const struct winsize *s,
		      const t_dblist *completions);
void	print_tab(const t_comp_tab *tab);
void	hide_tab(const t_comp_tab *tab);
char	show_comptab(const t_dblist *completions, t_line *l);

t_file	*new_file(const char *name, unsigned char type);
void	free_file(t_file *file);
void	show_file(t_file *file, int space);
int	cmp_files(const t_file *a, const t_file *b);
bool	is_at_cmd(const t_line *l);
char	*last_item(const t_line *l);
char	*last_word(const t_line *l);

#endif /* !AUTOCOMPLETE_H_ */
