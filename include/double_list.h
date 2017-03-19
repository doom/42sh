/*
** double_list.h for libmy in /home/doumer_c/libmy
**
** Made by clement doumergue
** Login   <doumer_c@epitech.net>
**
** Started on  Wed Jan 27 21:50:54 2016 clement doumergue
** Last update Sat Jun  4 16:40:50 2016 clement doumergue
*/

#ifndef DOUBLE_LIST_H_
# define DOUBLE_LIST_H_

# include "my.h"

typedef struct	s_elem
{
  void		*data;
  struct s_elem	*prev;
  struct s_elem	*next;
}		t_elem;

typedef struct	s_dblist
{
  t_elem	*first;
  t_elem	*last;
  int		size;
}		t_dblist;

typedef struct		s_elem_int
{
  int			data;
  struct s_elem_int	*prev;
  struct s_elem_int	*next;
}			t_elem_int;

typedef struct	s_dblist_int
{
  t_elem_int	*first;
  t_elem_int	*last;
  int		size;
}		t_dblist_int;

/*
** CORE FUNCTIONS
*/
t_dblist	*init_dblist();
t_dblist_int	*init_dblist_int();
int		show_dblist(const t_dblist *list);
void		release_dblist(t_dblist *list, void (*free_func)());

/*
** BASIC PUSH/POP/ADD OPERATIONS
*/
int		append_to_dblist(t_dblist *list, void *data);
int		append_to_dblist_int(t_dblist_int *list,  int data);
t_elem		*create_var(const char *name, const char *value);
int		remove_elem(t_dblist *list, t_elem *e);
void		*front_pop_from_dblist(t_dblist *l);

/*
** ADVANCED OPERATIONS
*/
void		sort_dblist(t_dblist *list, int (*cmp)());
int		get_longest_len(const t_dblist *list);
t_elem		*get_elem_at_index(t_dblist *list, int idx);
t_elem		*get_var_by_name(t_dblist *list, const char *name);
int		update_value_in_env(t_dblist *list,
				    const char *name,
				    const char *value);
int		swap_env_values(t_dblist *list,
				const char *name1,
				const char *name2);

#endif /* !DOUBLE_LIST_H_ */
