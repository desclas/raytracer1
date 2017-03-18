/*
** file3.c for  in /home/mathias/Bureau/projet_epitech/raytracer1
** 
** Made by Mathias
** Login   <mathias.descoin@epitech.eu@epitech.net>
** 
** Started on  Mon Mar  6 16:08:13 2017 Mathias
** Last update Sat Mar 18 18:44:22 2017 Mathias
*/

#include "framebuffer.h"

int bigger(float *all_k, int max)
{
  int i;
  int res;

  i = 0;
  res = -1;
  while (all_k[i] < 0 && i != max)
    i += 1;
  if (i == 4)
    return (res);
  res = i;
  i = 0;
  while (i != max)
    {
      if (all_k[i] >= 0)
	if (all_k[i] < all_k[res])
	  {
	    res = i;
	    i = 0;
	  }
      i += 1;
    }
  return (res);
}

float int_cone(sfVector3f eye_pos, sfVector3f dir_vector)
{
  sfVector3f trans = {0, 50, 0};
  sfVector3f rot = {90, 0, 0};
  
  return (intersect_cone(translate(rotate_xyz(eye_pos, rot), trans),
			 translate(rotate_xyz(dir_vector, rot), trans),
			 10));
}

void dark_cylinder(t_my_framebuffer *framebuffer, sfVector2i screen_pos,
		 sfVector3f eye_pos, sfVector3f dir_vector)
{
  sfVector3f point;
  sfVector3f dir_spot;
  float k_sphere;
  sfColor color;
  
  k_sphere = intersect_cylinder(eye_pos, dir_vector, 25);
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
  color = sfGreen;
  if (int_cone(point, dir_spot) <= 1 && int_cone(point, dir_spot) >= 0)
    color = col(color, (1 / k_sphere));
  else if (k_sphere < 0)
    color = sfBlack;
  else
    color = col(color, k_sphere);
  my_putpixels(framebuffer, screen_pos.x, screen_pos.y, color);
}

void dark_cone(t_my_framebuffer *framebuffer, sfVector2i screen_pos,
		 sfVector3f eye_pos, sfVector3f dir_vector)
{
  sfVector3f point;
  sfVector3f dir_spot;
  float k_sphere;
  sfColor color;
  
  k_sphere = int_cone(eye_pos, dir_vector);
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
  color = sfYellow;
  if (intersect_cylinder(point, dir_spot, 25) >= 0 && intersect_cylinder(point, dir_spot, 25) <= 1)
    color = col(color, 0.5);
  else if (k_sphere < 0)
    color = sfBlack;
  else
    color = col(color, k_sphere);
  my_putpixels(framebuffer, screen_pos.x, screen_pos.y, color);
}

void choice(t_my_framebuffer *framebuffer, sfVector3f eye_pos,
	    sfVector3f dir_vector, sfVector2i screen_pos)
{
  float all_k[4];
  int res;
  
  all_k[0] = intersect_sphere(eye_pos, dir_vector, 50);
  all_k[1] = intersect_plane(eye_pos, dir_vector);
  all_k[2] = intersect_cylinder(eye_pos, dir_vector, 25);
  all_k[3] = int_cone(eye_pos, dir_vector);
  res = bigger(all_k, 4);
  if (res == -1)
    my_putpixels(framebuffer, screen_pos.x, screen_pos.y, sfBlack);
  else if (res == 1)
    dark_plan(framebuffer, screen_pos, eye_pos, dir_vector);
  else if (res == 0)
    dark_sphere(framebuffer, screen_pos, eye_pos, dir_vector);
  else if (res == 2)
    dark_cylinder(framebuffer, screen_pos, eye_pos, dir_vector);
  else if (res == 3)
    dark_cone(framebuffer, screen_pos, eye_pos, dir_vector);
}
