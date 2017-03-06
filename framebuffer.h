#ifndef FRAMEBUFFER_H_
# define FRAMEBUFFER_H_

# include <stdlib.h>
# include <math.h>
# include <SFML/Graphics.h>

typedef struct s_my_framebuffer
{
  sfUint8 *pixels;
  int width;
  int height;
  sfVector3f light;
}		t_my_framebuffer;

sfVector3f calc_dir_vector(float dist_to_plane, sfVector2i screen_size,
			   sfVector2i screen_pos);
float intersect_sphere(sfVector3f eye_pos, sfVector3f dir_vector,
		       float radius);
float intersect_plane(sfVector3f eye_pos, sfVector3f dir_vector);
float intersect_cylinder(sfVector3f eye_pos, sfVector3f dir_vector,
			 float radius);
float intersect_cone(sfVector3f eye_pos, sfVector3f dir_vector,
		     float semiangle);
int process_game_loop(sfRenderWindow *window, sfSprite *sprite);
sfVector3f translate(sfVector3f to_translate, sfVector3f translation);
sfVector3f rotate_xyz(sfVector3f to_rotate, sfVector3f angles);
sfVector3f rotate_zyx(sfVector3f to_rotate, sfVector3f angles);
sfVector3f get_normal_sphere(sfVector3f intersection_point);
sfVector3f get_normal_plane(int upward);
sfVector3f get_normal_cylinder(sfVector3f intersection_point);
sfVector3f get_normal_cone(sfVector3f itnersection_point, float semiangle);
float get_light_coef(sfVector3f light_vector, sfVector3f normal_vector);
float one_sol(double a, double b);
float two_sol(double a, double b, float s);
t_my_framebuffer *my_framebuffer_create(int width, int height);
void my_framebuffer_destroy(t_my_framebuffer *framebuffer);
void my_putpixels(t_my_framebuffer *framebuffer, int x, int y, sfColor color);
sfColor col(sfColor color, float k_sphere);
sfVector3f div_f(sfVector3f vect, float norm);
float norm(sfVector3f vect);
sfVector3f the_point(sfVector3f eye_pos, sfVector3f dir_vector, float k_obj);
void dark_sphere(t_my_framebuffer *framebuffer, sfVector2i screen_pos,
		 sfVector3f eye_pos, sfVector3f dir_vector);
void dark_plan(t_my_framebuffer *framebuffer, sfVector2i screen_pos,
	       sfVector3f eye_pos, sfVector3f dir_vector);
void	raytrace_scene(t_my_framebuffer *framebuffer);
void choice(t_my_framebuffer *framebuffer, sfVector3f eye_pos,
	    sfVector3f dir_vector, sfVector2i screen_pos);

#endif /* !FRAMEBUFFER_H_ */
