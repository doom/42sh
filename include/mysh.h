/*
** mysh.h for 42sh in /home/doumer_c/rendu/PSU_2015_42sh
**
** Made by clement doumergue
** Login   <doumer_c@epitech.net>
**
** Started on  Mon May  2 16:56:07 2016 clement doumergue
** Last update Sun Jun  5 19:44:46 2016 clement doumergue
*/

#ifndef MYSH_H_
# define MYSH_H_

# include <termios.h>
# include "my.h"
# include "double_list.h"

/*
** Error messages
*/
# define SETUP_FAILED "%s%s%s %s%s%s\n", PRED("[MYSH]"), PYELLOW("Setup failed")
# define EXPECT_EXPR "Expected expression after binary operator\n"
# define FORK_FAILED "Unable to create subprocess\n"
# define UNMATCHED_SYM "Expected %s before newline\n"
# define EMPTY_EXPR "Invalid empty command\n"
# define GLOB_ERROR "No match found\n"
# define OPEN_ERROR(x) "Unable to open/create %s\n", x
# define RF "Failed to reset normal output. Your shell might be broken.\n"
# define RESET_FAILED RF
# define LETTER_VAR "setenv: Variable name must begin with a letter.\n"
# define A "setenv: Variable name must contain alphanumeric characters.\n"
# define NOT_ALPHANUM A
# define TOO_MANY_ARGS(x) "%s: Too many arguments.\n", x
# define TOO_FEW_ARGS(x) "%s: Too few arguments.\n", x
# define NOT_FOUND "%s: Command not found.\n", argv[0]
# define INVALID_ALIAS "[WARNING] Invalid alias: %s\n"
# define INVALID_EXPORT "[WARNING] Invalid export: %s\n"
# define EXPORT_FAIL "[WARNING] Failed exporting %s\n"
# define PIPE_FAILED "Unable to create pipe\n"
# define OPEN_FAIL "Failed to create a temp file.\n"
# define DLRED_FAILED "Unable to get input.\n"
# define BAD_EXEC(x) "%s: Exec format error. Binary file not executable.\n", x

/*
** Parser
*/
# define REDO_OP '!'
# define DELIM ";"
# define AND "&&"
# define OR "||"
# define PIPE "|"
# define LRED "<"
# define RRED ">"
# define DLRED "<<"
# define DRRED ">>"
# define SQUOTE "\'"
# define DQUOTE "\""
# define C "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789_-./"
# define WORDS (C)

/*
** 42shrc
*/
# define RCFILE ".42shrc"
# define SHARPS '#'
# define RCLIM " "

# define GET_PATTERN(av) ((av[0][1] != REDO_OP) ? av[0] + 1 : "")
# define GET_LIM(str) ((strchr(str, '"') != NULL) ? "\"" : " ")
# define RC_FAIL(msg, var) (print_error(msg, var))

typedef enum		e_op_type
  {
    DELIM_OP,
    AND_OP,
    OR_OP,
    PIPE_OP,
    DLRED_OP,
    LRED_OP,
    DRRED_OP,
    RRED_OP,
    NONE
  }			te_op_type;

typedef struct		s_tree
{
  char			*exp;
  te_op_type		op;
  struct s_tree		*left;
  struct s_tree		*right;
}			t_tree;

typedef struct		s_escape
{
  char			flag;
  char			*var;
}			t_escape;

typedef struct		s_signal_message
{
  int			signal;
  const char		*message;
}			t_signal_message;

typedef struct		s_config
{
  int			pipefd[2];
  int			bk[2];
}			t_config;

typedef struct		s_builtin
{
  const char		*name;
  int			(*func)(char **, t_dblist *);
}			t_builtin;

typedef struct		s_shell
{
  int			fd;
  bool			interactive;
  t_dblist		*env;
  t_dblist		*aliases;
  t_dblist		*history;
  t_dblist_int		*pids;
  int			pipes_count;
  t_elem		*hist_cur;
  char			*prompt;
  t_config		cfg;
  struct termios	term;
  int			count;
  unsigned char		exit_status;
  bool			run;
}			t_shell;

typedef struct		s_options
{
  int			e;
  int			n;
}			t_options;

/*
** SETUP
*/
int			init_seqs(void);
void			release_seqs(void);
t_shell			*setup_shell(int ac, char **av, char **env);
int			release_shell(t_shell *sh);
int			reset_term(struct termios *term);
int			init_term(struct termios *term, char *term_name);

/*
** .42SHRC
*/
int			open_myshrc(t_shell *shell);
int			myshrc_export(t_dblist *env, const char *line);
int			generate_prompt(t_shell *shell);

/*
** ENV
*/
t_dblist		*env_to_dblist(char **);
char			*my_getenv(const char *str, const t_dblist *env);
t_elem			*var_by_name(const t_dblist *env, const char *name);
int			update_var_value(t_dblist *env,
					 const char *name,
					 const char *value);
int			remove_var(t_dblist *env, const char *name);
char			**env_to_tab(t_dblist *env);
const char		*get_path(const t_dblist *env);

/*
** INPUT
*/
int			show_prompt(const t_shell *sh);
char			*read_command(t_shell *sh);

/*
** GLOBBING
*/
char			*replace_globs(char *exp);

/*
** PARSING
*/
bool			is_empty_invalid(const char *str);
bool			is_begin(const char *str, int pos);
bool			move_words(char *str, const char *op);
int			lredir_rule(t_tree *root);
int			delim_rule(t_tree *root);
t_tree			*parse_exp(char *exp);
t_tree			*tree_with_exp(char *exp, te_op_type op);
int			make_subtrees(t_tree *root, int pos, te_op_type op);
void			release_tree(t_tree *tree);

/*
** FD UTILS
*/
int			reset_redir(int rfd, int fd, int bk[2]);
int			prep_redir(int rfd, int fd, int bk[2]);
void			reset_fds(t_config *cfg);
void			set_fds(t_config *cfg);

/*
** EXECUTING / RUNNING
*/
int			handle_input(char *input, t_shell *sh);
char			*replace_aliases(char *input, const t_dblist *al);
int			find_path(char **argv, const t_shell *sh);
int			execute_tree(t_tree *tree, t_shell *sh);
int			simple_command(const char *input, t_shell *sh);
void			reset_config(t_config *cfg);
int			exec_delim(t_tree *left, t_tree *right, t_shell *sh);
int			exec_and(t_tree *left, t_tree *right, t_shell *sh);
int			exec_or(t_tree *left, t_tree *right, t_shell *sh);
int			exec_pipe(t_tree *left, t_tree *right, t_shell *sh);
int			exec_dlredir(t_tree *left, t_tree *right, t_shell *sh);
int			exec_lredir(t_tree *left, t_tree *right, t_shell *sh);
int			exec_rredir(t_tree *left, t_tree *right, t_shell *sh);
int			exec_drredir(t_tree *left, t_tree *right, t_shell *sh);
void			kill_pids(t_dblist_int *pids);

/*
** BUILTINS
*/
int			check_builtins(char **argv, t_shell *sh);
int			redo_cmd(char **argv, t_shell *sh);
int			my_setenv(char **args, t_dblist *env);
int			my_unsetenv(char **args, t_dblist *env);
int			my_printenv(char **args, t_dblist *env);
int			my_cd(char **args, t_dblist *env);
int			my_alias(char **argv, t_dblist *al);
int			my_unalias(char **argv, t_dblist *al);
int			history(char **argv, t_dblist *history);
int			my_exit(char **argv, t_shell *sh);
int			my_echo(char **av, t_dblist *env);
void			init_options(t_options *option);
void			print_env(char *str, const t_dblist *env, t_options option);
void			print_av(const char *str, t_options *option);
void			print_backslash_escapes(const char *str);
void			add_to_history(t_dblist *history, const char *input);

/*
** UTILS
*/
bool			my_isatty(int fd);
bool			is_empty(const char *str);
char			*remove_comments(char *str);
int			dir_exists(const char *path);

#endif /* !MYSH_H_ */
