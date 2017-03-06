/*
** file2.c for  in /home/mathias/Bureau/projet_epitech/raytracer1
** 
** Made by Mathias
** Login   <mathias.descoin@epitech.eu@epitech.net>
** 
** Started on  Thu Mar  2 14:58:22 2017 Mathias
** Last update Sun Mar  5 19:04:12 2017 Mathias
*/

#include "framebuffer.h"

float norm(sfVector3f vect)
{
  float normal;
  
  normal = sqrt(pow(vect.x, 2) + pow(vect.y, 2) + pow(vect.z, 2));
  return (normal);
}

sfVector3f the_point(sfVector3f eye_pos, sfVector3f dir_vector, float k_obj)
{
  sfVector3f point;
  
  point.x = eye_pos.x + (k_obj * dir_vector.x);
  point.y = eye_pos.y + (k_obj * dir_vector.y);
  point.z = eye_pos.z + (k_obj * dir_vector.z);
  return (point);
}

/* point = get_normal_sphere(point); */
/* k_sphere = get_light_coef(dir_spot, point); */
/* metre ces deux lignes au dessus de "k_sphere = norm(dir_vector);" */

void the_sphere(t_my_framebuffer *framebuffer, sfVector2i screen_pos,
		sfVector3f dir_vector, int k)
{
  sfVector3f point;
  sfVector3f dir_spot;
  sfColor color;

  point = the_point(eye_pos, dir_vector, framebuffer->all_k[k]);
  dir_spot.x = framebuffer->light.x - point.x;
  dir_spot.y = framebuffer->light.y - point.y;
  dir_spot.z = framebuffer->light.z - point.z;
  framebuffer->all_k[k] = norm(dir_vector);
  dir_vector = div_f(dir_vector, framebuffer->all_k[k]);
  framebuffer->all_k[k] = norm(dir_spot);
  dir_spot = div_f(dir_spot, framebuffer->all_k[k]);
  framebuffer->all_k[k] = (dir_vector.x * dir_spot.x) +
    (dir_vector.y * dir_spot.y) + (dir_vector.z * dir_spot.z);
  framebuffer->all_k[k] *= -1;
  color = sfRed;
  if (framebuffer->all_k[k] < 0)
    color = sfBlack;
  else
    color = col(color, framebuffer->all_k[k]);
  my_putpixels(framebuffer, screen_pos.x, screen_pos.y, color);
}

void dark_plan(t_my_framebuffer *framebuffer, sfVector2i screen_pos,
	       sfVector3f eye_pos, sfVector3f dir_vector)
{
  sfVector3f point;
  float k_plan;
  sfVector3f dir_spot;
  sfColor color;

  k_plan = intersect_plane(eye_pos, dir_vector);
  point.x = eye_pos.x + (k_plan * dir_vector.x);
  point.y = eye_pos.y + (k_plan * dir_vector.y);
  point.z = eye_pos.z + (k_plan * dir_vector.z);
  dir_spot.x = framebuffer->light.x - point.x;
  dir_spot.y = framebuffer->light.y - point.y;
  dir_spot.z = framebuffer->light.z - point.z;
  k_plan = intersect_sphere(point, dir_spot, 50);
  if (k_plan >= 0 && k_plan <= 1)
    {
      color = sfBlue;
      color.r /= 2;
      color.g /= 2;
      color.b /= 2;
      color.a /= 2;
      my_putpixels(framebuffer, screen_pos.x, screen_pos.y, color);
    }
  else
    my_putpixels(framebuffer, screen_pos.x, screen_pos.y, sfBlue);
}

void choice(t_my_framebuffer *framebuffer, sfVector3f eye_pos,
	    sfVector3f dir_vector, sfVector2i screen_pos)
{
  int res;
  
  framebuffer->all_k[0] = intersect_sphere(eye_pos, dir_vector, 50);
  framebuffer->all_k[1] = intersect_plane(eye_pos, dir_vector);
  framebuffer->all_k[2] = -1;
  /* framebuffer->all_k[2] = intersect_cylinder(eye_pos, dir_vector, 50); */
  framebuffer->all_k[3] = -1;
  res = bigger(framebuffer->all_k);
  if (res == -1)
    my_putpixels(framebuffer, screen_pos.x, screen_pos.y, sfBlack);
  else if (res == 0)
    the_sphere(framebuffer, screen_pos, eye_pos, dir_vector);
  else if (res == 1)
    dark_plan(framebuffer, screen_pos, eye_pos, dir_vector);
  else if (res == 2)
    ;
  else if (res == 3)
    ;
}
