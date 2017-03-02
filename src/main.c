#include <stdlib.h>
#include <SFML/Graphics.h>

#include "../framebuffer.h"

#define	FRAMEBUFFER_WIDTH 600
#define FRAMEBUFFER_HEIGHT 400

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

void dark_sphere(t_my_framebuffer *framebuffer, sfVector2i screen_pos,
		 sfVector3f eye_pos, sfVector3f dir_vector)
{
  sfVector3f point;
  sfVector3f dir_spot;
  float k_sphere;
  sfColor color;

  k_sphere = intersect_sphere(eye_pos, dir_vector, 50);
  point.x = eye_pos.x + (k_sphere * dir_vector.x);
  point.y = eye_pos.y + (k_sphere * dir_vector.y);
  point.z = eye_pos.z + (k_sphere * dir_vector.z);
  dir_spot.x = framebuffer->light.x - point.x;
  dir_spot.y = framebuffer->light.y - point.y;
  dir_spot.z = framebuffer->light.z - point.z;
  point = get_normal_sphere(point);
  k_sphere = get_light_coef(dir_spot, point);
  /* k_sphere = sqrt(pow(dir_vector.x, 2) + pow(dir_vector.y, 2) + pow(dir_vector.z, 2)); */
  /* dir_vector.x = dir_vector.x / k_sphere; */
  /* dir_vector.y = dir_vector.y / k_sphere; */
  /* dir_vector.z = dir_vector.z / k_sphere; */
  /* k_sphere = sqrt(pow(dir_spot.x, 2) + pow(dir_spot.y, 2) + pow(dir_spot.z, 2)); */
  /* dir_spot.x = dir_spot.x / k_sphere; */
  /* dir_spot.y = dir_spot.y / k_sphere; */
  /* dir_spot.z = dir_spot.z / k_sphere; */
  /* k_sphere = (dir_vector.x * dir_spot.x) + (dir_vector.y * dir_spot.y) + (dir_vector.z * dir_spot.z); */
  color = sfRed;
  if (k_sphere < 0)
    color = sfBlack;
  else
    {
      color.r *= k_sphere;
      color.g *= k_sphere;
      color.b *= k_sphere;
      color.a *= k_sphere;
    }
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
  eye_pos.z = 0;
  screen_size.x = framebuffer->width;
  screen_size.y = framebuffer->height;
  screen_pos.x = 0;
  while (screen_pos.x != screen_size.x)
    {
      screen_pos.y = 0;
      while (screen_pos.y != screen_size.y)
	{
	  dir_vector = calc_dir_vector(500, screen_size, screen_pos);
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
	  screen_pos.y += 1;
	}
      screen_pos.x += 1;
    }
}

/*
** This main function is provided for the bootstrap of the Raytracer1.
** YOU MUST NOT SUBMIT IT !
**
** Some functions are required for this code to work :
** - All functions of the c_graph_prog library
** - my_framebuffer_create
** - raytrace_scene
** - my_framebuffer_destroy
**
** //// my_framebuffer_create(int width, int height)
** Creates a framebuffer from the width and the height of the frame.
** 
** //// raytrace_scene(t_my_framebuffer *framebuffer)
** Launches rays and fills the framebuffer with the proper color for 
** every pixels.
** The frame is static so the function only needs to be called once at
** the beginning of the program (as it currently is).
**
** //// my_framebuffer_destroy(t_my_framebuffer *framebuffer)
** Frees the space allocated to the framebuffer.
*/

int	main()
{
  sfVideoMode		mode = {FRAMEBUFFER_WIDTH, FRAMEBUFFER_HEIGHT, 32};
  sfRenderWindow*	window;
  sfTexture*		texture;
  sfSprite*		sprite;

  t_my_framebuffer	*framebuffer;

  /* Create the main window */
  window = sfRenderWindow_create(mode, "Bootstrap Raytracer 1",
				 sfResize | sfClose, NULL);
  if (!window)
    return EXIT_FAILURE;
  /* Load a sprite to display */
  texture = sfTexture_create(FRAMEBUFFER_WIDTH, FRAMEBUFFER_HEIGHT);
  if (!texture)
    return EXIT_FAILURE;
  sprite = sfSprite_create();
  sfSprite_setTexture(sprite, texture, sfTrue);

  /* Create a framebuffer to store pixels in */
  framebuffer = my_framebuffer_create(FRAMEBUFFER_WIDTH, FRAMEBUFFER_HEIGHT);

  /* Raytrace the scene and start game loop */
  raytrace_scene(framebuffer);
  sfTexture_updateFromPixels(texture, framebuffer->pixels,
			     framebuffer->width, framebuffer->height,
			     0,0);
  process_game_loop(window, sprite);

  /* Destroy resources */
  my_framebuffer_destroy(framebuffer);
  sfSprite_destroy(sprite);
  sfTexture_destroy(texture);
  sfRenderWindow_destroy(window);
  return EXIT_SUCCESS;
}

int		process_game_loop(sfRenderWindow *window, sfSprite *sprite)
{
  sfEvent	event;

  /* Start the game loop */
  while (sfRenderWindow_isOpen(window))
    {
      /* Process events */
      while (sfRenderWindow_pollEvent(window, &event))
        {
	  /* Close window : exit */
	  if (event.type == sfEvtClosed)
	    sfRenderWindow_close(window);
        }
      /* Clear the screen */
      sfRenderWindow_clear(window, sfBlack);
      /* Draw the sprite */
      sfRenderWindow_drawSprite(window, sprite, NULL);
      /* Update the window */
      sfRenderWindow_display(window);
    }
}
