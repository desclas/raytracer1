/*
** file3.c for  in /home/mathias/Bureau/projet_epitech/raytracer1
** 
** Made by Mathias
** Login   <mathias.descoin@epitech.eu@epitech.net>
** 
** Started on  Mon Mar  6 16:08:13 2017 Mathias
** Last update Mon Mar  6 16:39:39 2017 Mathias
*/

#include "framebuffer.h"

void choice(t_my_framebuffer *framebuffer, sfVector3f eye_pos,
	    sfVector3f dir_vector, sfVector2i screen_pos)
{
  float k_sphere;
  float k_plan;
  
  k_sphere = intersect_sphere(eye_pos, dir_vector, 50);
  k_plan = intersect_plane(eye_pos, dir_vector);
  if (k_sphere < 0 && k_plan < 0)
    my_putpixels(framebuffer, screen_pos.x, screen_pos.y, sfBlack);
  else if (k_sphere == -1 && k_plan >= 0)
    dark_plan(framebuffer, screen_pos, eye_pos, dir_vector);
  else if (k_sphere >= 0 && k_plan == -1)
    dark_sphere(framebuffer, screen_pos, eye_pos, dir_vector);
  else if (k_sphere < k_plan)
    dark_sphere(framebuffer, screen_pos, eye_pos, dir_vector);
  else if (k_sphere > k_plan)
    dark_plan(framebuffer, screen_pos, eye_pos, dir_vector);
}
