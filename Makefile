##
## Makefile for make in /home/szterg_r/Documents/SYSTEME_UNIX/PSU_2015_42sh
## 
## Made by szterg_r
## Login   <szterg_r@epitech.net>
## 
## Started on  Mon May 30 11:52:36 2016 szterg_r
## Last update Sun Jun  5 21:17:09 2016 clement doumergue
##

CC	=	gcc

RM	=	rm -f

LIBSRC	=	\
		lib/my/my_dprintf.c \
	  	lib/my/my_printf.c \
	  	lib/my/dputstuff_bis.c \
	  	lib/my/dputstuff.c \
	  	lib/my/dputstuff_ter.c \
	  	lib/my/my_dputstr.c \
	  	lib/my/my_dputchar.c \
	  	lib/my/my_dshowstr_oct.c \
	  	lib/my/my_dputlong_base.c \
	  	lib/my/my_dputnbr_base.c \
	  	lib/my/my_dput_nbr.c \
	  	lib/my/my_xmalloc.c \
	  	lib/my/dblist_core.c \
	  	lib/my/dblist_ops.c \
	  	lib/my/dblist_utils.c \
	  	lib/my/tab_utils.c \
	  	lib/my/tab_utils2.c \
	  	lib/my/errors.c \
	  	lib/my/get_next_line.c \
	  	lib/my/my_getnbr.c \
	  	lib/my/my_strlen.c \
	  	lib/my/my_split.c \
	  	lib/my/my_strcpy.c \
	  	lib/my/my_strcmp.c \
	  	lib/my/my_strncmp.c \
	  	lib/my/my_strndup.c \
	  	lib/my/my_strchr.c \
	  	lib/my/my_memset.c \
	  	lib/my/get_file.c \
	  	lib/my/get_str_pos.c \
	  	lib/my/is_empty.c \
	  	lib/my/is_number.c \
		lib/my/my_atoi_base.c \
	  	lib/my/dputstr_centered.c \
	  	lib/my/word_replace_prev.c \
	  	lib/my/word_replace.c \
		lib/my/my_calloc.c \
	  	lib/my/my_strstr.c \
	  	lib/my/word_len.c \
	  	lib/my/count_char.c \
	 	lib/my/my_strncpy.c

INPUT	=	\
		srcs/input/seqs.c \
		srcs/input/handlers.c \
		srcs/input/handlers_bis.c \
		srcs/input/handlers_ter.c \
		srcs/input/line.c \
		srcs/input/print.c \
		srcs/input/input.c

CORE	=	\
		srcs/core/setup.c \
		srcs/core/term.c  \

AUTOCOMPLETE =	\
		srcs/autocomplete/utils.c \
		srcs/autocomplete/comp_tab.c \
		srcs/autocomplete/file.c \
		srcs/autocomplete/autocomplete.c \
		srcs/autocomplete/display.c

PARSER	=	\
		srcs/parser/tree.c \
		srcs/parser/utils.c \
		srcs/parser/rules.c \
		srcs/parser/rules_bis.c \
		srcs/parser/parse.c \

BUILTINS =	\
		srcs/builtins/cd.c \
		srcs/builtins/alias.c \
		srcs/builtins/var_utils.c \
		srcs/builtins/env.c \
		srcs/builtins/echo.c \
		srcs/builtins/echo_dollar.c \
		srcs/builtins/print_echo.c \
		srcs/builtins/history.c \
		srcs/builtins/redo.c \
		srcs/builtins/exit.c \
		srcs/builtins/builtins.c \

EXEC	=	\
		srcs/execution/fd_config.c \
		srcs/execution/execs.c \
		srcs/execution/execs_redir.c \
		srcs/execution/execute.c \
		srcs/execution/simple_run.c \
		srcs/execution/run_utils.c \

GLOB	=	\
		srcs/glob/globbing.c

RC	=	\
		srcs/rc/loader.c \
		srcs/rc/export.c

UTILS	=	\
		srcs/utils.c \
		srcs/prompt/prompt.c

SRCS	=	\
		$(UTILS) \
		$(CORE) \
		$(INPUT) \
		$(AUTOCOMPLETE) \
		$(PARSER) \
		$(BUILTINS) \
		$(EXEC) \
		$(GLOB) \
		$(RC) \
		srcs/main.c

OBJS	=	$(SRCS:.c=.o)

LIBOBJS	 =	$(LIBSRC:.c=.o)

NAME	=	42sh

LIBNAME	=	lib42sh.a

LDFLAGS  +=	-L.
LDLIBS   +=	-l42sh -lncurses
CPPFLAGS +=	-Iinclude -D_GNU_SOURCE
CFLAGS	 +=	-W -Wall -Wextra
#CFLAGS	 +=	-O2 -march=native

all:		$(LIBNAME) $(NAME)

$(LIBNAME):	$(LIBOBJS)
		ar rcs $(LIBNAME) $(LIBOBJS)

$(NAME):	$(OBJS)
		$(CC) -o $(NAME) $(OBJS) $(LDLIBS) $(LDFLAGS)

clean:
		$(RM) $(OBJS)
		$(RM) $(LIBOBJS)

fclean:		clean
		$(RM) $(LIBNAME)
		$(RM) $(NAME)

re:		fclean all

.PHONY:		all clean fclean re
