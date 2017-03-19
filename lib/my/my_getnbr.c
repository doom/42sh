/*
** my_getnbr.c for libdoom in /home/doumer_c/libmy
** 
** Made by clement doumergue
** Login   <doumer_c@epitech.net>
** 
** Started on  Wed Jan 27 22:38:26 2016 clement doumergue
** Last update Mon May  2 17:47:51 2016 clement doumergue
*/

int	my_getstr_sign(const char *str)
{
  int	i;
  int	sign_counter;

  i = 0;
  sign_counter = 0;
  while (str[i] != '\0' && (str[i] > '9' || str[i] < '0'))
    if (str[i++] == '-')
      sign_counter = sign_counter + 1;
  return ((sign_counter % 2) ? -1 : 1);
}

int	my_isnum(char c)
{
  return ('0' <= c && c <= '9');
}

int	my_getnbr(const char *str)
{
  int	nbr;
  int	i;

  nbr = 0;
  i = 0;
  while (str[i] != '\0' && my_isnum(str[i]) == 0)
    i = i + 1;
  while (str[i] != '\0' && my_isnum(str[i]) == 1)
    {
      nbr = nbr * 10 + (str[i] - '0');
      i = i + 1;
    }
  nbr = nbr * my_getstr_sign(str);
  return (nbr);
}
