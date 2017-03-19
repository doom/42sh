/*
** get_next_line.h for get_next_line in /home/doumer_c/rendu/CPE_2015_getnextline
** 
** Made by clement doumergue
** Login   <doumer_c@epitech.net>
** 
** Started on  Mon Jan  4 11:55:42 2016 
** Last update Sat Apr  2 13:09:51 2016 clement doumergue
*/

#ifndef GET_NEXT_LINE_H_
# define GET_NEXT_LINE_H_

# ifndef READ_SIZE
#  define READ_SIZE (1)
# endif /* !READ_SIZE */

typedef struct	s_line
{
  char		*buff;
  int		pos;
}		t_line;

char	*get_next_line(const int fd);

#endif /* !GET_NEXT_LINE_H_ */
