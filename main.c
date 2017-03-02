#include <SFML/Graphics.h>
#include "framebuffer.h"

#define	FRAMEBUFFER_WIDTH 600
#define FRAMEBUFFER_HEIGHT 400

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
	  choice(framebuffer, eye_pos, dir_vector, screen_pos);
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

  window = sfRenderWindow_create(mode, "Bootstrap Raytracer 1",
				 sfResize | sfClose, NULL);
  if (!window)
    return EXIT_FAILURE;
  texture = sfTexture_create(FRAMEBUFFER_WIDTH, FRAMEBUFFER_HEIGHT);
  if (!texture)
    return EXIT_FAILURE;
  sprite = sfSprite_create();
  sfSprite_setTexture(sprite, texture, sfTrue);
  framebuffer = my_framebuffer_create(FRAMEBUFFER_WIDTH, FRAMEBUFFER_HEIGHT);
  raytrace_scene(framebuffer);
  sfTexture_updateFromPixels(texture, framebuffer->pixels,
			     framebuffer->width, framebuffer->height, 0, 0);
  process_game_loop(window, sprite);
  my_framebuffer_destroy(framebuffer);
  sfSprite_destroy(sprite);
  sfTexture_destroy(texture);
  sfRenderWindow_destroy(window);
  return EXIT_SUCCESS;
}

int		process_game_loop(sfRenderWindow *window, sfSprite *sprite)
{
  sfEvent	event;

  while (sfRenderWindow_isOpen(window))
    {
      while (sfRenderWindow_pollEvent(window, &event))
        {
	  if (event.type == sfEvtClosed)
	    sfRenderWindow_close(window);
        }
      sfRenderWindow_clear(window, sfBlack);
      sfRenderWindow_drawSprite(window, sprite, NULL);
      sfRenderWindow_display(window);
    }
}
