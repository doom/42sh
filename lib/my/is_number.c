/*
** is_number.c for libmy in /home/doumer_c/rendu/PSU_2015_42sh
** 
** Made by clement doumergue
** Login   <doumer_c@epitech.net>
** 
** Started on  Mon May  2 17:49:25 2016 clement doumergue
** Last update Sun Jun  5 13:36:15 2016 clement doumergue
*/

#include <stdbool.h>
#include "my.h"

bool	is_alphanum(const char *str)
{
  while (IS_MIN(*str) || IS_MAJ(*str)
	 || ('0' <= *str && *str <= '9') || *str == '_')
    str += 1;
  return (*str == '\0');
}

bool	is_number(const char *str)
{
  while ('0' <= *str && *str <= '9')
    str += 1;
  return (*str == '\0');
}
