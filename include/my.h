/*
** my.h for libdoom in /home/doumer_c/libmy
**
** Made by clement doumergue
** Login   <doumer_c@epitech.net>
**
** Started on  Thu Jan 28 00:38:17 2016 clement doumergue
** Last update Sun Jun  5 13:29:56 2016 clement doumergue
*/

#ifndef MY_H_
# define MY_H_

# include <stdarg.h>
# include <stdbool.h>
# include <stddef.h>

/*
** RETURN CODES
*/
# define SUCCESS 0
# define FAILURE -1

/*
** ERROR MESSAGES
*/
# define MALLOC_ERROR "Malloc failed !\n"
# define READ_ERROR "Read failed !\n"

/*
** UTILS
*/
# define MY_MAX(x, y) ((x > y) ? (x) : (y))
# define MY_MIN(x, y) ((x < y) ? (x) : (y))

# define WORD	0
# define REP	1
# define NEW	2
# define IS_BEGIN (idx[WORD] == 0 || IS_WORD_SEP(str[idx[WORD] - 1]))
# define NORMAL "\033[0m"
# define RED "\033[31m"
# define GREEN "\033[32m"
# define BLUE "\033[34m"
# define YELLOW "\033[33m"
# define CYAN "\033[36m"
# define WHITE "\033[39m"
# define BOLD "\033[1m"
# define PGREEN(x) GREEN, x, NORMAL
# define PYELLOW(x) YELLOW, x, NORMAL
# define PRED(x) RED, x, NORMAL

# define IS_SEP(x) (x == ' ' || x == '\t' || x == '\v' || x == ';')
# define IS_WORD_SEP(x) (x == ' ' || x == '\t' || x == '/' || x == '\0')
# define IS_MIN(x) ('a' <= (x) && (x) <= 'z')
# define IS_MAJ(x) ('A' <= (x) && (x) <= 'Z')
# define IS_DIGIT(x) ('0' <= (x) && (x) <= '9')

/*
** WRAPPERS
*/
void	*my_xmalloc(int size);

/*
** Errors
*/
int	my_puterror(const char *format, ...);

/*
** Display
*/
int	my_dputchar(int fd, char c);
int	my_dputstr(int fd, const char *str);
int	my_dput_nbr(int fd, int nb);
int	my_dputnbr_base(int fd, unsigned int nb, char *base);
int	my_dputlong_base(int fd, unsigned long nb, char *base);
int	my_dput_float(int fd, float nb, int precision);
int	my_dshowstr_oct(int fd, const char *str);
int	my_vdprintf(int fd, const char *format, va_list ap);
int	my_dprintf(int fd, const char *format, ...);
int	my_printf(const char *format, ...);
void	dputstr_left(int fd, const char *str, int size);
void	dputstr_centered(int fd, const char *str, int size);

/*
** String: information gathering
*/
int	my_strlen(const char *str);
int	my_str_contains_numbers(const char *str);
int	my_endswith(const char *str, const char *end);
int	my_strcmp(const char *s1, const char *s2);
int	my_strncmp(const char *s1, const char *s2, int n);
int	get_char_pos(const char *str, char c);
char	*my_strchr(const char *str, char c);
int	my_getnbr(const char *str);
bool	is_number(const char *str);
bool   	is_instr(char c, const char *str);
int	my_atoi(const char *str);
int	my_atoi_base(const char *str, const char *base);
int	get_last_char(const char *str, char c);
int     get_str_pos(const char *str, const char *to_find);
int     get_last_pos(const char *str, const char *to_find);
bool	is_empty(const char *str);
bool	is_alphanum(const char *str);
char	*my_strstr(const char *str, const char *s);
int	word_len(const char *str);
int	count_char(const char *str, char c);
int	count_words(const char *str, const char *seps);

/*
** String: edition
*/
char	*my_strcat(char *dest, const char *src);
char	*my_strncat(char *dest, const char *src, int nb);
char	*my_strcpy(char *dest, const char *src);
char	*my_strncpy(const char *dest, const char *src, int n);
char	*my_strdup(const char *src);
char	*my_strndup(const char *src, int len);
char	*my_revstr(char *str);
char	*skip_blank(char *str);
char	*cut_end(char *str);
char	*replace_first_word(char *s, const char *w, const char *rep);
char	*replace_prev_word(char *str, int pos, const char *rep);
char	*replace_word(char *str, const char *word, const char *rep);

/*
** Double dimension tabs
*/
char	**my_split(const char *str, const char *sep);
void	free_tab(char **);
int	replace_tab_entry(char **, int, char *);

/*
** Raw memory utils
*/
void	*my_memset(void *ptr, int c, int n);
void	*my_calloc(size_t size);
char	*get_file(const char *dir, const char *file);

#endif /* !MY_H_ */
