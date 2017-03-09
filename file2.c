/*
** file2.c for  in /home/mathias/Bureau/projet_epitech/raytracer1
** 
** Made by Mathias
** Login   <mathias.descoin@epitech.eu@epitech.net>
** 
** Started on  Mon Mar  6 16:03:54 2017 Mathias
** Last update Thu Mar  9 18:39:10 2017 Mathias
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

void dark_sphere(t_my_framebuffer *framebuffer, sfVector2i screen_pos,
		 sfVector3f eye_pos, sfVector3f dir_vector)
{
  sfVector3f point;
  sfVector3f dir_spot;
  float k_sphere;
  sfColor color;

  k_sphere = intersect_sphere(eye_pos, dir_vector, 50);
  point = the_point(eye_pos, dir_vector, k_sphere);
  dir_spot.x = framebuffer->light.x - point.x;
  dir_spot.y = framebuffer->light.y - point.y;
  dir_spot.z = framebuffer->light.z - point.z;
  k_sphere = norm(dir_vector);
  dir_vector = div_f(dir_vector, k_sphere);
  k_sphere = norm(dir_spot);
  dir_spot = div_f(dir_spot, k_sphere);
  k_sphere = (dir_vector.x * dir_spot.x) +
    (dir_vector.y * dir_spot.y) + (dir_vector.z * dir_spot.z);
  k_sphere *= -1;
  color = sfRed;
  if (k_sphere < 0)
    color = sfBlack;
  else
    color = col(color, k_sphere);
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

void	raytrace_scene(t_my_framebuffer *framebuffer)
{
  sfVector3f eye_pos;
  sfVector2i screen_size;
  sfVector2i screen_pos;
  sfVector3f dir_vector;
  float k_sphere;
  float k_plan;

  eye_pos.x = -200;
  eye_pos.y = 0;
  eye_pos.z = 25;
  screen_size.x = framebuffer->width;
  screen_size.y = framebuffer->height;
  screen_pos.x = 0;
  while (screen_pos.x != screen_size.x)
    {
      screen_pos.y = 0;
      while (screen_pos.y != screen_size.y)
	{
	  dir_vector = calc_dir_vector(500, screen_size, screen_pos);
	  choice(framebuffer, eye_pos, dir_vector, screen_pos);
	  screen_pos.y += 1;
	}
      screen_pos.x += 1;
    }
}
