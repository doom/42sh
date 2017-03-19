/*
** my_dprintf.h for libdoom in /home/doumer_c/libmy
** 
** Made by clement doumergue
** Login   <doumer_c@epitech.net>
** 
** Started on  Thu Jan 28 00:13:55 2016 clement doumergue
** Last update Thu Jan 28 00:13:59 2016 clement doumergue
*/

#ifndef MY_DPRINTF_H_
# define MY_DPRINTF_H_

# include <stdarg.h>
# include "my.h"

int	dput_char(int fd, va_list ap, int opt);
int	dput_string(int fd, va_list ap, int opt);
int	dput_int(int fd, va_list ap, int opt);
int	dput_maj_hex(int fd, va_list ap, int opt);
int	dput_min_hex(int fd, va_list ap, int opt);
int	dput_oct(int fd, va_list ap, int opt);
int	dput_bin(int fd, va_list ap, int opt);
int	dput_pointer(int fd, va_list ap, int opt);
int	dput_string_maj(int fd, va_list ap, int opt);
int	dput_unsigned(int fd, va_list ap, int opt);
int	dput_float(int fd, va_list ap, int opt);

#endif /* !MY_DPRINTF_H_ */
