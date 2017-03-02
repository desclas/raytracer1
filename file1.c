/*
** file1.c for  in /home/mathias/Bureau/projet_epitech/raytracer1
** 
** Made by Mathias
** Login   <mathias.descoin@epitech.eu@epitech.net>
** 
** Started on  Thu Mar  2 14:57:17 2017 Mathias
** Last update Thu Mar  2 14:57:59 2017 Mathias
*/

#include "framebuffer.h"

t_my_framebuffer *my_framebuffer_create(int width, int height)
{
  t_my_framebuffer *framebuffer;
  int i;

  framebuffer = malloc(sizeof(*framebuffer));
  framebuffer->pixels = malloc(width * height * 4
			       * sizeof(*framebuffer->pixels));
  framebuffer->width = width;
  framebuffer->height = height;
  framebuffer->light.x = -100;
  framebuffer->light.y = 0;
  framebuffer->light.z = 0;
  i = 0;
  while (i != width * height * 4)
    {
      framebuffer->pixels[i] = 0;
      i += 1;
    }
  return (framebuffer);
}

void my_framebuffer_destroy(t_my_framebuffer *framebuffer)
{
  free(framebuffer->pixels);
  free(framebuffer);
}

void my_putpixels(t_my_framebuffer *framebuffer, int x, int y, sfColor color)
{
  framebuffer->pixels[(framebuffer->width * y + x) * 4] = color.r;
  framebuffer->pixels[(framebuffer->width * y + x) * 4 + 1] = color.g;
  framebuffer->pixels[(framebuffer->width * y + x) * 4 + 2] = color.b;
  framebuffer->pixels[(framebuffer->width * y + x) * 4 + 3] = color.a;
}

sfColor col(sfColor color, float k_sphere)
{
  color.r *= k_sphere;
  color.g *= k_sphere;
  color.b *= k_sphere;
  color.a *= k_sphere;
  return (color);
}

sfVector3f div_f(sfVector3f vect, float norm)
{
  vect.x = vect.x / norm;
  vect.y = vect.y / norm;
  vect.z = vect.z / norm;
  return (vect);
}
