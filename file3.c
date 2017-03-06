/*
** file3.c for  in /home/mathias/Bureau/projet_epitech/raytracer1
** 
** Made by Mathias
** Login   <mathias.descoin@epitech.eu@epitech.net>
** 
** Started on  Fri Mar  3 16:37:19 2017 Mathias
** Last update Fri Mar  3 18:44:11 2017 Mathias
*/

#include "framebuffer.h"

int bigger(float *all_k)
{
  int i;
  int res;

  i = 0;
  res = -1;
  while (all_k[i] < 0 && i != 4)
    i += 1;
  if (i == 4)
    return (res);
  res = i;
  i = 0;
  while (i != 4)
    {
      if (all_k[res] > all_k[i] && all_k[i] > 0)
	{
	  res = i;
	  i = 0;
	}
      else
	i += 1;
    }
  return (res);
}
