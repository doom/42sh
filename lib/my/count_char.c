/*
** count_char.c for libmy in /home/doumer_c/rendu/PSU_2015_42sh
** 
** Made by clement doumergue
** Login   <doumer_c@epitech.net>
** 
** Started on  Tue May 31 15:22:34 2016 clement doumergue
** Last update Tue May 31 15:23:25 2016 clement doumergue
*/

int	count_char(const char *str, char c)
{
  int	count;

  count = 0;
  while (*str)
    if (*str++ == c)
      count += 1;
  return (count);
}
